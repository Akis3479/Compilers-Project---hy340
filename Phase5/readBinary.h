#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *binary;
long long int magic;

unsigned i;
unsigned num,str,lib,user, instrnum;
int argSelector;
double *arrayNum;
char** arrayString;
char** arrayLibFun;
userfunc* arrayUserFun;
instruction* ins;

// instruction *headOfListOfInstructions = NULL;


void printReadBinary(char* path){

    binary = fopen(path, "rb");

    fread(&magic, sizeof(long long int), 1, binary);
    if(magic != 287234993479){
        fprintf(stderr,"Binary file not supported. Exiting...\n");
        return;
    }

    fread(&num, sizeof(unsigned), 1, binary);
    arrayNum = (double*)malloc(num*sizeof(double));
    for(i=0;i<num;i++){
        fread(&arrayNum[i], sizeof(double), 1, binary);
    }
    
    fread(&str, sizeof(unsigned), 1, binary);
    arrayString = (char **)malloc(str * sizeof(char*));
    char* inString = malloc(1000000);
    char stringchar[2];
    char c;
    stringchar[1] = '\0';

    for(i=0; i<str; i++){
        fread(&c, sizeof(char), 1, binary);
        while(c != '\0'){
            stringchar[0] = c;
            inString = strcat(inString, stringchar);
            fread(&c, sizeof(char), 1, binary);
        }
        arrayString[i] = strdup(inString);
        inString = strdup("");
    }

    fread(&lib, sizeof(unsigned), 1, binary);
    arrayLibFun = (char**)malloc(lib*sizeof(char*));
    for(i=0; i<lib; i++){
        fread(&c, sizeof(char), 1, binary);
        while(c != '\0'){
            stringchar[0] = c;
            inString = strcat(inString, stringchar);
            fread(&c, sizeof(char), 1, binary);
        }
        arrayLibFun[i] = strdup(inString);
        inString = strdup("");
    }

    fread(&user, sizeof(unsigned), 1, binary);
    arrayUserFun = (userfunc *)malloc(user*sizeof(userfunc));
    for(i=0;i<user;i++){
    // printf("user=%u\n",user);
        fread(&c, sizeof(char), 1, binary);
        while(c != '\0'){
            stringchar[0] = c;
            inString = strcat(inString, stringchar);
            fread(&c, sizeof(char), 1, binary);
        }
        arrayUserFun[i].id = strdup(inString);
        inString = strdup("");

        fread(&arrayUserFun[i].address, sizeof(unsigned), 1, binary);
        fread(&arrayUserFun[i].localSize, sizeof(unsigned), 1, binary);
    }
    
    fread(&instrnum, sizeof(unsigned), 1, binary);

    ins = (instruction *)malloc(instrnum*sizeof(instruction));
    for(i=0; i<instrnum; i++){
        fread(&argSelector, sizeof(int), 1, binary);
        
        fread(&ins[i].opcode, sizeof(vmopcode), 1, binary);
    
        ins[i].result.type = -1;
        ins[i].arg1.type = -1;
        ins[i].arg2.type = -1;

        if(argSelector==0){

        }else if(argSelector == 1){
            fread(&ins[i].arg2.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg2.val, sizeof(unsigned), 1, binary);
        }else if(argSelector == 2){
            fread(&ins[i].arg1.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg1.val, sizeof(unsigned), 1, binary);
        }else if(argSelector == 3){
            fread(&ins[i].arg1.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg1.val, sizeof(unsigned), 1, binary);
            fread(&ins[i].arg2.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg2.val, sizeof(unsigned), 1, binary);
        }else if(argSelector == 4){
            fread(&ins[i].result.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].result.val, sizeof(unsigned), 1, binary);
        }else if(argSelector == 5){
            fread(&ins[i].result.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].result.val, sizeof(unsigned), 1, binary);
            fread(&ins[i].arg2.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg2.val, sizeof(unsigned), 1, binary);
        }else if(argSelector == 6){
            fread(&ins[i].result.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].result.val, sizeof(unsigned), 1, binary);
            fread(&ins[i].arg1.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg1.val, sizeof(unsigned), 1, binary);
        }else if(argSelector == 7){
            fread(&ins[i].result.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].result.val, sizeof(unsigned), 1, binary);
            fread(&ins[i].arg1.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg1.val, sizeof(unsigned), 1, binary);
            fread(&ins[i].arg2.type, sizeof(vmarg_t), 1, binary);
            fread(&ins[i].arg2.val, sizeof(unsigned), 1, binary);
        }      
    }

    free(inString);
    fclose(binary);
}

void freeTables(){
    free(arrayNum);
    free(arrayString);
    free(arrayLibFun);
    free(arrayUserFun);
}

void printTheFuckingBinary(){
    printf("\n");
    printf("magic=%lld\n\n",magic);
    
    printf("\033[1;31m\t\t     (Tables from binary file):\033[0m\n");
    printf("Const Numbers: %d\n",num);
    for(i=0;i<num;i++){
        printf("\t%d:%f\n", i, arrayNum[i]);
    }
    
    printf("\nConst Strings: %d\n",str);
    for(i=0; i<str; i++){
        printf("\t%d:%s\n", i, arrayString[i]);
    }

    printf("\nLibrary Functions: %d\n",lib);
    for(i=0; i<lib; i++){
        printf("\t%d:%s\n", i, arrayLibFun[i]);
    }

    printf("\nUser Functions: %d\n",user);
    for(i=0;i<user;i++){
        printf("\t%d:%s", i, arrayUserFun[i].id);
        printf(" %d",arrayUserFun[i].address);
        printf(" %d\n",arrayUserFun[i].localSize);
    }
    printf("\n\033[1;31m\t\t   (Instructions from binary file):\033[0m\n");
    printf("\nInstructions: %d\n", instrnum);
    printf("\tOpcode\t|Result |Arg1\t|Arg2\n");
    for(i=0; i<instrnum; i++){
        printf("%d:\t%d\t|", i, ins[i].opcode);

        if(ins[i].result.type != -1){
            printf(" %d:",ins[i].result.type);
            printf(" %d\t|",ins[i].result.val);
        }
        if(ins[i].arg1.type != -1){
            printf(" %d:",ins[i].arg1.type);
            printf(" %d\t|",ins[i].arg1.val);
        }
        if(ins[i].arg2.type != -1){
            printf(" %d:",ins[i].arg2.type);
            printf(" %d\t",ins[i].arg2.val);
        }

        printf("\n");
            
    }

}
