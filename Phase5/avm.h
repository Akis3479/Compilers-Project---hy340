/* #include "../PhaseD/t_code_gen.h"*/
#include <stdio.h>
#include "AlphaStructures.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef _AVM_H_
#define _AVM_H_

#define AVM_STACKENV_SIZE 4
#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211

#define AVM_SAVEDTOPSP_OFFSET	1 
#define AVM_SAVEDTOP_OFFSET	2 
#define AVM_SAVEDPC_OFFSET	3 
#define AVM_NUMACTUALS_OFFSET 	4 

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_ENDING_PC codeSize
#define execute_add execute_arithmetic 
#define execute_sub execute_arithmetic 
#define execute_mul execute_arithmetic 
#define execute_div execute_arithmetic 
#define execute_mod execute_arithmetic 


typedef struct avm_memcell avm_memcell;
typedef struct avm_table_bucket avm_table_bucket;
typedef struct avm_table avm_table;

typedef enum avm_memcell_t{
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m  = 5,
    nil_m = 6,
    undef_m = 7
}avm_memcell_t;

struct avm_memcell{
    avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        avm_table* tableVal;
        unsigned funcVal;
        char* libfuncVal;
    }data;
};

struct avm_table_bucket{
    avm_memcell key;
    avm_memcell value;
    avm_table_bucket* next;
};

struct avm_table{
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
};

typedef void (*execute_func_t)(instruction*);
typedef void (*memclear_func_t) (avm_memcell*);
typedef char* (*tostring_func_t)(avm_memcell*);
typedef double (*arithmetic_func_t)(double x, double y);
typedef unsigned char (*tobool_func_t)(avm_memcell*);
typedef void(*library_func_t)(void);

// GLOBAL SECTION
avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;
avm_memcell stack[AVM_STACKSIZE];   //stack_cell
unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction* code = (instruction*) 0;
unsigned totalActuals = 0;
char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};
//GLOBAL SECTION

// FUNCTION DEFINITIONS
double consts_getnumber(unsigned index);
char*  consts_getstring(unsigned index);
char*  libfuncs_getused(unsigned index);

static void avm_initstack(void);
void avm_tableincrefcounter(avm_table* t);
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p);
void avm_tablebucketsdestroy(avm_table_bucket** p);
avm_table* avm_tablenew();
void avm_tabledestroy(avm_table* t);
// avm_memcell* avm_tablegetelem(avm_memcell* key);
// void avm_tablesetelem(avm_memcell* key, avm_memcell* value);
void avm_memcellclear(avm_memcell* m);
void execute_assign(instruction* instr);

void execute_add(instruction* instr);
void execute_sub(instruction* instr);
void execute_mul(instruction* instr);
void execute_div(instruction* instr);
void execute_mod(instruction* instr);
void execute_uminus(instruction* instr);   //x

void execute_and(instruction* instr);   //x
void execute_or(instruction* instr);   //x
void execute_not(instruction* instr);   //x

void execute_jeq(instruction* instr);
void execute_jne(instruction* instr);
void execute_jle(instruction* instr);
void execute_jge(instruction* instr);
void execute_jlt(instruction* instr);
void execute_jgt(instruction* instr);

void execute_call(instruction* instr);
void execute_pusharg(instruction* instr);
void execute_funcenter(instruction* instr);
void execute_funcexit(instruction* instr);

void execute_newtable(instruction* instr);
void execute_tablegetelem(instruction* instr);
void execute_tablesetelem(instruction* instr);

void execute_nop(instruction* instr);

void avm_warning(char* format, ...);
void avm_assign(avm_memcell* lv, avm_memcell* rv);

void avm_error(char* format, ...);
char* avm_tostring(avm_memcell*);
void avm_calllibfunc(char* funcName);
void avm_callsaveenvironment(void);

userfunc* avm_getfuncinfo(unsigned address);
library_func_t avm_getlibraryfunc(char* id);

char* number_tostring(avm_memcell*);
char* string_tostring(avm_memcell*);
char* bool_tostring(avm_memcell*);
char* table_tostring(avm_memcell*);
char* userfunc_tostring(avm_memcell*);
char* libfunc_tostring(avm_memcell*);
char* nil_tostring(avm_memcell*);
char* undef_tostring(avm_memcell*);

void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);

double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);

unsigned char number_tobool(avm_memcell* m);
unsigned char string_tobool(avm_memcell* m);
unsigned char bool_tobool(avm_memcell* m);
unsigned char table_tobool(avm_memcell* m);
unsigned char userfunc_tobool(avm_memcell* m);
unsigned char libfunc_tobool(avm_memcell* m);
unsigned char nil_tobool(avm_memcell* m);
unsigned char undef_tobool(avm_memcell* m);
unsigned char avm_tobool(avm_memcell* m);

avm_memcell* avm_tablegetelem(avm_table*, avm_memcell* index);
void avm_tablesetelem(avm_table*, avm_memcell* index, avm_memcell* content);

void avm_registerlibfunc(char* id, library_func_t addr);
void libfunc_typeof(void);
void libfunc_totalarguments(void);

void avm_initialize(void);
void libfunc_print(void);
void libfunc_typeof(void);
void libfunc_input(void);
void libfunc_objectmemberkeys(void);
void libfunc_objecttotalmembers(void);
void libfunc_objectcopy(void);
void libfunc_totalarguments(void);
void libfunc_argument(void);
void libfunc_strtonum(void);
void libfunc_sqrt(void);
void libfunc_cos(void);
void libfunc_sin(void);
// FUNCTION DEFINITIONS END

// FUNCTION TABLES
execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

memclear_func_t memclearFuncs[] = {
    0,  /*number*/
    memclear_string,
    0,  /*bool*/
    memclear_table,
    0,  /*userfunc*/
    0,  /*libfunc*/
    0,  /*nil*/
    0   /*undef*/
};

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring,
};

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool,
};

typedef void (*library_func_t) (void);
library_func_t avm_getlibraryfunc ( char *id);


library_func_t libraryFuncs[12]={0};

// FUNCTION TABLES END

static void avm_initstack(void){
    unsigned i;
    for(i = 0; i<AVM_STACKSIZE; i++){
        AVM_WIPEOUT(stack[i]);  //stack_cell
        stack[i].type = undef_m; //stack_cell   
    }
}

double consts_getnumber(unsigned index){

}
char*  consts_getstring(unsigned index){

}
char*  libfuncs_getused(unsigned index){

}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    switch(arg->type){
        case global_a: return &stack[AVM_STACKSIZE-1-arg->val];
        case local_a: return &stack[topsp-arg->val];
        case formal_a: return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case retval_a: return &retval;
        case number_a: {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a: {
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }
        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a: reg->type = nil_m; return reg;
        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        } 
        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = strdup(libfuncs_getused(arg->val));
            return reg;
        }
        default: assert(0);
    }
}

void execute_cycle(void){
    if(executionFinished){
        return;
    }else if(pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    }else{
        assert(pc < AVM_ENDING_PC);
        instruction* instr = code + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if(instr->srcLine){
            currLine = instr->srcLine;
        }
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode]) (instr);
        if(pc == oldPC){
            ++pc;
        }
    }
}

void avm_memcellclear(avm_memcell* m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f){
            (*f)(m);
        }
        m->type = undef_m;
    }
}


void memclear_string(avm_memcell* m){
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m){
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

void execute_assign(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);

    // printf("386:: %p %p\n", lv , &stack[top]);

    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv >= &stack[top] || lv == &retval)); //N-1??AVM_STACKSIZE
    assert(rv);

    avm_assign(lv, rv);
}

void avm_assign(avm_memcell* lv, avm_memcell* rv){
    if(lv == rv){
        return;
    }
    if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal){
        return;
    }
    if(rv->type == undef_m){
        avm_warning("assign from 'undef' content!");
    }
    avm_memcellclear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));

    if(lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    }else if(lv->type == table_m){
            avm_tabledecrefcounter(lv->data.tableVal);
    }
}


void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveenvironment();

    switch(func->type){
        case userfunc_m: {
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);
            break;
        }
        case string_m: avm_calllibfunc(func->data.strVal); break;
        case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;
        default: {
            char* s = avm_tostring(func);
            avm_error("call: cannot bind '%s' to function!", s);
            free(s);
            executionFinished = 1;
        }
    }
}

void avm_dec_top(void){
    if(!top){
        avm_error("stack overflow");
        executionFinished = 1;
    }else{
        --top;
    }
}

void avm_push_envvalue(unsigned val){
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenvironment(void){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->arg1, &ax); //mallon prepei na valoume arg1
    assert(func);
    assert(pc == func->data.funcVal);

    totalActuals = 0;
    userfunc* funcinfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcinfo->localSize;
}

unsigned avm_get_envvalue(unsigned i){
    assert(stack[i].type = number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(instruction* instr){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while(++oldTop <= top){
        avm_memcellclear(&stack[oldTop]);
    }
}

void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        avm_error("unsupported lib func '%s' called!", id);
        executionFinished = 1;
    }else{
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished){
            execute_funcexit((instruction *)0);
        }
    }
}


unsigned avm_totalactuals(void){
    return avm_get_envvalue(top + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print(void){
    unsigned i;
    unsigned n = avm_totalactuals();
    for(i=0; i<n; ++i){
        char* s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}

void execute_pusharg(instruction* instr){
    avm_memcell* arg = avm_translate_operand(&instr->result, &ax);
    assert(arg);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}




char* avm_tostring(avm_memcell* m){
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

double add_impl(double x, double y){
    return x+y;
}

double sub_impl(double x, double y){
    return x-y;
}

double mul_impl(double x, double y){
    return x*y;
}

double div_impl(double x, double y){
    return x/y;
}

double mod_impl(double x, double y){
    return ((unsigned) x) % ((unsigned) y);
}


void execute_arithmetic(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    // printf("566:: %p %p\n",  lv , &stack[top] );
    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv >= &stack[top] || lv == &retval)); // N??AVM_STACKSIZE
    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m){
        avm_error("not a number in arithmetic!");
        executionFinished = 1;
    }else{
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}

unsigned char number_tobool(avm_memcell* m){
    return m->data.numVal != 0;
}
unsigned char string_tobool(avm_memcell* m){
    return m->data.strVal[0] != 0;
}
unsigned char bool_tobool(avm_memcell* m){
    return m->data.boolVal;
}
unsigned char table_tobool(avm_memcell* m){
    return 1;
}
unsigned char userfunc_tobool(avm_memcell* m){
    return 1;
}
unsigned char libfunc_tobool(avm_memcell* m){
    return 1;
}
unsigned char nil_tobool(avm_memcell* m){
    return 0;
}
unsigned char undef_tobool(avm_memcell* m){
    assert(0);
    return 0;
}

unsigned char avm_tobool(avm_memcell* m){
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}


void execute_jeq(instruction* instr){
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality!");
    }else if(rv1->type == nil_m || rv2->type == nil_m){
            result = rv1->type == nil_m && rv2->type == nil_m;
    }else if(rv1->type == bool_m || rv2->type == bool_m){
            result = (avm_tobool)(rv1) == (avm_tobool)(rv2);
    }else if(rv1->type != rv2->type){
        avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    }else{
        /*Εδώ συμπληρώστε την
        υλοποίηση. Αρκεί να
        κάνετε dispatching ως
        προς τον τύπο του rv1*/
    }

    if(!executionFinished && result){
        pc = instr->result.val;
    }
}

void libfunc_typeof(void){
    unsigned n = avm_totalactuals();

    if(n != 1){
        avm_error("one argument (not %d) expected in 'typeof'!",n);
    }else{
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void execute_newtable(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval)); // N??AVM_STACKSIZE

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}


void execute_tablegetelem(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*) 0);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);

    assert(lv && &stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval); // N??AVM_STACKSIZE
    assert(t && &stack[AVM_STACKSIZE-1] >= t && t > &stack[top]); // N??AVM_STACKSIZE
    assert(i);

    avm_memcellclear(lv);
    lv->type = nil_m;

    if(t->type != table_m){
        avm_error("illegal use of type %s as table!", typeStrings[t->type]);
    }else{
        avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
        if(content){
            avm_assign(lv, content);
        }else{
            char* ts = avm_tostring(t);
            char* is = avm_tostring(i);
            avm_warning("%s[%s] not found!",ts, is);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(instruction* instr){
    avm_memcell* t = avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* c = avm_translate_operand(&instr->arg2, &bx);

    assert(t && &stack[AVM_STACKSIZE-1] >= t && t > &stack[top]); // N??AVM_STACKSIZE
    assert(i && c);

    if(t->type != table_m){
        avm_error("illegal use of type %s as table!", typeStrings[t->type]);
    }else{
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}

void avm_initialize(void){
    avm_initstack();

    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("input", libfunc_typeof);
    avm_registerlibfunc("objectmemberkeys", libfunc_typeof);
    avm_registerlibfunc("objecttotalmembers", libfunc_typeof);
    avm_registerlibfunc("objectcopy", libfunc_typeof);
    avm_registerlibfunc("totalarguments", libfunc_typeof);
    avm_registerlibfunc("argument", libfunc_typeof);
    avm_registerlibfunc("strtonum", libfunc_typeof);
    avm_registerlibfunc("sqrt", libfunc_typeof);
    avm_registerlibfunc("cos", libfunc_typeof);
    avm_registerlibfunc("sin", libfunc_typeof);
}

void libfunc_totalarguments(void){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if(!p_topsp){
        avm_error("'totalarguments' called outside a function!");
        retval.type = nil_m;
    }else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p){
    unsigned i;
    for(i = 0; i<AVM_TABLE_HASHSIZE; i++){
        p[i] = (avm_table_bucket*) 0;
    }
}

avm_table* avm_tablenew(){
    avm_table* t = (avm_table*) malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = 0;
    t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}

void avm_tablebucketsdestroy(avm_table_bucket** p){
    unsigned i;
    avm_table_bucket* b;
    for(i = 0; i<AVM_TABLE_HASHSIZE; i++,++p){      /*Kati de paei kala edw*/
        for(b = *p; b;){                            /*Kati de paei kala edw*/
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*) 0;
    }
}

void avm_tabledestroy(avm_table* t){
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}

void avm_warning(char* format, ...){

}

void avm_error(char* format, ...){

}

userfunc* avm_getfuncinfo(unsigned address){
    
}

library_func_t avm_getlibraryfunc(char* id){

}

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index){

}

void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content){

}

void avm_registerlibfunc(char* id, library_func_t addr){

}

void execute_uminus(instruction* instr){

}   //x

void execute_and(instruction* instr){

}   //x
void execute_or(instruction* instr){

}   //x
void execute_not(instruction* instr){

}   //x
void execute_jne(instruction* instr){

}
void execute_jle(instruction* instr){

}
void execute_jge(instruction* instr){

}
void execute_jlt(instruction* instr){

}
void execute_jgt(instruction* instr){

}

void execute_nop(instruction* instr){

}

char* number_tostring(avm_memcell* var){
    return "";
}
char* string_tostring(avm_memcell* var){
    return "";
}
char* bool_tostring(avm_memcell* var){
    return "";
}
char* table_tostring(avm_memcell* var){
    return "";
}
char* userfunc_tostring(avm_memcell* var){
    return "";
}
char* libfunc_tostring(avm_memcell* var){
    return "";
}
char* nil_tostring(avm_memcell* var){
    return "";
}
char* undef_tostring(avm_memcell* var){
    return "";
}

#endif