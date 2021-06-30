/* 
    This library provides some stack and list functions and also a structure for comments.
*/

struct Comment{
    int token_no;
    int start_line;
    int end_line;
    char* comment_type;
    char* final_content;
    struct Comment *next;
};

// A structure to represent a stack 
struct Stack {
    int top; 
    unsigned capacity; 
    struct Comment* array; 
}; 
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity)
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (struct Comment*)malloc(stack->capacity * sizeof(struct Comment)); 
    return stack; 
} 

// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, struct Comment item) 
{ 
    stack->array[++stack->top] = item;
} 
  
// Function to remove an item from stack.  It decreases top by 1 
struct Comment pop(struct Stack* stack) 
{  
    return stack->array[stack->top--]; 
} 

// Stack is empty when top is equal to -1 
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
}

/* Function to insert in a sorted list */
void sortedInsert(struct Comment** head_ref, struct Comment* new_node) 
{ 
    struct Comment* current; 
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->token_no >= new_node->token_no) 
    { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
        current = *head_ref; 
        while (current->next!=NULL && 
               current->next->token_no < new_node->token_no) 
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 
