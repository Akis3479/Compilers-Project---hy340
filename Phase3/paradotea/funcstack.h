#include <stdio.h>
#include <stdlib.h>

#ifndef _FUNCSTACK_H_
#define _FUNCSTACK_H_

typedef struct funcStack { 
    int func_start_label;
    struct funcStack* next; 
}funcStack; 

struct funcStack* newNode(int data) 
{
    struct funcStack* stackNode = (funcStack *)malloc(sizeof(funcStack)); 
    stackNode->func_start_label = data; 
    stackNode->next = NULL; 
    return stackNode; 
}
  
int isEmptyFuncStack(struct funcStack* root) 
{ 
    return !root; 
} 

int topFuncStack(struct funcStack* root) 
{ 
    if (isEmptyFuncStack(root)) 
        return -1; 
    return root->func_start_label; 
} 
  
void pushFuncStack(struct funcStack** root, int data) 
{ 
    struct funcStack* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode;
} 
  
int popFuncStack(struct funcStack** root) 
{ 
    if (isEmptyFuncStack(*root)) 
        return -1; 
    struct funcStack* temp = *root; 
    *root = (*root)->next; 
    int popped = temp->func_start_label; 
    free(temp); 
  
    return popped; 
} 



#endif