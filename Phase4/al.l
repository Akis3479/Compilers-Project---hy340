%{
    #include "Utilities.h"
    #include <stdlib.h>
    #include "y.tab.h"
    #define STACK_SIZE 100

    int token_ctr = 0;
    int comment_ctr = 0;

    struct alpha_token_t {
        int lineno;
        int token_num;
        char* content;
        char* category;
        char* value;
        char* type;
        struct alpha_token_t *next;
    };

    struct Comment *comment_head = NULL;

    struct alpha_token_t *head = NULL;
    struct alpha_token_t *tmp = NULL;

    void insert_token(char* cat, char* val, char* cont, char* type){
        struct alpha_token_t* newnode = (struct alpha_token_t *)malloc(sizeof(struct alpha_token_t));
        newnode->lineno = yylineno;
        newnode->token_num = token_ctr;
        newnode->content = strdup(cont);
        newnode->category = strdup(cat);
        newnode->value = strdup(val);
        newnode->type = strdup(type);
        newnode->next = NULL;

        if(head == NULL){
            head = newnode;
            tmp = newnode;
        }else{
            tmp->next = newnode;
            tmp = tmp->next;
        }
    }

    void print_token_list(){
        struct alpha_token_t *curr = head;
        fprintf(stdout, "\n-----------------    Lexical Analysis    -----------------\n\n");
        while(curr!=NULL){
            if(strcmp(curr->category, "ID") || strcmp(curr->category, "STRING")){
                fprintf(stdout, "%d:  #%d  \"%s\"  %s  \"%s\"  <-%s\n", curr->lineno, curr->token_num, curr->content, curr->category, curr->value, curr->type);
            }else
                fprintf(stdout, "%d:  #%d  \"%s\"  %s  %s   <-%s\n", curr->lineno, curr->token_num, curr->content, curr->category, curr->value, curr->type);
            curr = curr->next;
        }
    }

   struct Stack* stack;

    // buffer for reading string content
    char *buf;
    char *s;
    int n=0;

%}

%option noyywrap
%option yylineno

IF                      "if"
ELSE                    "else"
WHILE                   "while"
FOR                     "for"
FUNCTION                "function"
RETURN                  "return"
BREAK                   "break"
CONTINUE                "continue"
AND                     "and"
OR                      "or"
NOT                     "not"
LOCAL                   "local"
TRUE                    "true"
FALSE                   "false"
NIL                     "nil"

NOT_EQUALS              "!="
EQUALS                  "=="
ASSIGN                  "="
PLUS_PLUS               "++"
MINUS_MINUS             "--"
PLUS                    "+"
MINUS                   "-"
MULTI                   "*"
DIV                     "/"
MOD                     "%"
GREATER_OR_EQUAL        ">="
LESS_OR_EQUAL           "<="
GREATER_THAN            ">"
LESS_THAN               "<"

LEFT_CURLY              "{"
RIGHT_CURLY             "}"
LEFT_BRACKET            "["
RIGHT_BRACKET           "]"
LEFT_PARENTHESIS        "("
RIGHT_PARENTHESIS       ")"
SEMICOLON               ";"
COMMA                   ","
COLON                   ":"
SCOPE                   "::"
DOT                     "."
DOUBLE_DOT              ".."
SPACE                   " "

INTCONST                [1-9][0-9]*|0
REALCONST               [0-9]*\.[0-9]*
STRING                  \"
NEWLINE                 [\n \\n \r\n]
TAB                     [\t \v]


ID                      [a-zA-Z][_a-zA-Z0-9]*
LINE_COMMENT            "//".*
BLOCK_COMMENT_START     \/\*
BLOCK_COMMENT_END       \*\/


%x BLOCK_COMMENT STATE_STRING

%%

{BLOCK_COMMENT_START}   {
    struct Comment com;
    com.start_line = yylineno;
    token_ctr++;
    com.token_no = token_ctr;
    push(stack, com);
    comment_ctr++;
    BEGIN(BLOCK_COMMENT);
    }
<BLOCK_COMMENT>"/*"     {
    struct Comment com;
    com.start_line = yylineno;
    token_ctr++;
    com.token_no = token_ctr;
    push(stack, com);
    comment_ctr++;
    }
<BLOCK_COMMENT>"\n"     {yylineno;}
<BLOCK_COMMENT>"*"+"/"  {
    int line = -1;
    int token = -1;
    char content[20];
    comment_ctr--;
    struct Comment tmp = pop(stack);
    struct Comment *tmp1 = (struct Comment *)malloc(sizeof(struct Comment));

    tmp.end_line = yylineno;
    sprintf(content, "%d - %d\0", tmp.start_line, tmp.end_line);
    tmp.final_content = strdup(content);
    
    tmp1->token_no = tmp.token_no;
    tmp1->start_line = tmp.start_line;
    tmp1->end_line = tmp.end_line;
    tmp1->comment_type = tmp.comment_type;
    tmp1->final_content = tmp.final_content;
    tmp1->next = NULL;

    if(comment_ctr>0){
        tmp1->comment_type = strdup("NESTED_COMMENT");
        sortedInsert(&comment_head, tmp1);

    }else if(comment_ctr == 0){
        struct Comment *temp = comment_head;
        
        tmp1->comment_type = strdup("BLOCK_COMMENT");
        sortedInsert(&comment_head, tmp1);
        line = yylineno;
        token = token_ctr;
        yylineno = tmp1->start_line;
        token_ctr = tmp1->token_no;
        insert_token("COMMENT", tmp1->comment_type, tmp1->final_content, "enumerated");
        yylineno = line;
        token_ctr = token;

        while(temp!=NULL){
            line = yylineno;
            token = token_ctr;
            yylineno = temp->start_line;
            token_ctr = temp->token_no;
            insert_token("COMMENT", temp->comment_type, temp->final_content, "enumerated");
            yylineno = line;
            token_ctr = token;
            temp = temp->next;
        }

        comment_head = NULL;
        
        BEGIN(INITIAL);
    }

}
<BLOCK_COMMENT><<EOF>>  {fprintf(stderr, "Comment starts but never ends. Terminating...\n"); yyterminate();}
<BLOCK_COMMENT>.        {}

{STRING}                {
    token_ctr++;
    if(buf==NULL){
        buf = (char*) malloc(1*sizeof(char));
        s = buf;
    }
    BEGIN(STATE_STRING);
    }
<STATE_STRING>\n|\\n    {n++; buf = (char*)realloc(buf,(n*sizeof(char))); *s++ = '\n';}
<STATE_STRING>\\t       {n++; buf = (char*)realloc(buf,(n*sizeof(char))); *s++ = '\t';}
<STATE_STRING>\\\"      {n++; buf = (char*)realloc(buf,(n*sizeof(char))); *s++ = '\"';}
<STATE_STRING>\"        {
    insert_token("STRING", buf, buf, "char*");
    yylval.id = strdup(buf);
    buf=NULL;
    s=NULL;
    n = 0;
    BEGIN(INITIAL);
    return STRING;
}
<STATE_STRING>.       {n++; buf = (char*)realloc(buf,(n*sizeof(char))); *s++ = *yytext;}
<STATE_STRING><<EOF>> {fprintf(stderr, "String starts but never ends. Terminating...\n"); yyterminate();}

{LINE_COMMENT}          {token_ctr++; insert_token("COMMENT", "LINE_COMMENT", "", "enumerated");}

{ELSE}                  {token_ctr++; insert_token("KEYWORD", "ELSE", yytext, "enumerated"); return ELSE;}
{WHILE}                 {token_ctr++; insert_token("KEYWORD", "WHILE", yytext, "enumerated"); return WHILE;}
{FOR}                   {token_ctr++; insert_token("KEYWORD", "FOR", yytext, "enumerated"); return FOR;}
{FUNCTION}              {token_ctr++; insert_token("KEYWORD", "FUNCTION", yytext, "enumerated"); return FUNCTION;}
{RETURN}                {token_ctr++; insert_token("KEYWORD", "RETURN", yytext, "enumerated"); return RETURN;}
{BREAK}                 {token_ctr++; insert_token("KEYWORD", "BREAK", yytext, "enumerated"); return BREAK;}
{CONTINUE}              {token_ctr++; insert_token("KEYWORD", "CONTINUE", yytext, "enumerated"); return CONTINUE;}
{AND}                   {token_ctr++; insert_token("KEYWORD", "AND", yytext, "enumerated"); return AND;}
{OR}                    {token_ctr++; insert_token("KEYWORD", "OR", yytext, "enumerated"); return OR;}
{NOT}                   {token_ctr++; insert_token("KEYWORD", "NOT", yytext, "enumerated"); return NOT;}
{LOCAL}                 {token_ctr++; insert_token("KEYWORD", "LOCAL", yytext, "enumerated"); return LOCAL;}
{TRUE}                  {token_ctr++; insert_token("KEYWORD", "TRUE", yytext, "enumerated"); return TRUE;}
{FALSE}                 {token_ctr++; insert_token("KEYWORD", "FALSE", yytext, "enumerated"); return FALSE;}
{NIL}                   {token_ctr++; insert_token("KEYWORD", "NIL", yytext, "enumerated"); return NIL;}
{IF}                    {token_ctr++; insert_token("KEYWORD", "IF", yytext, "enumerated"); return IF;}

{NOT_EQUALS}            {token_ctr++; insert_token("OPERATOR", "NOT_EQUALS", yytext, "enumerated"); return NOT_EQUALS;}
{EQUALS}                {token_ctr++; insert_token("OPERATOR", "EQUALS", yytext, "enumerated"); return EQUALS;}
{ASSIGN}                {token_ctr++; insert_token("OPERATOR", "ASSIGN", yytext, "enumerated"); return ASSIGN;}
{PLUS_PLUS}             {token_ctr++; insert_token("OPERATOR", "PLUS_PLUS", yytext, "enumerated"); return PLUS_PLUS;}
{MINUS_MINUS}           {token_ctr++; insert_token("OPERATOR", "MINUS_MINUS", yytext, "enumerated"); return MINUS_MINUS;}
{PLUS}                  {token_ctr++; insert_token("OPERATOR", "PLUS", yytext, "enumerated"); return PLUS;}
{MINUS}                 {token_ctr++; insert_token("OPERATOR", "MINUS", yytext, "enumerated"); return MINUS;}
{MULTI}                 {token_ctr++; insert_token("OPERATOR", "MULTI", yytext, "enumerated"); return MULTI;}
{DIV}                   {token_ctr++; insert_token("OPERATOR", "DIV", yytext, "enumerated"); return DIV;}
{MOD}                   {token_ctr++; insert_token("OPERATOR", "MOD", yytext, "enumerated"); return MOD;}
{GREATER_OR_EQUAL}      {token_ctr++; insert_token("OPERATOR", "GREATER_OR_EQUAL", yytext, "enumerated"); return GREATER_OR_EQUAL;}
{LESS_OR_EQUAL}         {token_ctr++; insert_token("OPERATOR", "LESS_OR_EQUAL", yytext, "enumerated"); return LESS_OR_EQUAL;}
{GREATER_THAN}          {token_ctr++; insert_token("OPERATOR", "GREATER_THAN", yytext, "enumerated"); return GREATER_THAN;}
{LESS_THAN}             {token_ctr++; insert_token("OPERATOR", "LESS_THAN", yytext, "enumerated");return LESS_THAN;}

{LEFT_CURLY}            {token_ctr++; insert_token("PUNCTUATION", "LEFT_CURLY", yytext, "enumerated"); return LEFT_CURLY;}
{RIGHT_CURLY}           {token_ctr++; insert_token("PUNCTUATION", "RIGHT_CURLYT", yytext, "enumerated"); return RIGHT_CURLY;}
{LEFT_BRACKET}          {token_ctr++; insert_token("PUNCTUATION", "LEFT_BRACKET", yytext, "enumerated"); return LEFT_BRACKET;}
{RIGHT_BRACKET}         {token_ctr++; insert_token("PUNCTUATION", "RIGHT_BRACKET", yytext, "enumerated"); return RIGHT_BRACKET;}
{LEFT_PARENTHESIS}      {token_ctr++; insert_token("PUNCTUATION", "LEFT_PARENTHESIS", yytext, "enumerated"); return LEFT_PARENTHESIS;}
{RIGHT_PARENTHESIS}     {token_ctr++; insert_token("PUNCTUATION", "RIGHT_PARENTHESIS", yytext, "enumerated"); return RIGHT_PARENTHESIS;}
{SEMICOLON}             {token_ctr++; insert_token("PUNCTUATION", "SEMICOLON", yytext, "enumerated"); return SEMICOLON;}
{COMMA}                 {token_ctr++; insert_token("PUNCTUATION", "COMMA", yytext, "enumerated"); return COMMA;}
{COLON}                 {token_ctr++; insert_token("PUNCTUATION", "COLON", yytext, "enumerated"); return COLON;}
{SCOPE}                 {token_ctr++; insert_token("PUNCTUATION", "SCOPE", yytext, "enumerated"); return SCOPE;}
{DOT}                   {token_ctr++; insert_token("PUNCTUATION", "DOT", yytext, "enumerated"); return DOT;}
{DOUBLE_DOT}            {token_ctr++; insert_token("PUNCTUATION", "DOUBLE_DOT", yytext, "enumerated"); return DOUBLE_DOT;}

{SPACE}                 {}

{INTCONST}              {token_ctr++; insert_token("INTCONST", "INTCONST", yytext, "integer"); yylval.intNum = atoi(yytext); return INTCONST;}
{REALCONST}             {token_ctr++; insert_token("REALCONST", "REALCONST", yytext, "real"); yylval.doubleNum = atof(yytext); return REALCONST;}


{ID}                    {token_ctr++; insert_token("ID", yytext, yytext, "char*"); yylval.id = strdup(yytext); return ID;}
{NEWLINE}               {yylineno;}
{TAB}                   {}
.                       {fprintf(stderr,"Undefine tokken..\nError!!!Terminating...\n"); yyterminate();}

%%