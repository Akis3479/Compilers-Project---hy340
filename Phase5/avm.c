#include "AlphaStructures.h"
#include "readBinary.h"
#include "avm.h"
#include <stdlib.h>
#include<string.h>

typedef enum var_type{
	noumero,
	alpharithmitiko,
    boolean
}var_type;

typedef struct metavliti{
	var_type type;
	union val{
		double numVal;
		char* strVal;
        double boolVal;
	}val;
}metavliti;

int execFinished();
void execute();
double exec_arthm();

metavliti* variables;
metavliti* args;
int a=0; // num of args


void main(int argc, char *argv[])
{
    printf("\033[1;31m------------------------------PhaseE------------------------------\033[0m\n");
    if(argc == 2){
        printReadBinary(argv[1]);
    }else if(argc == 3){
        printReadBinary(argv[1]);
        if(strcmp(argv[2], "-p") == 0)
            printTheFuckingBinary();
    }else{
        printf("input Format: avm BinaryFilePath\n");
        printf("input Format: avm BinaryFilePath -print (to print the binary file)\n");
    }

    printf("\033[1;31m\t\t\t (Code execution)\033[0m\n");
    variables = (metavliti*) malloc (instrnum * 3* sizeof(metavliti));
    args = (metavliti*) malloc (instrnum * sizeof(metavliti));
    
    code = ins;
    pc = 0;
    codeSize = instrnum;
    top = topsp = AVM_STACKSIZE - (str+num) -1;
    avm_initstack();
    execute();

    // Garbage Collection
    // freeTables();
}

int execFinished(){
    if(pc >= instrnum)
        return 1;
    else
        return 0;
}

void execute(){
    int i=0;

    for(i=0; i<instrnum; i++){
        switch(ins[i].opcode){
            case assign_v: {
                if(ins[i].result.type == global_a ){
                    if(ins[i].arg1.type == 1){
                        variables[ins[i].result.val] = variables[ins[i].arg1.val];                   
                    }else if(ins[i].arg1.type == 4){
						variables[ins[i].result.val].type = noumero;
                        variables[ins[i].result.val].val.numVal = arrayNum[ins[i].arg1.val];
                    }else if(ins[i].arg1.type == 10){
                        //assign retval
						//printf("retval\n");
						continue;
                    }else if(ins[i].arg1.type == 5){
						//strings
						variables[ins[i].result.val].type = alpharithmitiko;
                        variables[ins[i].result.val].val.strVal = strdup(arrayString[ins[i].arg1.val]);
					}else if(ins[i].arg1.type == 6){
                        variables[ins[i].result.val].type = boolean;
                        variables[ins[i].result.val].val.boolVal = ins[i].arg1.val;
                    }
                }
                break;
            }
            case add_v:
            case sub_v:
            case mul_v:
            case div_v:
            case mod_v:{
				variables[ins[i].result.val].type = noumero;
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                    variables[ins[i].result.val].val.numVal = exec_arthm(ins[i].opcode, variables[ins[i].arg1.val].val.numVal, variables[ins[i].arg2.val].val.numVal);
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    variables[ins[i].result.val].val.numVal = exec_arthm(ins[i].opcode, variables[ins[i].arg1.val].val.numVal, arrayNum[ins[i].arg2.val]);
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    variables[ins[i].result.val].val.numVal = exec_arthm(ins[i].opcode, arrayNum[ins[i].arg1.val], variables[ins[i].arg2.val].val.numVal);
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    variables[ins[i].result.val].val.numVal = exec_arthm(ins[i].opcode, arrayNum[ins[i].arg1.val], arrayNum[ins[i].arg2.val]);
                }
                break;
            }
            case call_v:{
                int j;
                if(ins[i].result.type == 9){
                    if(strcmp(arrayLibFun[ins[i].result.val], "print") == 0){
                        for(j=a-1; j>=0; j--){
                            if(args[j].type == noumero){
                                if((int)args[j].val.numVal == args[j].val.numVal)
								    printf("%d", (int)args[j].val.numVal);
                                else
								    printf("%.2f", args[j].val.numVal);

                            }
							else if(args[j].type == alpharithmitiko)
								printf("%s", args[j].val.strVal);
                        }
                    }
                }
                for(a=0; a<instrnum;a++){
                    if(args[a].type == alpharithmitiko)
                        args[a].val.strVal = strdup("");
                }
                a=0;
                break;
            }
            case pusharg_v:{
                if(ins[i].result.type == 5){
                    variables[ins[i].result.val].type = alpharithmitiko;
                    variables[ins[i].result.val].val.strVal = strdup(arrayString[ins[i].result.val]);
                }else if(ins[i].result.type == 4){
                    variables[ins[i].result.val].type = noumero;
                    variables[ins[i].result.val].val.numVal = arrayNum[ins[i].result.val];
                }
                
                args[a++] = variables[ins[i].result.val];
                break;
            }
            case jump_v:{
                if(ins[i].result.type == label_a){
                    i = ins[i].result.val -1;
                }
                break;
            }
            case jeq_v:{
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                     if(variables[ins[i].arg1.val].val.numVal == variables[ins[i].arg2.val].val.numVal)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    if(variables[ins[i].arg1.val].val.numVal == arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    if(variables[ins[i].arg2.val].val.numVal == arrayNum[ins[i].arg1.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    if(arrayNum[ins[i].arg1.val] == arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 6){
                    if(variables[ins[i].arg1.val].val.numVal == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 6){
                    if(arrayNum[ins[i].arg1.val] == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }
                break;
            }
            case jlt_v:{
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                     if(variables[ins[i].arg1.val].val.numVal < variables[ins[i].arg2.val].val.numVal)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    if(variables[ins[i].arg1.val].val.numVal < arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    if(variables[ins[i].arg2.val].val.numVal < arrayNum[ins[i].arg1.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    if(arrayNum[ins[i].arg1.val] < arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 6){
                    if(variables[ins[i].arg1.val].val.numVal == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }
                break;
            }
            case jgt_v:{
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                     if(variables[ins[i].arg1.val].val.numVal  > variables[ins[i].arg2.val].val.numVal)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    if(variables[ins[i].arg1.val].val.numVal  > arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    if(variables[ins[i].arg2.val].val.numVal  > arrayNum[ins[i].arg1.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    if(arrayNum[ins[i].arg1.val]  > arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 6){
                    if(variables[ins[i].arg1.val].val.numVal == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }
                break;
            }
            case jge_v:{
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                     if(variables[ins[i].arg1.val].val.numVal  >= variables[ins[i].arg2.val].val.numVal)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    if(variables[ins[i].arg1.val].val.numVal  >= arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    if(variables[ins[i].arg2.val].val.numVal  >= arrayNum[ins[i].arg1.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    if(arrayNum[ins[i].arg1.val]  >= arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 6){
                    if(variables[ins[i].arg1.val].val.numVal == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }
                break;
            }
            case jle_v:{
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                     if(variables[ins[i].arg1.val].val.numVal <= variables[ins[i].arg2.val].val.numVal)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    if(variables[ins[i].arg1.val].val.numVal <= arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    if(variables[ins[i].arg2.val].val.numVal <= arrayNum[ins[i].arg1.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    if(arrayNum[ins[i].arg1.val] <= arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 6){
                    if(variables[ins[i].arg1.val].val.numVal == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }
                break;
            }
            case jne_v:{
                if(ins[i].arg1.type == 1 && ins[i].arg2.type == 1){
                     if(variables[ins[i].arg1.val].val.numVal != variables[ins[i].arg2.val].val.numVal)
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 4){
                    if(variables[ins[i].arg1.val].val.numVal != arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 1){
                    if(variables[ins[i].arg2.val].val.numVal != arrayNum[ins[i].arg1.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 4 && ins[i].arg2.type == 4){
                    if(arrayNum[ins[i].arg1.val] != arrayNum[ins[i].arg2.val])
                        i = ins[i].result.val -1;
                }else if(ins[i].arg1.type == 1 && ins[i].arg2.type == 6){
                    if(variables[ins[i].arg1.val].val.numVal == ins[i].arg2.val)
                        i = ins[i].result.val -1;
                }
                break;
            }
            default: printf("Gamwwww\n"); break;
        }
    }
}

double exec_arthm(vmopcode type, double x, double y){
    switch(type){
        case add_v:{
            return x+y;
            break;
        }
        case sub_v:{
            return x-y;
            break;
        }
        case mul_v:{
            return x*y;
            break;
        }
        case div_v:{
            if(y!=0){
                return x/y;
            }else{
                fprintf(stderr, "Division by zero.\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case mod_v:{
            return (int)x%(int)y;
            break;
        }
        default: exit(EXIT_FAILURE);
    }
}































// void execute_instr(){
//     int i=0;
//     for(i=0; i<instrnum; i++){
//         switch(ins[i].opcode){
//             case assign_v: {
//                 if(ins[i].result.type == global_a){
                    
//                 }
//                 break;
//             }
//             case add_v:
//             case sub_v:
//             case mul_v:
//             case div_v:
//             case call_v:
//             case pusharg_v:
//         }
//     }
// }
