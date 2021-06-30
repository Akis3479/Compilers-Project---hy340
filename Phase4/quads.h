#include "symtable.h"
#include <string.h>
#include <assert.h>

#ifndef _QUADS_H_
#define _QUADS_H_

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad) + CURR_SIZE)

typedef enum iopcode{
    assign, add, sub,
    mul, div_i, mod,
    uminus, and, or,
    not, if_eq, if_noteq,
    if_lesseq, if_greatereq, if_less,
    if_greater, call, param,
    ret, getretval, funcstart,
    funcend, tablecreate, tablegetelem,
    tablesetelem,jump
}iopcode;

typedef enum symbol_t{
    var_s,
    programfunc_s,
    libraryfunc_s
}symbol_t;

typedef enum expr_t {
    var_e, tableitem_e, programfunc_e,
    libraryfunc_e, arithexpr_e, boolexpr_e,
    assignexpr_e, newtable_e, constint_e,constreal_e,
    constbool_e, conststring_e, nil_e
}expr_t;

typedef struct expr {
    expr_t type;
    SymbolTableEntry* sym;
    struct expr* index;
    double realConst;
    int intConst;
    char* strConst;
    unsigned char boolConst;
    struct expr* next;
}expr;

typedef struct quad{
    iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned label;
    unsigned line;
    unsigned taddress;
}quad;

typedef struct stmt_t{
    int breakList, contList;
}stmt_t;

typedef struct forstruct{
        unsigned enter;
        unsigned test;
}forstruct;

typedef struct brcontList{
    int quadNo; // quad no. of break or continue
    int target; // jump target for quadNo
    char name; // 'c' for continue or 'b' for break;
    struct brcontList *next;
}brcontList;

typedef struct call_t{
        expr* elist;
        unsigned char method;
        char* name;
}call_t;

typedef struct retList{
    int quadNo;
    int target;
    struct retList *next;
}retList;


/*->4i Fasi*/

/*<-4i Fasi*/

void expandQuadTable(void);
void emitQuad(iopcode op, expr* result, expr* arg1, expr* arg2, unsigned label, unsigned line);
scopespace_t currscopespace(void);
unsigned currscopeoffset();
void incurrscopeoffset(void);
void enterscopespace(void);
void exitscopespace(void);
void resetformalargoffset(void);
void resetfuntionlocalsoffset(void);
void restorecurrscopeoffset(unsigned n);
unsigned nextquadlabel(void);
void patchlabel(unsigned quadNo, unsigned label);
expr* lvalue_expr(SymbolTableEntry* sym);
expr* newexpr(expr_t t);
expr* newexpr_constint(int integer);
expr* newexpr_constreal(double real);
expr* newexpr_constbool(unsigned char boolean);
expr* newexpr_conststring(char *string);
expr* newexpr_constsnill(void);
expr* member_item(SymTable_T *symtab,expr* lv, char* name);
expr* emit_iftableitem(SymTable_T *symtab,expr* e);
expr* make_call(SymTable_T *symtab,expr* lv,expr* reversed_elist);
void check_arith(expr* e);
void make_stmt(stmt_t* s);
int newList(int i);
int mergelist(int l1,int l2);
void patchlist(int list, int label);
unsigned int istempname(char* s);
unsigned int istempexpr(expr* e);
char* newtempname(void);
SymbolTableEntry* newtemp(SymTable_T *symtab);
void resettemp(void);
void printQuads(void);
void printExpr(expr* expression);
void insertBrContList(int currquad, int label, char name);
void patchBrContList(int startLabel, int endLabel);
void insertRetList(int currquad, int label);
void patchRetList(int startLabel, int endLabel);
void reverseList(expr** head_ref);
void patchJumpBeforeFuncStrt(); // NEWSTUFF
void initJumpsArray(); // NEWSTUFF

/*->4i Fasi*/

/*<-4i Fasi*/

extern GlobalScope;

quad* quads = (quad*) 0;
unsigned total = 0;
unsigned int currQuad = 0;
int tempcounter = 0;
char tempname[6];
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
brcontList * brContListHead = NULL;
retList *retListHead = NULL;

FILE *output;

int jumpsarray[1000]; // NEWSTUFF
int topJumpsArray; // NEWSTUFF

void emitFirstDummyQuad(){
    emitQuad(0, NULL, NULL, NULL, -1, -1);
}

void expandQuadTable(void){
    assert(total == currQuad);
    quad *tmp = (quad *)malloc(NEW_SIZE);
    if(quads != NULL){
        memcpy(tmp, quads, CURR_SIZE);
        free(quads);
    }
    quads = tmp;
    total += EXPAND_SIZE;
}

void emitQuad(iopcode op, expr* result, expr* arg1, expr* arg2, unsigned label, unsigned line){
    if(currQuad == total)   expandQuadTable();

    quad *newquad = quads + currQuad;
    currQuad++;

    newquad->op = op;
    newquad->result = result;
    newquad->arg1 = arg1;
    newquad->arg2 = arg2;
    newquad->label = label;
    newquad->line = line;
}

scopespace_t currscopespace(void){
    if(scopeSpaceCounter == 1)
        return programvar;
    else
        if(scopeSpaceCounter % 2 == 0)
            return formalarg;
        else
            return functionlocal;
}

unsigned currscopeoffset(void){
    switch(currscopespace()){
        case programvar : return programVarOffset;
        case functionlocal : return functionLocalOffset;
        case formalarg : return formalArgOffset;
        default : printf("currscopeoffset\n"); assert(0);
    }
}

void incurrscopeoffset(void){
    switch(currscopespace()){
        case programvar : ++programVarOffset; break;
        case functionlocal : ++functionLocalOffset; break;
        case formalarg : ++formalArgOffset; break;
        default: printf("incurrscopeoffset\n"); assert(0);
    }
}

void enterscopespace(void){
    ++scopeSpaceCounter;
}

void exitscopespace(void){
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}

void resetformalargoffset(void){
    formalArgOffset = 0;
}

void resetfuntionlocalsoffset(void){
    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned n){
    switch(currscopespace()){
        case programvar : programVarOffset = n; break;
        case functionlocal : functionLocalOffset = n; break;
        case formalarg: formalArgOffset = n; break;
        default : printf("restorecurrscopeoffset\n"); assert(0);
    }
}

unsigned nextquadlabel(void){
    return currQuad;
}

void patchlabel(unsigned quadNo, unsigned label){
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

expr* lvalue_expr(SymbolTableEntry* sym){
    //assert(sym);
    expr* e;
    e = (expr *) malloc (sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = (expr *) 0;
    e->sym = sym;

    switch(sym->type){
        case GLOBAL : e->type = var_e; break;
        case LOCALS : e->type = var_e; break;
        case FORMAL : e->type = var_e; break;
        case USERFUNC : e->type = programfunc_e; break;
        case LIBFUNC : e->type = libraryfunc_e; break;
        default: assert(0);
    }

    
    return e;
}

expr* newexpr(expr_t t){
    expr* e = (expr *) malloc (sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
    return e;
}

expr* newexpr_constint(int integer){
    expr* e = newexpr(constint_e);
    e->intConst = integer;
    return e;
}

expr* newexpr_constreal(double real){
    expr* e = newexpr(constreal_e);
    e->realConst = real;
    return e;
}

expr* newexpr_constbool(unsigned char boolean){
    expr* e = newexpr(constbool_e);
    e->boolConst = !!boolean;
    return e;
}

expr* newexpr_conststring(char *string){
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(string);
    return e;
}

expr* newexpr_constsnill(void){
    expr* e = newexpr(nil_e);
    return e;
}

expr* member_item(SymTable_T *symtab,expr* lv, char* name){
    lv = emit_iftableitem(symtab, lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

expr* emit_iftableitem(SymTable_T *symtab,expr* e){
    if(e->type != tableitem_e)
        return e;
    else{
        expr* result = newexpr(var_e);
        result->sym = newtemp(symtab);
        emitQuad(tablegetelem, result, e, e->index,-1 , yylineno);
        return result;
    }
}

void print_elist(expr *list){
    expr *ptr = list;
    while(ptr!=NULL){
        printf("\t%s -> ", ptr->sym->value.varVal->name);
        ptr=ptr->next;
    }
}
expr* make_call(SymTable_T *symtab,expr* lv,expr* reversed_elist){
    expr* func = emit_iftableitem(symtab,lv);
    
    reverseList(&reversed_elist);
    /* print_elist(reversed_elist); */
    
    while(reversed_elist != NULL){
        emitQuad(param, reversed_elist, NULL, NULL, -1, yylineno);
        reversed_elist = reversed_elist->next;
    }
    emitQuad(call, func, NULL, NULL, -1, yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp(symtab);
    emitQuad(getretval, result, NULL, NULL, -1, yylineno);
    return result;
}


void check_arith(expr* e){
    if( e->type == constbool_e      ||
        e->type == conststring_e    ||
        e->type == nil_e            ||
        e->type == newtable_e       ||
        e->type == programfunc_e    ||
        e->type == libraryfunc_e    ||
        e->type == boolexpr_e){
            printf("Illegal expression.\n");
            exit(EXIT_FAILURE);
        }
}

void make_stmt(stmt_t* s){
    s->breakList = 0; // VLEPOUME 0 i 1
    s->contList = 0; // VLEPOUME 0 i 1
}

int newList(int i){
    quads[i].label = 0;
    return i;
}

int mergelist(int l1,int l2){
    if(!l1)
        return l2;
    else{
        if(!l2)
            return l1;
        else{
            int i = l1;
            while(quads[i].label){
                i = quads[i].label;
            }
            quads[i].label = l2;
            return l1;
        }
    }
}

void patchlist(int list, int label){
    while(list){
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

unsigned int istempname(char* s){
    return *s == '^';
}

unsigned int istempexpr(expr* e){
    return (e->sym && istempname(e->sym->value.varVal->name));
}

/*Paragei ena neo onoma*/
char* newtempname(void){
    snprintf(tempname, 6, "^t%d", tempcounter++);
    return tempname;
}

/*η οποία επιστρέφει είτε μία νέα κρυφή μεταβλητή στο παρόν scope
ή μία ήδη διαθέσιμη κρυφή μεταβλητή με το όνομα newtempname.*/
SymbolTableEntry* newtemp(SymTable_T *symtab){
    char* name;
    SymbolTableEntry* sym = NULL;
    tempVarList *ptr = NULL;
    tempVarList *ptr2 = NULL;

    name = newtempname();
    sym = RetLookupInScope(name, GlobalScope);

    if (sym == NULL){
        if(GlobalScope == 0)
            sym = insert(symtab, name, GlobalScope, yylineno, GLOBAL, currscopeoffset(), currscopespace());  //??????????????????????????
        else{
            sym = insert(symtab, name, GlobalScope, yylineno, LOCALS, currscopeoffset(), currscopespace());
        }
        //sym = RetLookupInScope(name, GlobalScope);
    }

    /* insert into tempVarList */
    if(sym != NULL){
        if(TempVarListHead == NULL){
            TempVarListHead = (tempVarList *)malloc(sizeof(tempVarList));
            TempVarListHead->tempvar = sym;
            TempVarListHead->next = NULL;
        }else{
            ptr = TempVarListHead;
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr2 = (tempVarList *) malloc (sizeof(tempVarList));
            ptr2->tempvar = sym;
            ptr2->next = NULL;
            ptr->next = ptr2;
        }
    }

    return sym;
}

/*η οποία καλείται πάντα με την αναγωγή ενός statement, και κάνει τον tempcounter μηδέν.*/
void resettemp(void){
    tempVarList *ptr = TempVarListHead;

    while(ptr!=NULL){
        ptr->tempvar->isActive = 0;
        ptr = ptr->next;
    }

    TempVarListHead = NULL;
    
    tempcounter = 0;

}

void printQuads(void){
    int j=1;
	quad *tmp = quads;

    output = fopen("quads.txt", "w");
	
	while(j < currQuad){
        tmp = quads + j;
		printf("\n\033[1;36m%d: \033[0m",j);
        printf("\033[1;32m");

		fprintf(output, "%d: ",j);
        if(tmp->op == assign){
            printf("ASSIGN  ");
            fprintf(output, "ASSIGN  ");
        }else if(tmp->op == add){
            printf("ADD  ");
            fprintf(output, "ADD  ");
        }else if(tmp->op == sub){
            printf("SUB  ");
            fprintf(output, "SUB  ");
        }else if(tmp->op == mul){
            printf("MUL  ");
            fprintf(output, "MUL  ");
        }else if(tmp->op == div_i){
            printf("DIV  ");
            fprintf(output, "DIV  ");
        }else if(tmp->op == mod){
            printf("MOD  ");
            fprintf(output, "MOD  ");
        }else if(tmp->op == uminus){
            printf("UMINUS  ");
            fprintf(output, "UMINUS  ");
        }else if(tmp->op == and){
            printf("AND  ");
            fprintf(output, "AND  ");
        }else if(tmp->op == or){
            printf("OR  ");
            fprintf(output, "OR  ");
        }else if(tmp->op == not){
            printf("NOT  ");
            fprintf(output, "NOT  ");
        }else if(tmp->op == if_eq){
            printf("IF_EQ  ");
            fprintf(output, "IF_EQ  ");
        }else if(tmp->op == if_noteq){
            printf("IF_NOTEQ  ");
            fprintf(output, "IF_NOTEQ  ");
        }else if(tmp->op == if_lesseq){
            printf("IF_LESSEQ  ");
            fprintf(output, "IF_LESSEQ  ");
        }else if(tmp->op == if_greatereq){
            printf("IF_GREATEREQ  ");
            fprintf(output, "IF_GREATEREQ  ");
        }else if(tmp->op == if_less){
            printf("IF_LESS  ");
            fprintf(output, "IF_LESS  ");
        }else if(tmp->op == if_greater){
            printf("IF_GREATER  ");
            fprintf(output, "IF_GREATER  ");
        }else if(tmp->op == param){
            printf("PARAM  ");
            fprintf(output, "PARAM  ");
        }else if(tmp->op == call){
            printf("CALL  ");
            fprintf(output, "CALL  ");
        }else if(tmp->op == ret){
            printf("RETURN  ");
            fprintf(output, "RETURN  ");
        }else if(tmp->op == getretval){
            printf("GETRETVAL  ");
            fprintf(output, "GETRETVAL  ");
        }else if(tmp->op == funcstart){
            printf("FUNCSTART  ");
            fprintf(output, "FUNCSTART  ");
        }else if(tmp->op == funcend){
            printf("FUNCEND  ");
            fprintf(output, "FUNCEND  ");
        }else if(tmp->op == tablecreate){
            printf("TABLECREATE  ");
            fprintf(output, "TABLECREATE  ");
        }else if(tmp->op == tablegetelem){
            printf("TABLEGETELEM  ");
            fprintf(output, "TABLEGETELEM  ");
        }else if(tmp->op == tablesetelem){
            printf("TABLESETELEM  ");
            fprintf(output, "TABLESETELEM  ");
        }else if(tmp->op == jump){
            printf("JUMP  ");
            fprintf(output, "JUMP  ");
        }
        printf("\033[0m");
        if(tmp->result){
            printExpr(tmp->result);
        }	      
        if(tmp->arg1){
            printExpr(tmp->arg1);
        }      
        if(tmp->arg2){
            printExpr(tmp->arg2);
        }
        if(tmp->label != -1){
            printf("%d  ",tmp->label);
            fprintf(output, "%d  ",tmp->label);
        }
        printf("\033[1;36m[line %d]\033[0m",tmp->line);
        fprintf(output, "[line %d]\n",tmp->line);
        j++;
    }
    printf("\n");
    fprintf(output, "\n");

    fclose(output);
}

void printExpr(expr* expression){
    if(expression->type == var_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == tableitem_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == programfunc_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == libraryfunc_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == arithexpr_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == boolexpr_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == assignexpr_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == newtable_e){
        printf("%s  ",expression->sym->value.varVal->name);
        fprintf(output, "%s  ",expression->sym->value.varVal->name);
    }else if(expression->type == constint_e){
        printf("%d  ",expression->intConst);
        fprintf(output, "%d  ",expression->intConst);
    }else if(expression->type == constreal_e){
        printf("%f  ",expression->realConst);
        fprintf(output, "%f  ",expression->realConst);
    }else if(expression->type == constbool_e){
        if(expression->boolConst == 1){
            printf("TRUE  ");
            fprintf(output, "TRUE  ");
        }else{
            printf("FALSE  ");
            fprintf(output, "FALSE  ");
        }
    }else if(expression->type == conststring_e){
        printf("\"%s\" ",expression->strConst);
        fprintf(output, "\"%s\" ",expression->strConst);
    }else if(expression->type == nil_e){
        printf("NILL  ");
        fprintf(output, "NILL  ");
    }else{
        printf("blabla  ");
        fprintf(output, "blabla  ");
    }

    
}

void insertBrContList(int currquad, int label, char name){
    brcontList *tmp;
    brcontList *tmp2;

    if(brContListHead == NULL){
        brContListHead = (brcontList *)malloc(sizeof(brcontList));
        brContListHead->quadNo = currquad;
        brContListHead->target = label;
        brContListHead->name = name;
        brContListHead->next = NULL;
    }else{
        tmp = brContListHead;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp2 = (brcontList *)malloc(sizeof(brcontList));
        tmp2->quadNo = currquad;
        tmp2->target = label;
        tmp2->name = name;
        tmp2->next = NULL;
        tmp->next = tmp2;
    }
}

void patchBrContList(int startLabel, int endLabel){
    brcontList *ptr = brContListHead;

    while(ptr!=NULL){
        if(ptr->quadNo < endLabel && ptr->quadNo > startLabel && ptr->target == 0 && ptr->name == 'b'){
            ptr->target = endLabel;
            quads[ptr->quadNo].label = ptr->target;
        }else if(ptr->quadNo < endLabel && ptr->quadNo > startLabel && ptr->target == 0 && ptr->name == 'c'){
            ptr->target = startLabel;
            quads[ptr->quadNo].label = ptr->target;
        }
        ptr = ptr->next;
    }
}

void insertRetList(int currquad, int label){
    retList *tmp;
    retList *tmp2;

    if(retListHead == NULL){
        retListHead = (retList *)malloc(sizeof(retList));
        retListHead->quadNo = currquad;
        retListHead->target = label;
        retListHead->next = NULL;
    }else{
        tmp = retListHead;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp2 = (retList *)malloc(sizeof(retList));
        tmp2->quadNo = currquad;
        tmp2->target = label;
        tmp2->next = NULL;
        tmp->next = tmp2;
    }
}

void patchRetList(int startLabel, int endLabel){
    retList *ptr = retListHead;

    while(ptr!=NULL){
        if(ptr->quadNo < endLabel && ptr->quadNo > startLabel && ptr->target == 0){
            printf("\t\t\t\t\t\tLOLOLOLOLOL (%d)\n", ptr->quadNo);
            ptr->target = endLabel;
            quads[ptr->quadNo].label = ptr->target;
        }
        ptr = ptr->next;
    }
}

/* Function to reverse the linked list */
void reverseList(expr** head_ref) { 
    expr* prev = NULL; 
    expr* current = *head_ref; 
    expr* next = NULL; 
    while (current != NULL) { 
        // Store next 
        next = current->next; 
  
        // Reverse current node's pointer 
        current->next = prev; 
  
        // Move pointers one position ahead. 
        prev = current; 
        current = next; 
    } 
    *head_ref = prev; 
}

// NEWSTUFF
void initJumpsArray(){
    int i=0;
    for(i = 0; i<1000; i++)
        jumpsarray[i] = 0;
}

// NEWSTUFF
void patchJumpBeforeFuncStrt(unsigned funcendquadno){
    int i=0;
    quad *tmp;

    for(i=999; i>0; i--){
        if(jumpsarray[i] == -1) break;
    }

    tmp = quads + i;
    if(tmp->op == jump){
        tmp->label = funcendquadno;
        jumpsarray[i] = 0;
    }

}

#endif