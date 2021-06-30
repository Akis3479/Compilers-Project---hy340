#include "symtable.h"

#ifndef _RETURNLIST_FUNCTIONSTACK_H_
#define _RETURNLIST_FUNCTIONSTACK_H_

ReturnListFuncs *returnListFuncsHead = NULL;
FunctionStack *FunctionStackHead = NULL;


typedef struct ReturnListFuncs{
    unsigned retlabel;
    struct ReturnListFuncs *next;
}ReturnListFuncs;

typedef struct FunctionStack{
    SymbolTableEntry *symbol;
    ReturnListFuncs *retlist;
    struct FunctionStack *next;
}FunctionStack;


void insertRetListTcode(unsigned label){
    ReturnListFuncs *tmp;
    ReturnListFuncs *tmp2;

    if(returnListFuncsHead == NULL){
        returnListFuncsHead = (returnListFuncsHead *)malloc(sizeof(returnListFuncsHead));
        returnListFuncsHead->retlabel = label;
        returnListFuncsHead->next = NULL;
    }else{
        tmp = returnListFuncsHead;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp2 = (returnListFuncsHead *)malloc(sizeof(returnListFuncsHead));
        tmp2->retlabel = label;
        tmp2->next = NULL;
        tmp->next = tmp2;
    }
}

void pop();

void push();

void top();









#endif