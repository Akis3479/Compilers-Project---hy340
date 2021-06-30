#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE    509
#define HASH_MULTIPLIER 65599

typedef struct Variable{
	char *name;
	unsigned int scope;
	unsigned int line;
} Variable;

typedef struct Function{
	char *name; 
	/* table of arguments */
	struct SymbolTableEntry **funcargs;
	/* number of arguments */
	int argsnum;
	unsigned int scope;
	unsigned int line;
} Function;

enum SymbolType{
	GLOBAL, LOCALS, FORMAL, USERFUNC, LIBFUNC
};

typedef struct SymbolTableEntry{
	int isActive;
	union value{
		Variable *varVal;
		Function *funcVal;
	} value;
	enum SymbolType type;
	struct SymbolTableEntry *nextEntry;
	struct SymbolTableEntry *nextSameScope;
} SymbolTableEntry;

typedef struct symtable {
	unsigned int total;
	SymbolTableEntry *hashtab[DEFAULT_SIZE];
} SymTable_T;

extern int yylineno;
int GlobalScope = 0;
char *lastFunctionRead, *lastUnknownFunctionRead;
int lastFunctionReadScope;
int localspecified = 0;
int lastLookupTypeSeen;
SymbolTableEntry *ScopeArray[100]; /* heads of scope lists */
int unknownfunctionNum = 0; /* unknown function name suffix */
char *libfuncArr[12] = {"print", "input", "objectmemberkeys", 
						"objecttotalmembers", "objectcopy", 
						"totalarguments", "argument", "typeof", 
						"strtonum", "sqrt", "cos", "sin"
						};

unsigned int hash_function(char *key); 
SymTable_T* SymTable_new(void);
unsigned int getLength(SymTable_T symtab);
int insert(SymTable_T *symtab, char *key, int scope, int line, int type);
void hide(SymTable_T *symtab, int scope);
int lookup(SymTable_T *symtab, char *key, int scope);
int lookupInScope(SymTable_T *symtab, char *key, int scope);
void printSymbolTable(SymTable_T *symtab);
void initializeSymbolTable(SymTable_T *symtab);
int isLibfunc(char *key);
void insertFuncArgs(SymTable_T *symtab, char *newArg, int scope);
void setLastFunctionRead(char *name, int scope);
void PrintListOfArgs(SymTable_T *symtab);



/* returns the index of hash table where key goes */
unsigned int hash_function(char *key) {
	int i;
	unsigned int uiHash = 0U;
	for (i = 0; key[i] != '\0'; i++)
		uiHash = uiHash * HASH_MULTIPLIER + (unsigned int)key[i];
	return (uiHash % DEFAULT_SIZE);
}

/* makes a new symbol table */
SymTable_T* SymTable_new(void){
	SymTable_T *symtab;
	int i;
	symtab = malloc(sizeof(SymTable_T));
	if (symtab == NULL) {
		printf("ERROR: could not allocate new symtable\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < DEFAULT_SIZE; i++)
		symtab->hashtab[i] = NULL;

	/* initialize ScopeArray */
	for(i=0; i<100; i++){
		ScopeArray[i] = NULL;
	}

	initializeSymbolTable(symtab);

	return symtab;
}

/* returns 0 for failure to insert, or 1 for success */
int insert(SymTable_T *symtab, char *key, int scope, int line, int type){
	SymbolTableEntry *newEntry;
	SymbolTableEntry *ptr;
	SymbolTableEntry *scopePtr = ScopeArray[scope];
	unsigned int hash;
	char buf[4];

	if(lookup(symtab, key, scope) >= 0 && isLibfunc(key) == 1 && (localspecified == 1 || type == USERFUNC)){
		printf("\033[1;31mError: Cannot shadow global library function. Symbol %s Line %d \033[0m \n", key, yylineno);
		exit(EXIT_FAILURE);
		return 0;
	}else if(lookup(symtab, key, scope) >= 0 && localspecified==1){
		if(lookupInScope(symtab, key, scope)==1) {return 0;}

	}else if(lookup(symtab, key, scope) >= 0 && (type == LOCALS || type == GLOBAL)){
		return 0;
	}else if(lookup(symtab, key, scope) < 0 && type == LOCALS){

	}else if(lookupInScope(symtab, key, scope)==1 && type==USERFUNC && (lastLookupTypeSeen == GLOBAL || lastLookupTypeSeen == LOCALS)){
		printf("\033[1;31mError: Variable Redefinition as function. Symbol %s Line %d \033[0m \n", key, yylineno);
		exit(EXIT_FAILURE);
		return 0;
	}else if(lookupInScope(symtab, key, scope)==1 && type == USERFUNC){
		printf("\033[1;31mError: Function Redefinition. Symbol %s Line %d \033[0m \n", key, yylineno);
		exit(EXIT_FAILURE);
		return 0;
	}else if(lookup(symtab, key, scope) < 0 && type == USERFUNC){

	}

	


	
	newEntry = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
	if (newEntry == NULL) {
		printf("ERROR: could not allocate new node\n");
		exit(EXIT_FAILURE);
	}
	newEntry->isActive = 1;
	newEntry->nextEntry = NULL;
	newEntry->nextSameScope = NULL;
	newEntry->type = type;

	if(type != 3 && type != 4){
		/* is VARIABLE */
		newEntry->value.varVal = (Variable*)malloc(sizeof(Variable));
		newEntry->value.varVal->name = strdup(key);
		newEntry->value.varVal->scope = scope;		   
		newEntry->value.varVal->line = line;
		hash = hash_function(key);
	}else{
		/*is FUNCTION */
		newEntry->value.funcVal = (Function*)malloc(sizeof(Function));
		if(strcmp(key, "") == 0){
			snprintf(buf, 4, "$%d", unknownfunctionNum++);
			setLastFunctionRead(buf, scope);
			newEntry->value.funcVal->name = strdup(buf);
		}else{
			setLastFunctionRead(key, scope);
			newEntry->value.funcVal->name = strdup(key);
		}
		hash = hash_function(lastFunctionRead);
		newEntry->value.funcVal->scope = scope;
		newEntry->value.funcVal->line = line;
		newEntry->value.funcVal->argsnum = 0;
		newEntry->value.funcVal->funcargs = NULL;
	}
	
	ptr = symtab->hashtab[hash];
	if(ptr == NULL){
		/* ptr = newEntry; */
		symtab->hashtab[hash] = newEntry;
	}else{
		while(ptr->nextEntry != NULL)
			ptr = ptr->nextEntry;
		ptr->nextEntry = newEntry;
	}

	if(scopePtr == NULL)
		/*scopePtr = newEntry;*/
		ScopeArray[scope] = newEntry;
	else{
		while(scopePtr->nextSameScope != NULL)
			scopePtr = scopePtr->nextSameScope;
		scopePtr->nextSameScope = newEntry;
	}

	return 1;
}

/* hides the symbols that are in the scope specified */
void hide(SymTable_T *symtab, int scope){
	SymbolTableEntry *ptr = ScopeArray[scope];

	while(ptr!=NULL){
		ptr->isActive = 0;
		ptr = ptr->nextSameScope;
	}
}

/* returns the scope where the key was found or -1 for not found */
int lookup(SymTable_T *symtab, char *key, int currScope){
	int i=currScope;

	while(!lookupInScope(symtab, key, i) && i>=0){
		i--;
	}
	
	return i;
}

/* returns 1 if found and 0 otherwise */
int lookupInScope(SymTable_T *symtab, char *key, int scope){
	SymbolTableEntry *ptr = ScopeArray[scope];
	while(ptr!=NULL){
		if(ptr->value.varVal->name != NULL && strcmp(ptr->value.varVal->name, key) == 0 && ptr->isActive==1){
			lastLookupTypeSeen = ptr->type;
			return 1;
		}
		ptr = ptr->nextSameScope;
	}
	return 0;
}

/* prints the symbol table */
void printSymbolTable(SymTable_T *symtab){
	int i=0;
	int j=0;
	SymbolTableEntry *head;
	while(ScopeArray[i] != NULL){
		head = ScopeArray[i];
		printf("\n\033[0;32m-------------   Scope #%d   -------------\033[0m\n", i);
		while(head != NULL){
			if(head->type !=3 && head->type !=4){
				/* if VARIABLE */
				printf("\"%s\"  ", head->value.varVal->name);
				switch(head->type){
					case GLOBAL:
						printf("[global variable]");
						break;
					case LOCALS:
						printf("[local variable]");
						break;
					case FORMAL:
						printf("[formal argument]");
						break;
					default:
						break;
				}
				printf("  (line %d)  (scope %d)\n", head->value.varVal->line, head->value.varVal->scope);
			}else{
				/*if FUNCTION */
				printf("\"%s\"  ", head->value.funcVal->name);
				switch(head->type){
					case USERFUNC:
						printf("[user function]");
						break;
					case LIBFUNC:
						printf("[library function]");
						break;
					default:
						break;
				}
				printf("  (line %d)  (scope %d)\n", head->value.funcVal->line, head->value.funcVal->scope);
			}
			head = head->nextSameScope;
		}
		j = i+1;
		while(ScopeArray[j] == NULL){
			j++;
		}
		if(j<100) {
			i = j;
		}else{
			break;
		}
	}
	printf("\n");
}

/* Initializes Symbol Table with the global library functions */
void initializeSymbolTable(SymTable_T *symtab){
	int i=0;
	for(i=0; i<12; i++){
		insert(symtab, libfuncArr[i], 0, 0, LIBFUNC);
	}
}

/* returns 1 if key is a global library function */
int isLibfunc(char *key){
	int i=0;
	for(i=0; i<12; i++){
		if(strcmp(key, libfuncArr[i]) == 0)
			return 1;
	}
	return 0;
}

void insertFuncArgs(SymTable_T *symtab, char *newArg, int scope){
	SymbolTableEntry *lastfunction;
	SymbolTableEntry *tmp;
	int lastFunctionReadIndex = hash_function(lastFunctionRead);
	int newArgIndex = hash_function(newArg);
	
	tmp = symtab->hashtab[lastFunctionReadIndex];
	
	while(tmp != NULL){
		if(tmp->type == 3 && strcmp(lastFunctionRead, tmp->value.funcVal->name)==0 && GlobalScope == (lastFunctionReadScope+1)){
			lastfunction = tmp;
			break;
		}
		tmp = tmp->nextEntry;
	}

	/* last function position found in symtable*/
	tmp = symtab->hashtab[newArgIndex];
	while(tmp!=NULL){
		if(tmp->type == 2 && strcmp(newArg, tmp->value.varVal->name)==0 && tmp->value.varVal->scope == GlobalScope){
			if(lastfunction->value.funcVal->funcargs == NULL){
				lastfunction->value.funcVal->funcargs = (SymbolTableEntry **)malloc(sizeof(SymbolTableEntry *));
				lastfunction->value.funcVal->funcargs[lastfunction->value.funcVal->argsnum++] = tmp;
				break;
			}else{
				lastfunction->value.funcVal->funcargs[lastfunction->value.funcVal->argsnum++] = tmp;
				break;
			}
		}
		tmp=tmp->nextEntry;
	}


}

void setLastFunctionRead(char *name, int scope){
	lastFunctionRead = strdup(name);
	lastFunctionReadScope = scope;
}

void PrintListOfArgs(SymTable_T *symtab){
	int index = 0,i;
	SymbolTableEntry *tmp;

	for(index = 0; index < 509; index++){
		tmp = symtab->hashtab[index];
		while(tmp != NULL){
			if(tmp->type == 3){
				printf("%s :: [ ", tmp->value.funcVal->name);
				for(i=0; i<tmp->value.funcVal->argsnum; i++){
					if(i+1 == tmp->value.funcVal->argsnum)
						printf("%s", tmp->value.funcVal->funcargs[i]->value.varVal->name);
					else
						printf("%s -> ", tmp->value.funcVal->funcargs[i]->value.varVal->name);
				}
				printf(" ]\n");
			}
			tmp = tmp->nextEntry;
		}
	}
}