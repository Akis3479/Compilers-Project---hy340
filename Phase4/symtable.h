#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE    509
#define HASH_MULTIPLIER 65599

#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

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

typedef enum scopespace_t{
    tipota,
    programvar,
    functionlocal,
    formalarg
}scopespace_t;

typedef struct SymbolTableEntry{
	int isActive;
	union value{
		Variable *varVal;
		Function *funcVal;
	} value;
	enum SymbolType type;
	struct SymbolTableEntry *nextEntry;
	struct SymbolTableEntry *nextSameScope;
	unsigned offset;
	scopespace_t space;
	int totalLocals;
	unsigned taddress;
} SymbolTableEntry;

typedef struct symtable {
	unsigned int total;
	SymbolTableEntry *hashtab[DEFAULT_SIZE];
} SymTable_T;

typedef struct tempVarList{
	SymbolTableEntry *tempvar;
	struct tempVarList *next;
}tempVarList;

tempVarList *TempVarListHead = NULL;

extern int yylineno;
extern int inFunct;
extern int inLoop; // ALLAGI
int GlobalScope = 0;
char *lastFunctionRead, *lastUnknownFunctionRead;
int lastFunctionReadScope;
int localspecified = 0;
int lastLookupTypeSeen;
int isUserFunc = 0;
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
SymbolTableEntry* insert(SymTable_T *symtab, char *key, int scope, int line, int type, unsigned offset, scopespace_t space);
void hide(int scope);
int lookup(char *key, int scope);
int lookupInScope(char *key, int scope);
void printSymbolTable();
void initializeSymbolTable(SymTable_T *symtab);
int isLibfunc(char *key);
void insertFuncArgs(SymTable_T *symtab, char *newArg, int scope);
void setLastFunctionRead(char *name, int scope);
void PrintListOfArgs(SymTable_T *symtab);
int isUserFunction(SymTable_T *symtab, char *key); /* NEW */

SymbolTableEntry* RetLookup(char *key,int currScope);
SymbolTableEntry* RetLookupInScope(char *key, int scope);



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
	symtab = (SymTable_T *)malloc(sizeof(SymTable_T));
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
SymbolTableEntry* insert(SymTable_T *symtab, char *key, int scope, int line, int type, unsigned offset, scopespace_t space){
	SymbolTableEntry *newEntry;
	SymbolTableEntry *ptr;
	SymbolTableEntry *symbol;
	SymbolTableEntry *scopePtr = ScopeArray[scope];
	unsigned int hash;
	char buf[4];
	int lookupreturn = lookup(key, scope);

	symbol = RetLookup(key, scope);

	if(lookupreturn >= 0 && isLibfunc(key) == 1 && (localspecified == 1 || type == USERFUNC || type == FORMAL)){ // ALLAGI
		if(type == FORMAL){ // ALLAGI
			printf("\033[1;31mError: Cannot pass a library function as formal argument. Symbol %s Line %d \033[0m \n", key, yylineno);
			exit(EXIT_FAILURE);
			return NULL;
		}
		printf("\033[1;31mError: Cannot shadow global library function. Symbol %s Line %d \033[0m \n", key, yylineno);
		exit(EXIT_FAILURE);
		return NULL;
	}else if(lookupreturn >= 0 && localspecified==1){
		if(lookupInScope(key, scope)==1) {return NULL;}

	}else if(lookupreturn >= 0 && type==FORMAL && lastLookupTypeSeen != FORMAL){ // ALLAGI

	}else if(lookupreturn >= 0 && (type == LOCALS || type == GLOBAL || type == FORMAL)){
		if(type == FORMAL && lastLookupTypeSeen == FORMAL){
			fprintf(stderr,"\033[1;31mError: Redefinition of Formal Argument. Symbol \"%s\" Line %d \033[0m \n", key, yylineno);
			exit(EXIT_FAILURE);
			return NULL;
		}
		if(lookupreturn < scope && isLibfunc(key) == 0 && inFunct>1 && localspecified == 0 && isUserFunc == 0 && inLoop == 0){ // ALLAGI
			fprintf(stderr,"\033[1;31mError: Cannot access symbol \"%s\" Line %d \033[0m \n", key, yylineno);
			exit(EXIT_FAILURE);
			return NULL;
		}
		if(symbol != NULL){
			return symbol;
		}
		return NULL;
	}else if(lookupreturn < 0 && type == LOCALS){

	}else if(lookupInScope(key, scope)==1 && type==USERFUNC && (lastLookupTypeSeen == GLOBAL || lastLookupTypeSeen == LOCALS)){
		printf("\033[1;31mError: Variable Redefinition as function. Symbol %s Line %d \033[0m \n", key, yylineno);
		exit(EXIT_FAILURE);
		return NULL;
	}else if(lookupInScope(key, scope)==1 && type == USERFUNC){
		printf("\033[1;31mError: Function Redefinition. Symbol %s Line %d \033[0m \n", key, yylineno);
		exit(EXIT_FAILURE);
		return NULL;
	}else if(lookupreturn < 0 && type == USERFUNC){

	}

	newEntry = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
	if (newEntry == NULL) {
		printf("ERROR: could not allocate new node\n");
		exit(EXIT_FAILURE);
		return NULL;
	}
	newEntry->isActive = 1;
	newEntry->nextEntry = NULL;
	newEntry->nextSameScope = NULL;
	newEntry->type = (enum SymbolType)type;

	newEntry->offset = offset;
	newEntry->space = space;


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

	return newEntry;
}

/* hides the symbols that are in the scope specified */
void hide(int scope){
	SymbolTableEntry *ptr = ScopeArray[scope];
	
	if(scope == 0) return;

	while(ptr!=NULL){
		ptr->isActive = 0;
		ptr = ptr->nextSameScope;
	}
}

/* returns the scope where the key was found or -1 for not found */
int lookup(char *key, int currScope){
	int i=currScope;

	while(!lookupInScope(key, i) && i>=0){
		i--;
	}
	
	return i;
}

SymbolTableEntry* RetLookup(char *key,int currScope){
	int i=currScope;
	SymbolTableEntry* symbol = NULL;
	while(((symbol = RetLookupInScope(key, i)) == NULL) && i>=0){
		i--;
	}
	
	
	return symbol;
}

/* returns 1 if found and 0 otherwise */
int lookupInScope(char *key, int scope){
	SymbolTableEntry *ptr = ScopeArray[scope];
	while(ptr!=NULL){
		if(ptr->value.varVal->name != NULL && strcmp(ptr->value.varVal->name, key) == 0 && ptr->isActive==1){
			lastLookupTypeSeen = ptr->type;
			if(ptr->type == USERFUNC) isUserFunc = 1;
			else if(ptr->type != USERFUNC) isUserFunc = 0;
			return 1;
		}
		ptr = ptr->nextSameScope;
	}
	return 0;
}

SymbolTableEntry* RetLookupInScope(char *key, int scope){
	SymbolTableEntry *ptr = ScopeArray[scope];
	while(ptr!=NULL){
		if(ptr->value.varVal->name != NULL && strcmp(ptr->value.varVal->name, key) == 0 && ptr->isActive==1){
			return ptr;
		}
		ptr = ptr->nextSameScope;
	}
	return NULL;
}

/* prints the symbol table */
void printSymbolTable(){
	int i=0;
	int j=0;
	SymbolTableEntry *head;
	while(ScopeArray[i] != NULL){
		head = ScopeArray[i];
		fprintf(stderr,"\n\033[0;32m-------------   Scope #%d   -------------\033[0m\n", i);
		while(head != NULL){
			if(head->type !=3 && head->type !=4){
				/* if VARIABLE */
				fprintf(stderr,"\"%s\"  ", head->value.varVal->name);
				switch(head->type){
					case GLOBAL:
						fprintf(stderr,"[global variable]");
						break;
					case LOCALS:
						fprintf(stderr,"[local variable]");
						break;
					case FORMAL:
						fprintf(stderr,"[formal argument]");
						break;
					default:
						break;
				}
				fprintf(stderr,"  (line %d)  (scope %d)\n", head->value.varVal->line, head->value.varVal->scope);
			}else{
				/*if FUNCTION */
				fprintf(stderr,"\"%s\"  ", head->value.funcVal->name);
				switch(head->type){
					case USERFUNC:
						fprintf(stderr,"[user function]");
						break;
					case LIBFUNC:
						fprintf(stderr,"[library function]");
						break;
					default:
						break;
				}
				fprintf(stderr,"  (line %d)  (scope %d)\n", head->value.funcVal->line, head->value.funcVal->scope);
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
	fprintf(stderr,"\n");
}

/* Initializes Symbol Table with the global library functions */
void initializeSymbolTable(SymTable_T *symtab){
	int i=0;
	for(i=0; i<12; i++){
		insert(symtab, libfuncArr[i], 0, 0, LIBFUNC, 0, 0);
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

/* returns 1 if key if found in symtab and is user function */
int isUserFunction(SymTable_T *symtab, char *key){
	int index = hash_function(key);
	SymbolTableEntry *tmp = symtab->hashtab[index];

	while(tmp!=NULL){
		if(tmp->isActive==1 && tmp->type==USERFUNC && strcmp(tmp->value.funcVal->name, key)==0){
			return 1;
		}
		tmp = tmp->nextEntry;
	}
	return 0;
}

#endif