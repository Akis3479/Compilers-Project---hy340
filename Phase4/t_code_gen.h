#include "symtable.h"
#include "quads.h"
#include <string.h>
#include <assert.h>

#ifndef _T_CODE_GEN_H_
#define _T_CODE_GEN_H_

typedef struct vmarg vmarg;
typedef struct instruction instruction;
typedef struct userfunc userfunc;
typedef struct incomplete_jump incomplete_jump;

typedef enum vmopcode{
    assign_v, add_v, sub_v,
    mul_v, div_v, mod_v,
    uminus_v, and_v, or_v,
    not_v, jeq_v, jne_v,
    jle_v, jge_v, jlt_v,
    jgt_v, call_v, pusharg_v,
    funcenter_v, funcexit_v, newtable_v,
    tablegetelem_v, tablesetelem_v, nop_v , jump_v
}vmopcode;

typedef enum vmarg_t{
    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a = 10
}vmarg_t;

struct vmarg{
    vmarg_t type;
    unsigned val;
};

struct instruction{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
};

struct userfunc{
    unsigned address;
    unsigned localSize;
    char* id;
};



typedef struct incomplete_jump{
    unsigned instrNo;
    unsigned iaddress;
    struct incomplete_jump* next;
}incomplete_jump;

typedef void (*generator_func_t) (quad*);

void reset_operand(vmarg* arg);

void generate_ADD(quad* quad);
void generate_SUB(quad* quad);
void generate_MUL(quad* quad);
void generate_DIV(quad* quad);
void generate_MOD(quad* quad);
void generate_UMINUS(quad* quad);
void generate_NEWTABLE(quad* quad);
void generate_TABLEGETELEM(quad* quad);
void generate_TABLESETELEM(quad* quad);
void generate_ASSIGN(quad* quad);
void generate_NOP();
void generate_JUMP(quad* quad);
void generate_IF_EQ(quad* quad);
void generate_IF_NOTEQ(quad* quad);
void generate_IF_GREATER(quad* quad);
void generate_IF_GREATEREQ(quad* quad);
void generate_IF_LESS(quad* quad);
void generate_IF_LESSEQ(quad* quad);
void generate_AND(quad* quad);
void generate_NOT(quad* quad);
void generate_OR(quad* quad);
void generate_PARAM(quad* quad);
void generate_CALL(quad* quad);
void generate_GETRETVAL(quad* quad);
void generate_FUNCSTART(quad* quad);
void generate_RETURN(quad* quad);
void generate_FUNCEND(quad* quad);

unsigned consts_newstring(char* s);
unsigned consts_newnum(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(SymbolTableEntry* sym);

void make_operand(expr* e, vmarg* arg);
void make_numberoperand(vmarg * arg, int val);
void make_booloperand(vmarg * arg, unsigned val);
void make_retvaloperand(vmarg * arg);
void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps(void);
void generate(vmopcode op, quad* quad);
void generate_gen();
unsigned nextinstructionlabel();
void emitInstr(instruction t);
void expandInstrTable();
void printInstructions(void);
void printArg(vmarg* arg);
void printTables();
void printBinary();
void printReadBinary();

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;


FILE *tcode;

long long int magicNumber = 287234993479;

double* numConsts = NULL;
unsigned totalNumConsts = 0;
char** stringConsts = NULL;
unsigned totalStringConsts = 0;;
char** namedLibfuncs = NULL;
unsigned totalNamedLibfuncs = 0;
userfunc* userfuncs = NULL;
unsigned totalUserfuncs = 0;

int currInstruction = 0;
int totalInstr = 0;
instruction* instructions = (instruction*) 0;
int processedquad = 0;

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};

void expandInstrTable(void){
    assert(totalInstr == currInstruction);
    instruction *tmp = (instruction *)malloc(NEW_SIZE);
    if(instructions != NULL){
        memcpy(tmp, instructions, CURR_SIZE);
        free(instructions);
    }
    instructions = tmp;
    totalInstr += EXPAND_SIZE;
}

void emitInstr(instruction t){
    if(currInstruction == totalInstr)   expandInstrTable();

    instruction *newInstr = instructions + currInstruction;
    currInstruction++;

    newInstr->opcode = t.opcode;
    newInstr->result = t.result;
    newInstr->arg1 = t.arg1;
    newInstr->arg2 = t.arg2;
    newInstr->srcLine = t.srcLine;
}

unsigned nextinstructionlabel(){
    return currInstruction;
}

unsigned consts_newstring(char* s){
    if (stringConsts == NULL){
	    stringConsts = (char**)malloc(sizeof(char*));
    }else{
	    stringConsts = (char**)realloc(stringConsts,((totalStringConsts)+1)*sizeof(char*));
    }
    stringConsts[totalStringConsts] = strdup(s);
    totalStringConsts++;
    return totalStringConsts-1;
}

unsigned consts_newnum(double n){
    if (numConsts == NULL){
	    numConsts = (double*)malloc(sizeof(double));
    }else{
	    numConsts = (double*)realloc(numConsts,((totalNumConsts)+1)*sizeof(double));
    }
    numConsts[totalNumConsts] = n;
    totalNumConsts++;
    return totalNumConsts-1;
}

unsigned libfuncs_newused(char* s){
    unsigned i;
    for (i=0 ;i<totalNamedLibfuncs ;i++){
		if (strcmp(namedLibfuncs[i], s) == 0){
            return i;
        }
	}
    if (namedLibfuncs == NULL){
	    namedLibfuncs = (char**)malloc(sizeof(char *));
    }else{
	    namedLibfuncs = (char**)realloc(namedLibfuncs,((totalNamedLibfuncs)+1)*sizeof(char*) );
    }
    namedLibfuncs[totalNamedLibfuncs] = strdup(s);
    totalNamedLibfuncs++;
    return totalNamedLibfuncs-1;
}

unsigned userfuncs_newfunc(SymbolTableEntry* sym){
    unsigned i;
    for (i=0 ;i<totalUserfuncs ;i++){
		if (strcmp(userfuncs[i].id, sym->value.varVal->name) == 0){
            return i;
        }
	}
    if (userfuncs == NULL){
		userfuncs = (userfunc*)malloc(sizeof(userfunc));
    }else{
		userfuncs = (userfunc*)realloc(userfuncs,((totalUserfuncs)+1)*sizeof(userfunc));
    }
    userfuncs[totalUserfuncs].id = strdup(sym->value.varVal->name);
    userfuncs[totalUserfuncs].address = sym->taddress;
    userfuncs[totalUserfuncs].localSize = sym->totalLocals;
    totalUserfuncs++;
    return totalUserfuncs-1;
}

void reset_operand(vmarg* arg){
    arg->type = -1;
}

void add_incomplete_jump(unsigned instrNo, unsigned iaddress){
    
}

void make_operand(expr* e, vmarg* arg){
    if(e != NULL){
        switch (e->type){
            case var_e:
            case tableitem_e:
            case arithexpr_e:
            case boolexpr_e:
            case assignexpr_e:
            case newtable_e:{
                //assert(e->sym);
                arg->val = e->sym->offset;

                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
            }
            case constbool_e: {
                arg->val = e->boolConst;
                arg->type = bool_a;
                break;
            }
            case conststring_e: {
                arg->val = consts_newstring(e->strConst);
                arg->type = string_a;
                break;
            }
            case constint_e: {
                arg->val = consts_newnum(e->intConst);
                arg->type = number_a;
                break;
            }
            case constreal_e: {
                arg->val = consts_newnum(e->realConst);
                arg->type = number_a;
                break;
            }
            case nil_e: arg->type = nil_a; arg->val = 0; break;
            case programfunc_e: {
                arg->type = userfunc_a;
                //arg->val = e->sym->taddress;
                /*alternatively*/
                arg->val = userfuncs_newfunc(e->sym);
                break;
            }
            case libraryfunc_e: {
                arg->type = libfunc_a;
                arg->val = libfuncs_newused(e->sym->value.varVal->name);
                break;
            }
            default: assert(0);
        }
    }else{
        arg->type = -1;
    }
}

void make_numberoperand(vmarg * arg, int val){
    arg->val = consts_newnum(val);
    arg->type = number_a;
}

void make_booloperand(vmarg * arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg * arg){
    arg->type = retval_a;
    arg->val = 0;
}

void patch_incomplete_jumps(void){
    incomplete_jump* x = ij_head;
    while(x != NULL){
        if(x->iaddress = currQuad){
            instructions[x->instrNo].result.val = currInstruction;
        }else{
            instructions[x->instrNo].result.val = quads[x->iaddress].taddress;
        }
        x = x->next;
    }
}

void generate(vmopcode op, quad* quad){
    instruction t;
    t.opcode = op;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &(t.arg1));
    make_operand(quad->arg2, &(t.arg2));
    make_operand(quad->result, &(t.result));
    quad->taddress = nextinstructionlabel();
    emitInstr(t);
}

int currprocessedquad(){
    return processedquad;
}

void generate_gen(){
    unsigned i;
    for(i=1; i<currQuad;i++){
        processedquad++;
        (*generators[quads[i].op])(quads+i);
    }
}

void generate_ADD(quad* quad){
    generate(add_v, quad);
}

void generate_SUB(quad* quad){
    generate(sub_v, quad);
}

void generate_MUL(quad* quad){
    generate(mul_v, quad);
}

void generate_DIV(quad* quad){
    generate(div_v, quad);
}

void generate_MOD(quad* quad){
    generate(mod_v, quad);
}

void generate_UMINUS(quad* quad){
    instruction t;
    t.opcode = mul_v;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &t.arg1);
    make_numberoperand(&t.arg2, -1);
    make_operand(quad->result, &t.result);
    emitInstr(t);
}

void generate_NEWTABLE(quad* quad){
    generate(newtable_v, quad);
}

void generate_TABLEGETELEM(quad* quad){
    generate(tablegetelem_v, quad);
}

void generate_TABLESETELEM(quad* quad){
    generate(tablesetelem_v, quad);
}

void generate_ASSIGN(quad* quad){
    generate(assign_v, quad);
}

void generate_NOP(){
    instruction t;
    t.opcode = nop_v;
    emitInstr(t);
}

void generate_relational(vmopcode op, quad* quad){
    instruction t;
    t.opcode = op;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &(t.arg1));
    make_operand(quad->arg2, &(t.arg2));

    t.result.type = label_a;
    if(quad->label < currprocessedquad()){
        t.result.val = quads[quad->label].taddress;
    }/*else{
        add_incomplete_jump(nextinstructionlabel(), quad->label);
    }*/

    quad->taddress = nextinstructionlabel();
    emitInstr(t);
}

void generate_JUMP(quad* quad){
    generate_relational(jump_v, quad);
}

void generate_IF_EQ(quad* quad){
    generate_relational(jeq_v, quad);
}

void generate_IF_NOTEQ(quad* quad){
    generate_relational(jne_v, quad);
}

void generate_IF_GREATER(quad* quad){
    generate_relational(jgt_v, quad);
}

void generate_IF_GREATEREQ(quad* quad){
    generate_relational(jge_v, quad);
}

void generate_IF_LESS(quad* quad){
    generate_relational(jlt_v, quad);
}

void generate_IF_LESSEQ(quad* quad){
    generate_relational(jle_v, quad);
}

void generate_AND(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;

    t.opcode = jeq_v;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 4;
    emitInstr(t);

    make_operand(quad->arg2, &t.arg1);
    t.result.val = nextinstructionlabel() + 3;
    emitInstr(t);

    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emitInstr(t);

    t.opcode = jump_v;
    t.srcLine = quad->line;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emitInstr(t);

    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emitInstr(t);
}

void generate_NOT(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;

    t.opcode = jeq_v;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 3;
    emitInstr(t);

    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emitInstr(t);

    t.opcode = jump_v;
    t.srcLine = quad->line;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emitInstr(t);

    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emitInstr(t);
}

void generate_OR(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;

    t.opcode = jeq_v;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &t.arg1);
    make_booloperand(&t.arg2, 1);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 4;
    emitInstr(t);

    make_operand(quad->arg2, &t.arg1);
    t.result.val = nextinstructionlabel() + 3;
    emitInstr(t);

    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emitInstr(t);

    t.opcode = jump_v;
    t.srcLine = quad->line;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emitInstr(t);

    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emitInstr(t);
}

void generate_PARAM(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_v;
    t.srcLine = quad->line;
    make_operand(quad->result, &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    emitInstr(t);
}

void generate_CALL(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = call_v;
    t.srcLine = quad->line;
    make_operand(quad->result, &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    emitInstr(t);
}

void generate_GETRETVAL(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_operand(quad->result, &t.result);
    make_retvaloperand(&t.arg1);
    //reset_operand(&t.arg2);
    emitInstr(t);
}

void generate_FUNCSTART(quad* quad){
    SymbolTableEntry* f;
    instruction t;
    //f = quad->result->sym;
    f = quad->arg1->sym;
    f->taddress = nextinstructionlabel();
    quad->taddress = nextinstructionlabel();

    /*userfunctions->add(f->id, f->taddress, f->totalLocals);
    push(funcstack, f);*/

    t.opcode = funcenter_v;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &t.arg1);
    reset_operand(&t.arg2);
    reset_operand(&t.result);
    emitInstr(t);
}

void generate_RETURN(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    t.srcLine = quad->line;
    make_retvaloperand(&t.result);
    make_operand(quad->result, &t.arg1);
    reset_operand(&t.arg2);
    emitInstr(t);
    /*f = top(funcstack);
    append(f->returnList, nextinstructionlabel());*/


}

void generate_FUNCEND(quad* quad){
    //f = pop(funcstack);
    //backpatach(f->returnList, nextinstructionlabel());

    quad->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = funcexit_v;
    t.srcLine = quad->line;
    make_operand(quad->arg1, &t.arg1);
    reset_operand(&t.arg2);
    reset_operand(&t.result);
    emitInstr(t);
}

void printInstructions(void){
    int j=0;
	instruction* tmp = instructions;

    tcode = fopen("t_code.txt", "w");
	
    printTables();

	while(j < currInstruction){
        tmp = instructions + j;
		printf("\n\033[1;36m%d: \033[0m",j);
        printf("\033[1;32m");
        fprintf(tcode, "%d: ",j);
        if(tmp->opcode == assign_v){
            printf("ASSIGN  ");
            fprintf(tcode, "ASSIGN  ");
        }else if(tmp->opcode == add_v){
            printf("ADD  ");
            fprintf(tcode, "ADD  ");
        }else if(tmp->opcode == sub_v){
            printf("SUB  ");
            fprintf(tcode, "SUB  ");
        }else if(tmp->opcode == mul_v){
            printf("MUL  ");
            fprintf(tcode, "MUL  ");
        }else if(tmp->opcode == div_v){
            printf("DIV  ");
            fprintf(tcode, "DIV  ");
        }else if(tmp->opcode == mod_v){
            printf("MOD  ");
            fprintf(tcode, "MOD  ");
        }else if(tmp->opcode == uminus_v){
            printf("UMINUS  ");
            fprintf(tcode, "UMINUS  ");
        }else if(tmp->opcode == and_v){
            printf("AND  ");
            fprintf(tcode, "AND  ");
        }else if(tmp->opcode == or_v){
            printf("OR  ");
            fprintf(tcode, "OR  ");
        }else if(tmp->opcode == not_v){
            printf("NOT  ");
            fprintf(tcode, "NOT  ");
        }else if(tmp->opcode == jeq_v){
            printf("JEQ  ");
            fprintf(tcode, "JEQ  ");
        }else if(tmp->opcode == jne_v){
            printf("JNE  ");
            fprintf(tcode, "JNE  ");
        }else if(tmp->opcode == jle_v){
            printf("JLE  ");
            fprintf(tcode, "JLE  ");
        }else if(tmp->opcode == jge_v){
            printf("JGE  ");
            fprintf(tcode, "JGE  ");
        }else if(tmp->opcode == jlt_v){
            printf("JLT  ");
            fprintf(tcode, "JLT  ");
        }else if(tmp->opcode == jgt_v){
            printf("JGT  ");
            fprintf(tcode, "JGT  ");
        }else if(tmp->opcode == pusharg_v){
            printf("PUSHARG  ");
            fprintf(tcode, "PUSHARG  ");
        }else if(tmp->opcode == call_v){
            printf("CALLFUNC  ");
            fprintf(tcode, "CALLFUNC  ");
        }else if(tmp->opcode == funcenter_v){
            printf("ENTERFUNC  ");
            fprintf(tcode, "ENTERFUNC  ");
        }else if(tmp->opcode == funcexit_v){
            printf("EXITFUNC  ");
            fprintf(tcode, "EXITFUNC  ");
        }else if(tmp->opcode == newtable_v){
            printf("NEWTABLE  ");
            fprintf(tcode, "NEWTABLE  ");
        }else if(tmp->opcode == tablegetelem_v){
            printf("TABLEGETELEM  ");
            fprintf(tcode, "TABLEGETELEM  ");
        }else if(tmp->opcode == tablesetelem_v){
            printf("TABLESETELEM  ");
            fprintf(tcode, "TABLESETELEM  ");
        }else if(tmp->opcode == nop_v){
            printf("NOP  ");
            fprintf(tcode, "NOP  ");
        }else if(tmp->opcode == jump_v){
            printf("JUMP  ");
            fprintf(tcode, "JUMP  ");
        }
        printf("\033[0m");
        if(&tmp->result){
            printArg(&tmp->result);
        }
        if(&tmp->arg1){
            printArg(&tmp->arg1);
        }      
        if(&tmp->arg2){
            printArg(&tmp->arg2);
        }
        printf("\033[1;36m[line %d]\033[0m",tmp->srcLine);
        fprintf(tcode, "[line %d]\n",tmp->srcLine);
        j++;
    }
    printf("\n");
    fprintf(tcode, "\n");

    fclose(tcode);
}

void printArg(vmarg* arg){
    if(arg->type == label_a){
        printf("0%d(label),%d  ", arg->type , arg->val);
        fprintf(tcode, "0%d(label),%d  ", arg->type , arg->val);
    }else if(arg->type == global_a){
        printf("0%d(global),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(global),%d  ", arg->type, arg->val);
    }else if(arg->type == formal_a){
        printf("0%d(formal),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(formal),%d  ", arg->type, arg->val);
    }else if(arg->type == local_a){
        printf("0%d(local),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(local),%d  ", arg->type, arg->val);
    }else if(arg->type == number_a){
        printf("0%d(num),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(num),%d  ", arg->type, arg->val);
    }else if(arg->type == string_a){
        printf("0%d(string),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(string),%d  ", arg->type, arg->val);
    }else if(arg->type == bool_a){
        printf("0%d(boolean),%d:", arg->type, arg->val);
        fprintf(tcode, "0%d(boolean),%d:", arg->type, arg->val);
        if(arg->val == 1){
            printf("true  ");
            fprintf(tcode,"true  ");
        }else{
            printf("false  ");
            fprintf(tcode,"false  ");
        }
    }else if(arg->type == nil_a){
        printf("0%d(nil),%d:nil  ", arg->type, arg->val);
        fprintf(tcode, "0%d(nil),%d:nil  ", arg->type, arg->val);
    }else if(arg->type == userfunc_a){
        printf("0%d(userfunc),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(userfunc),%d  ", arg->type, arg->val);
    }else if(arg->type == libfunc_a){
        printf("0%d(libfunc),%d  ", arg->type, arg->val);
        fprintf(tcode, "0%d(libfunc),%d  ", arg->type, arg->val);
    }else if(arg->type == retval_a){
        printf("%d(retval)  ", arg->type); 
        fprintf(tcode, "%d(retval)  ", arg->type); 
    }
}

void printTables(){
    unsigned i=0;
    printf("---------NumConsts---------\n");
    fprintf(tcode, "---------NumConsts---------\n");
    for(i=0;i<totalNumConsts;i++){
        printf("numConsts[%d] = %f\n", i, numConsts[i]);
        fprintf(tcode, "numConsts[%d] = %f\n", i, numConsts[i]);
    }
    printf("---------StringConsts---------\n");
    fprintf(tcode, "---------StringConsts---------\n");
    for(i=0;i<totalStringConsts;i++){
        printf("stringConsts[%d] = %s\n", i, stringConsts[i]);
        fprintf(tcode, "stringConsts[%d] = %s\n", i, stringConsts[i]);
    }
    printf("---------LibFuncs---------\n");
    fprintf(tcode, "---------LibFuncs---------\n");
    for(i=0;i<totalNamedLibfuncs;i++){
        printf("namedLibfuncs[%d] = %s\n", i, namedLibfuncs[i]);
        fprintf(tcode, "namedLibfuncs[%d] = %s\n", i, namedLibfuncs[i]);
    }
    printf("---------UserFuncs---------\n");
    fprintf(tcode, "---------UserFuncs---------\n");
    for(i=0;i<totalUserfuncs;i++){
        printf("userfuncs[%d].id = %s\n", i, userfuncs[i].id);
        printf("userfuncs[%d].address = %u\n", i, userfuncs[i].address);
        printf("userfuncs[%d].localSize = %u\n", i, userfuncs[i].localSize);
        fprintf(tcode, "userfuncs[%d].id = %s\n", i, userfuncs[i].id);
        fprintf(tcode, "userfuncs[%d].address = %u\n", i, userfuncs[i].address);
        fprintf(tcode, "userfuncs[%d].localSize = %u\n", i, userfuncs[i].localSize);
    }
    printf("\n");
    fprintf(tcode, "\n");
}

void patchdemjumps(){
    quad *tmp;
    instruction *instr;
    int i=1;
    unsigned taddr;


    while(i<currQuad){
        tmp = quads + i;
        if(tmp->op == jump || tmp->op == if_eq || tmp->op == if_noteq 
            || tmp->op == if_lesseq || tmp->op == if_greatereq 
            || tmp->op == if_less || tmp->op == if_greater){
            instr = instructions + tmp->taddress; 
            
            tmp = quads + tmp->label;
            taddr = tmp->taddress;
            if(instr->result.val != 0){
                instr->result.val = taddr;
                if(instr->result.val == 0){
                    instr->result.val = currInstruction;
                }
            }
            if(tmp->op == jump){
                instr->arg1.type = -1;
                instr->arg2.type = -1;
            }
        }
        i++;
    }
}

void printBinary(){
    FILE *binary;
    binary = fopen("binary.bin", "wb");
    unsigned i;
    int j=0;
    int argSelector=0;
    char terminator = '\0';
    

    fwrite(&magicNumber, sizeof(long long int), 1, binary);

    fwrite(&totalNumConsts, sizeof(unsigned), 1, binary);
    for(i=0;i<totalNumConsts;i++){
        fwrite(&numConsts[i], sizeof(double), 1, binary);
    }

    fwrite(&totalStringConsts, sizeof(unsigned), 1, binary);
    for(i=0; i<totalStringConsts; i++){
        for(j=0; j<strlen(stringConsts[i]); j++){
            fwrite(&stringConsts[i][j], sizeof(char), 1, binary);
        }
        fwrite(&terminator, sizeof(char), 1, binary);
    }

    fwrite(&totalNamedLibfuncs, sizeof(unsigned), 1, binary);
    for(i=0; i<totalNamedLibfuncs; i++){
        for(j=0; j<strlen(namedLibfuncs[i]); j++){
            fwrite(&namedLibfuncs[i][j], sizeof(char), 1, binary);
        }
        fwrite(&terminator, sizeof(char), 1, binary);
    }


    fwrite(&totalUserfuncs, sizeof(unsigned), 1, binary);
    for(i=0; i<totalUserfuncs; i++){
        for(j=0; j<strlen(userfuncs[i].id); j++){
            fwrite(&userfuncs[i].id[j], sizeof(char), 1, binary);
        }
        fwrite(&terminator, sizeof(char), 1, binary);
        fwrite(&userfuncs[i].address, sizeof(unsigned), 1, binary);
        fwrite(&userfuncs[i].localSize, sizeof(unsigned), 1, binary);
    }

    
    fwrite(&currInstruction, sizeof(unsigned), 1, binary);
    instruction *tmp;
    for(i=0; i<currInstruction; i++){
        tmp = instructions + i;
        
        argSelector = 0;
        if(tmp->result.type != -1)
            argSelector+=4;
        if(tmp->arg1.type != -1)
            argSelector+=2;
        if(tmp->arg2.type != -1)
            argSelector+=1;
        
        fwrite(&argSelector, sizeof(int), 1, binary);

        fwrite(&tmp->opcode, sizeof(vmopcode), 1, binary);
        if(tmp->result.type != -1){
            fwrite(&tmp->result.type, sizeof(vmarg_t), 1, binary);
            fwrite(&tmp->result.val, sizeof(unsigned), 1, binary);
        }
        if(tmp->arg1.type != -1){
            fwrite(&tmp->arg1.type, sizeof(vmarg_t), 1, binary);
            fwrite(&tmp->arg1.val, sizeof(unsigned), 1, binary);
        }
        if(tmp->arg2.type != -1){
            fwrite(&tmp->arg2.type, sizeof(vmarg_t), 1, binary);
            fwrite(&tmp->arg2.val, sizeof(unsigned), 1, binary);
        }
    }

    fclose(binary);
}


#endif
