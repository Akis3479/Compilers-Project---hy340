%{
    #include <stdio.h>
    #include "symtable.h"
    #define STACK_SIZE 100

    int yyerror (char* yaccProvideMessage);
    int yylex (void);

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    struct Stack* stack;
    int isFunct = 0;

    SymTable_T *symtab;
    

%}

%start program

%union{
    int intNum;
    double doubleNum;
    char* id;
}

%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND OR NOT LOCAL TRUE FALSE NIL
%token NOT_EQUALS EQUALS ASSIGN PLUS_PLUS MINUS_MINUS PLUS MINUS MULTI DIV MOD GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN
%token LEFT_CURLY RIGHT_CURLY LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA COLON SCOPE DOT DOUBLE_DOT SPACE
%token LINE_COMMENT BLOCK_COMMENT_START BLOCK_COMMENT_END NEWLINE TAB

%token <intNum> INTCONST
%token <doubleNum> REALCONST
%token <id> STRING ID


%right ASSIGN
%left OR
%left AND
%nonassoc EQUALS NOT_EQUALS
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL
%left PLUS MINUS
%right MULTI DIV MOD
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT DOUBLE_DOT
%left LEFT_BRACKET RIGHT_BRACKET  
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program : statements          {printf("\033[1;31mprogram\033[0m <- statements :line  \033[1;32m✓\033[0m\n", yylineno);}
        ;

statements : statements stmt  {printf("statements <- statements stmt :line  %d  \n", yylineno);}
           |                  {printf("statements <- empty :line  %d  \n", yylineno);}
           ;

stmt : expr SEMICOLON         {printf("stmt <- expr; :line  %d  \n", yylineno);}
     | ifstmt                 {printf("stmt <- ifstmt :line  %d  \n", yylineno);}
     | whilestmt              {printf("stmt <- whilestmt :line  %d  \n", yylineno);}
     | forstmt                {printf("stmt <- forstmt :line  %d  \n", yylineno);}
     | returnstmt             {printf("stmt <- returnstmt :line  %d  \n", yylineno);}
     | BREAK SEMICOLON        {printf("stmt <- break; :line  %d  \n", yylineno);}
     | CONTINUE SEMICOLON     {printf("stmt <- continue; :line  %d  \n", yylineno);}
     | block                  {printf("stmt <- block :line  %d  \n", yylineno);}
     | funcdef                {printf("stmt <- funcdef :line  %d  \n", yylineno);}
     | SEMICOLON              {printf("stmt <- ; :line  %d  \n", yylineno);}
     ;

expr : assignexpr                           {printf("expr <- assignexpr :line  %d  \n", yylineno);}
     | expr PLUS expr                       {printf("expr <- expr + expr :line  %d  \n", yylineno);}
     | expr MINUS expr                      {printf("expr <- expr - expr :line  %d  \n", yylineno);}
     | expr MULTI expr                      {printf("expr <- expr * expr :line  %d  \n", yylineno);}
     | expr DIV expr                        {printf("expr <- expr DIV expr :line  %d  \n", yylineno);}
     | expr MOD expr                        {printf("expr <- expr MOD expr :line  %d  \n", yylineno);}
     | expr GREATER_THAN expr               {printf("expr <- expr > expr :line  %d  \n", yylineno);}
     | expr GREATER_OR_EQUAL expr           {printf("expr <- expr >= expr :line  %d  \n", yylineno);}
     | expr LESS_THAN expr                  {printf("expr <- expr < expr :line  %d  \n", yylineno);}
     | expr LESS_OR_EQUAL expr              {printf("expr <- expr <= expr :line  %d  \n", yylineno);}
     | expr EQUALS expr                     {printf("expr <- expr == expr :line  %d  \n", yylineno);}
     | expr NOT_EQUALS expr                 {printf("expr <- expr != expr :line  %d  \n", yylineno);}
     | expr AND expr                        {printf("expr <- expr AND expr :line  %d  \n", yylineno);}
     | expr OR expr                         {printf("expr <- expr OR expr :line  %d  \n", yylineno);}
     | term                                 {printf("expr <- term :line  %d  \n", yylineno);}
     ;

term : LEFT_PARENTHESIS expr RIGHT_PARENTHESIS         {printf("term <- ( expr ) :line  %d  \n", yylineno);}
     | MINUS expr %prec UMINUS                         {printf("term <- -expr  :line  %d  \n", yylineno);}
     | NOT expr                                        {printf("term <- NOT expr  :line  %d  \n", yylineno);}
     | PLUS_PLUS lvalue                                {printf("term <- ++lvalue  :line  %d  \n", yylineno);}
     | lvalue PLUS_PLUS                                {printf("term <- lvalue++  :line  %d  \n", yylineno);}
     | MINUS_MINUS lvalue                              {printf("term <- --lvalue  :line  %d  \n", yylineno);}
     | lvalue MINUS_MINUS                              {printf("term <- lvalue--  :line  %d  \n", yylineno);}
     | primary                                         {printf("term <- primary  :line  %d  \n", yylineno);}
     ;

assignexpr : lvalue ASSIGN expr      {printf("assignexpr <- lvalue = expr :line  %d  \n", yylineno);}
           ;

primary : lvalue                                                 {printf("primary <- lvalue :line  %d  \n", yylineno);}
        | call                                                   {printf("primary <- call :line  %d  \n", yylineno);}  
        | objectdef                                              {printf("primary <- objectdef :line  %d  \n", yylineno);}
        | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS             {printf("primary <- ( funcdef ) :line  %d  \n", yylineno);}
        | const                                                  {printf("primary <- const :line  %d  \n", yylineno);}
        ;

lvalue : ID                     {if(GlobalScope == 0) insert(symtab, yytext, 0, yylineno, GLOBAL); else insert(symtab, yytext, GlobalScope, yylineno, LOCALS); printf("lvalue <- ID :line  %d  \n", yylineno);}
       | LOCAL ID               {if(GlobalScope == 0) insert(symtab, yytext, 0, yylineno, GLOBAL); else {localspecified=1; insert(symtab, yytext, GlobalScope, yylineno, LOCALS); localspecified = 0;} printf("lvalue <- LOCAL ID :line  %d  \n", yylineno);}
       | SCOPE ID               {if(!lookupInScope(symtab, yytext, 0)) yyerror("ID: not found globaly.\n"); printf("lvalue <- :: ID :line  %d  \n", yylineno);}
       | member                 {printf("lvalue <- member :line  %d  \n", yylineno);}
       ; 

member : lvalue DOT ID                                 {if(!lookup(symtab, yytext, GlobalScope)) yyerror("ID: not found.\n"); printf("member <- lvalue.ID :line  %d  \n", yylineno);}
       | lvalue LEFT_BRACKET expr RIGHT_BRACKET        {printf("member <- lvalue[expr] :line  %d  \n", yylineno);}
       | call DOT ID                                   {if(!lookup(symtab, yytext, GlobalScope)) yyerror("ID: not found.\n"); printf("member <- call.ID :line  %d  \n", yylineno);}
       | call LEFT_BRACKET expr RIGHT_BRACKET          {printf("member <- call[expr] :line  %d  \n", yylineno);}
       ;

call : call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS                                           {printf("call <- call ( elist ) :line  %d  \n", yylineno);}
     | lvalue callsuffix                                                                       {printf("call <- lvalue callsuffix :line  %d  \n", yylineno);}
     | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS     {printf("call <- ( funcdef ) ( elist ) :line  %d  \n", yylineno);}
     ;

callsuffix : normcall           {printf("callsuffix <- normcall :line  %d  \n", yylineno);}
           | methodcall         {printf("callsuffix <- methodcall :line  %d  \n", yylineno);}
           ;

normcall : LEFT_PARENTHESIS elist RIGHT_PARENTHESIS            {printf("normcall <- ( elist ) :line  %d  \n", yylineno);}
         ;
         
methodcall : DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS        {printf("methodcall <- ..ID(elist) :line  %d  \n", yylineno);}
           ;

elist	: expr elists	                {printf("elist <- expr elists :line  %d  \n", yylineno);}
	|                    	        {printf("elist <- empty :line  %d  \n", yylineno);}
	;

elists	: COMMA expr elists              {printf("elists <- COMMA expr elists :line  %d  \n", yylineno);}
	|       	                {printf("elist <- empty :line  %d  \n", yylineno);}	
	;

objectdef : LEFT_BRACKET elist RIGHT_BRACKET       {printf("objectdef <- [elist] :line  %d  \n", yylineno);}
          | LEFT_BRACKET indexed RIGHT_BRACKET     {printf("objectdef <- [indexed] :line  %d  \n", yylineno);}
          ;

indexed : indexedelem indexeds	                                {printf("indexed <- indexedelem indexeds :line  %d  \n", yylineno);}
	;
		
indexeds : COMMA indexedelem indexeds	                        {printf("indexeds <- ,indexedelem indexeds :line  %d  \n", yylineno);}
         |         		                                {printf("indexeds <- empty :line  %d  \n", yylineno);}
         ;

indexedelem : LEFT_CURLY expr COLON expr RIGHT_CURLY            {printf("indexedelem <- { expr:expr } :line  %d  \n", yylineno);}
            ;

block : LEFT_CURLY{if(!isFunct) GlobalScope++; else isFunct=0;}  statements stmt RIGHT_CURLY {hide(symtab, GlobalScope); GlobalScope--;}                  {printf("block <- { statements stmt } :line  %d  \n", yylineno);}
      | LEFT_CURLY RIGHT_CURLY   {hide(symtab, GlobalScope); GlobalScope--; isFunct=0;}                                                                   {printf("block <- { } :line %d  \n", yylineno);}
      ;

funcdef : FUNCTION ID {insert(symtab, yytext, GlobalScope, yylineno, USERFUNC);} LEFT_PARENTHESIS{GlobalScope++; isFunct=1;}  idlist RIGHT_PARENTHESIS block            {printf("funcdef <- FUNCTION ID(idlist) block :line  %d  \n", yylineno);}
        | FUNCTION {insert(symtab, "", GlobalScope, yylineno, USERFUNC);} LEFT_PARENTHESIS{GlobalScope++; isFunct=1;}  idlist RIGHT_PARENTHESIS block               {printf("funcdef <- FUNCTION (idlist) block :line  %d  \n", yylineno);}
        ;

const : number           {printf("const <- number :line  %d  \n", yylineno);}
      | STRING           {printf("const <- STRING :line  %d  \n", yylineno);}
      | NIL              {printf("const <- NIL :line  %d  \n", yylineno);}
      | TRUE             {printf("const <- TRUE :line  %d  \n", yylineno);}
      | FALSE            {printf("const <- FALSE :line  %d  \n", yylineno);}
      ;
     
number : INTCONST        {printf("number <- INTCONST :line  %d  \n", yylineno);}
       | REALCONST       {printf("number <- REALCONST :line  %d  \n", yylineno);}
       ;

idlist : ID        { if(isFunct) {insert(symtab, yytext, GlobalScope, yylineno, FORMAL); insertFuncArgs(symtab, yytext, GlobalScope);} } idlists
       |                        {printf("idlist <- empty :line  %d  \n", yylineno);}
       ;

idlists : COMMA ID{ if(isFunct) {insert(symtab, yytext, GlobalScope, yylineno, FORMAL); insertFuncArgs(symtab, yytext, GlobalScope);} } idlists    {printf("idlist <- empty :line  %d  \n", yylineno);}
        |                       {printf("idlist <- empty :line  %d  \n", yylineno);}
        ;

ifstmt : IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt     %prec LOWER_THAN_ELSE          {printf("if(expr) stmt :line  %d  \n", yylineno);}
       | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt                          {printf("if(expr) stmt else stmt :line  %d  \n", yylineno);}
       ;

whilestmt : WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt         {printf("whilestmt <- while(expr) stmt :line  %d  \n", yylineno);}
          ;

forstmt : FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt          {printf("for(elist;expr;elist) stmt :line  %d  \n", yylineno);}
        ;

returnstmt : RETURN expr SEMICOLON        {printf("returnstmt <- return expr; :line  %d  \n", yylineno);}
           | RETURN SEMICOLON             {printf("returnstmt <- return; :line  %d  \n", yylineno);}
           ;

%%


int yyerror (char* yaccProvideMessage){
    fprintf(stderr, "%s: at :line %d, before token: %s\n",yaccProvideMessage,yylineno,yytext);
    fprintf(stderr,"INPUT NOT VALID\n");
}


int main(){
        stack = (struct Stack*)createStack(STACK_SIZE);
        symtab = SymTable_new();
        yyparse();
        printSymbolTable(symtab);
        PrintListOfArgs(symtab);
}