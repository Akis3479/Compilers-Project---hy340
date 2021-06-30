%{
    #include <stdio.h>
    #include "symtable.h"
    #include "quads.h"
    #define STACK_SIZE 100

    int yyerror (char* yaccProvideMessage);
    int yylex (void);

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    struct Stack* stack;
    int inFunct = 0;
    int local=0;
    int isCalledFunc = 0;
    int comingFromFuncdef = 0;
    int inLoop=0, inIF=0, inELSE=0;
    typedef enum lastCurlyUsedenum { E_FUNCTION, E_IF, E_ELSE, E_LOOP }lastCurlyUsedenum; // ALLAGI
    lastCurlyUsedenum lastCurlyUsed; // ALLAGI
    char *lastlvalue = ""; /* NEW */ 
    int wasInLoop = 0;

    SymTable_T *symtab;
    

%}

%start program

%union{
    int intNum;
    double doubleNum;
    char* id;
    struct stmt_t *stmt_tt;
    struct expr* expression;
    struct forstruct* forpref;
    struct call_t* s_call;
}

%token <expression> IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND OR NOT LOCAL TRUE FALSE NIL
%token <expression> NOT_EQUALS EQUALS ASSIGN PLUS_PLUS MINUS_MINUS PLUS MINUS MULTI DIV MOD GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN
%token <expression> LEFT_CURLY RIGHT_CURLY LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA COLON SCOPE DOT DOUBLE_DOT SPACE
%token <expression> LINE_COMMENT BLOCK_COMMENT_START BLOCK_COMMENT_END NEWLINE TAB

%token <intNum> INTCONST
%token <doubleNum> REALCONST
%token <id> STRING ID


%right ASSIGN
%left OR
%left AND
%nonassoc EQUALS NOT_EQUALS
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL
%left PLUS MINUS
%left MULTI DIV MOD
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT DOUBLE_DOT
%left LEFT_BRACKET RIGHT_BRACKET  
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%type <stmt_tt> statements
%type <stmt_tt> stmt

%type <expression> expr
%type <expression> term
%type <expression> assignexpr
%type <expression> primary
%type <expression> lvalue
%type <expression> member
%type <expression> call
%type <expression> elist
%type <expression> elists
%type <expression> objectdef
%type <expression> indexed
%type <expression> indexeds
%type <expression> indexedelem
%type <expression> block
%type <expression> funcdef funcprefix funcargs
%type <expression> const
%type <expression> number
%type <expression> forstmt
%type <expression> returnstmt

%type <intNum> ifstmt ifprefix elseprefix
%type <intNum> N M
%type <intNum> whilestmt whilestart whilecond funcbody

%type <forpref> forprefix

%type <s_call> callsuffix normcall methodcall


%%

program : statements          {printf("\033[1;31mprogram\033[0m <- statements :line  \033[1;32m✓\033[0m\n", yylineno);}
        ;

statements : statements stmt    {printf("statements <- statements stmt :line  %d  \n", yylineno);}
           |                    {printf("statements <- empty :line  %d  \n", yylineno);}
           ;

stmt : expr SEMICOLON         {resettemp();     printf("stmt <- expr; :line  %d  \n", yylineno);}
     | ifstmt                 {printf("stmt <- ifstmt :line  %d  \n", yylineno);}
     | whilestmt              {printf("stmt <- whilestmt :line  %d  \n", yylineno);}
     | forstmt                {printf("stmt <- forstmt :line  %d  \n", yylineno);}
     | returnstmt             {printf("stmt <- returnstmt :line  %d  \n", yylineno);}
     | BREAK                    {
                                        if(inLoop == 0 || GlobalScope == 0){
                                                yyerror("Cannot break when not in loop.");
                                        }
                                }
                                SEMICOLON       {
                                                        insertBrContList(nextquadlabel(), 0, 'b');
                                                        emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        printf("stmt <- break; :line  %d  \n", yylineno);
                                                }
     | CONTINUE                 {
                                        if(inLoop == 0 || GlobalScope == 0){
                                                yyerror("Cannot continue when not in loop.");
                                        }
                                }
                                SEMICOLON        {
                                                        insertBrContList(nextquadlabel(), 0, 'c');
                                                        emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        printf("stmt <- continue; :line  %d  \n", yylineno);
                                                }
     | block                  {printf("stmt <- block :line  %d  \n", yylineno);}
     | funcdef                {printf("stmt <- funcdef :line  %d  \n", yylineno);}
     | SEMICOLON              {printf("stmt <- ; :line  %d  \n", yylineno);}
     ;

expr : assignexpr                       {$$ = $1; printf("expr <- assignexpr :line  %d  \n", yylineno);}
     | expr PLUS expr                   {
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(add, $$, $1, $3, -1, yylineno);
                                                
                                                printf("expr <- expr + expr :line  %d  \n", yylineno);
                                        }
     | expr MINUS expr                  {
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(sub, $$, $1, $3, -1, yylineno);   
                                                
                                                printf("expr <- expr - expr :line  %d  \n", yylineno);
                                        }
     | expr MULTI expr                  {
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(mul, $$, $1, $3, -1, yylineno);

                                                printf("expr <- expr * expr :line  %d  \n", yylineno);
                                        }
     | expr DIV expr                    {
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(div_i, $$, $1, $3, -1, yylineno);

                                                printf("expr <- expr DIV expr :line  %d  \n", yylineno);
                                        }
     | expr MOD expr                    {
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(mod, $$, $1, $3, -1, yylineno);        

                                                printf("expr <- expr MOD expr :line  %d  \n", yylineno);
                                        }
     | expr GREATER_THAN expr           {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);

                                                emitQuad(if_greater, NULL, $1, $3, nextquadlabel()+3, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr > expr :line  %d  \n", yylineno);
                                        }
     | expr GREATER_OR_EQUAL expr       {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);

                                                emitQuad(if_greatereq, NULL, $1, $3, nextquadlabel()+3, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(1), NULL, -1, yylineno);
                                                
                                                printf("expr <- expr >= expr :line  %d  \n", yylineno);
                                        }
     | expr LESS_THAN expr              {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);

                                                emitQuad(if_less, NULL, $1, $3, nextquadlabel()+3, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(1), NULL, -1, yylineno);
                                                
                                                printf("expr <- expr < expr :line  %d  \n", yylineno);
                                        }
     | expr LESS_OR_EQUAL expr          {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);

                                                emitQuad(if_lesseq, NULL, $1, $3, nextquadlabel()+3, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr <= expr :line  %d  \n", yylineno);
                                        }
     | expr EQUALS expr                 {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);

                                                emitQuad(if_eq, NULL, $1, $3, nextquadlabel()+3, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr == expr :line  %d  \n", yylineno);
                                        }
     | expr NOT_EQUALS expr             {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);

                                                emitQuad(if_noteq, NULL, $1, $3, nextquadlabel()+3, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(0), NULL, -1, yylineno);
                                                emitQuad(jump, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
                                                emitQuad(assign, $$, newexpr_constbool(1), NULL, -1, yylineno);

                                                printf("expr <- expr != expr :line  %d  \n", yylineno);
                                        }
     | expr AND expr                    {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(and, $$, $1, $3, -1, yylineno);

                                                printf("expr <- expr AND expr :line  %d  \n", yylineno);
                                        }
     | expr OR expr                     {
                                                $$ = newexpr(boolexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(or, $$, $1, $3, -1, yylineno);

                                                printf("expr <- expr OR expr :line  %d  \n", yylineno);
                                        }
     | term                             {$$ = $1; printf("expr <- term :line  %d  \n", yylineno);}
     ;

term : LEFT_PARENTHESIS expr RIGHT_PARENTHESIS         {$$ = $2; printf("term <- ( expr ) :line  %d  \n", yylineno);}
     | MINUS expr %prec UMINUS                         {
                                                                printf("term <- -expr  :line  %d  \n", yylineno);
                                                                check_arith($2);
                                                                $$ = newexpr(arithexpr_e);
                                                                $$->sym = istempexpr($2) ? $2->sym :newtemp(symtab);
                                                                emitQuad(uminus,$$, $2, NULL, -1, yylineno);
                                                        }
     | NOT expr                                        {
                                                                $$ = newexpr(boolexpr_e);
                                                                $$->sym = newtemp(symtab);
                                                                emitQuad(not, $$, $2, NULL, -1, yylineno);
                                                                printf("term <- NOT expr  :line  %d  \n", yylineno);
                                                        }
     | PLUS_PLUS lvalue {
                                if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1){
                                        yyerror("Cannot use function as lvalue");
                                }
                                printf("term <- ++lvalue  :line  %d  \n", yylineno);
                                /*check_arith($2);*/
                                if($2->type == tableitem_e){
                                        $$ = emit_iftableitem(symtab,$2);
                                        emitQuad(add, $$, $$, newexpr_constint(1), -1, yylineno);
                                        emitQuad(tablesetelem, $$, $2, $2->index, -1, yylineno);
                                }else{
                                        emitQuad(add, $2, newexpr_constint(1), $2, -1, yylineno);
                                        $$ = newexpr(arithexpr_e);
                                        $$->sym = newtemp(symtab);
                                        emitQuad(assign, $$, $2, NULL, -1, yylineno);
                                }
                        }
     | lvalue   {
                        if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1)
                                yyerror("Cannot use function as lvalue");
                } 
                PLUS_PLUS       {
                                        printf("term <- lvalue++  :line  %d  \n", yylineno);
                                        /*check_arith($1);*/
                                        $$ = newexpr(var_e);
                                        $$->sym = newtemp(symtab);
                                        if($1->type == tableitem_e){
                                                expr* val = emit_iftableitem(symtab,$1);
                                                emitQuad(assign, $1, val, NULL, -1, yylineno);
                                                emitQuad(add, val, val, newexpr_constint(1), -1,yylineno);
                                                emitQuad(tablesetelem, val, $1, $1->index, -1, yylineno);
                                        }else{
                                                emitQuad(assign, $$, $1, NULL, -1, yylineno);
                                                emitQuad(add, $1, $1, newexpr_constint(1), -1, yylineno);
                                        }
                                }
     | MINUS_MINUS lvalue       {
                                        if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1){
                                                yyerror("Cannot use function as lvalue");
                                        }
                                        printf("term <- --lvalue  :line  %d  \n", yylineno);
                                        /*check_arith($2);*/
                                        if($2->type == tableitem_e){
                                                $$ = emit_iftableitem(symtab,$2);
                                                emitQuad(sub, $$, $$, newexpr_constint(1), -1, yylineno);
                                                emitQuad(tablesetelem, $$, $2, $2->index, -1, yylineno);
                                        }else{
                                                emitQuad(sub, $2, $2, newexpr_constint(1), -1, yylineno);
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp(symtab);
                                                emitQuad(assign, $$, $2, NULL, -1, yylineno);
                                        }
                                }
     | lvalue   {
                        if(isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1)
                                yyerror("Cannot use function as lvalue");
                } MINUS_MINUS           {
                                                printf("term <- lvalue--  :line  %d  \n", yylineno);
                                                /*check_arith($1);*/
                                                $$ = newexpr(var_e);
                                                $$->sym = newtemp(symtab);
                                                if($1->type == tableitem_e){
                                                        expr* val = emit_iftableitem(symtab,$1);
                                                        emitQuad(assign, $1, val, NULL, -1, yylineno);
                                                        emitQuad(sub, val, val, newexpr_constint(1), -1,yylineno);
                                                        emitQuad(tablesetelem, val, $1, $1->index, -1, yylineno);
                                                }else{
                                                        emitQuad(assign, $$, $1, NULL, -1, yylineno);
                                                        emitQuad(sub, $1, $1, newexpr_constint(1), -1, yylineno);
                                                }
                                        }
     | primary                          {$$ = $1; printf("term <- primary  :line  %d  \n", yylineno);}
     ;

assignexpr : lvalue     {
                                printf("lastlvalue: -- %s", lastlvalue);
                                if(local == 0 && (isLibfunc(lastlvalue)==1 || isUserFunction(symtab, lastlvalue) == 1)){
                                        yyerror("Cannot use function as lvalue");
                                }
                                local=0;
                        } ASSIGN expr   {
                                                printf("assignexpr <- lvalue = expr :line  %d  \n", yylineno);
                                                if($1->type == tableitem_e){
                                                        emitQuad(tablesetelem, $4, $1, $1->index, -1, yylineno);
                                                        $$ = emit_iftableitem(symtab,$1);
                                                        $$->type = assignexpr_e;
                                                }else{
                                                        
                                                        emitQuad(assign, $1, $4, NULL, -1, yylineno);
                                                        $$ = newexpr(assignexpr_e);
                                                        $$->sym = newtemp(symtab);
                                                        if($$->sym == NULL){
                                                                printf("\nerorrrrrrrrr\n");
                                                        }
                                                        emitQuad(assign, $$, $1, NULL, -1, yylineno);
                                                }
                                                
                                        }
           ;

primary : lvalue                                               {
                                                                        $$ = emit_iftableitem(symtab,$1);
                                                                        printf("primary <- lvalue :line  %d  \n", yylineno);
                                                                }
        | call                                                  {$$ = $1; printf("primary <- call :line  %d  \n", yylineno);}  
        | objectdef                                             {$$ = $1; printf("primary <- objectdef :line  %d  \n", yylineno);}
        | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS            {
                                                                        $$ = newexpr(programfunc_e);
                                                                        $$->sym = $2->sym;

                                                                        printf("primary <- ( funcdef ) :line  %d  \n", yylineno);
                                                                }
        | const                                                  {$$ = $1; printf("primary <- const :line  %d  \n", yylineno);}
        ;

lvalue : ID                     {
                                        lastlvalue = strdup(yytext);
                                        SymbolTableEntry* sym;
                                        if(GlobalScope == 0){
                                                sym = RetLookup(yytext,0);
                                                if(sym == NULL){
                                                        sym = insert(symtab, yytext, 0, yylineno, GLOBAL, currscopeoffset(), currscopespace());
                                                        incurrscopeoffset();
                                                }
                                                $$ = lvalue_expr(sym);
                                        }else{
                                                sym = RetLookup(yytext,GlobalScope);
                                                if(sym == NULL){
                                                        sym =  insert(symtab, yytext, GlobalScope, yylineno, LOCALS, currscopeoffset(), currscopespace());
                                                        incurrscopeoffset();
                                                }
                                                $$ = lvalue_expr(sym);
                                        }
                                        printf("lvalue <- ID :line  %d  \n", yylineno);
                                }
       | LOCAL {local=1;} ID            {
                                                SymbolTableEntry* sym;
                                                if(GlobalScope == 0){
                                                        sym = RetLookupInScope(yytext,0);
                                                        if(sym == NULL){
                                                                sym = insert(symtab, yytext, 0, yylineno, GLOBAL, currscopeoffset(), currscopespace());
                                                                incurrscopeoffset();
                                                        }
                                                        $$ = lvalue_expr(sym);
                                                }else{
                                                        sym = RetLookupInScope(yytext,GlobalScope);
                                                        if(sym == NULL){
                                                                localspecified=1;
                                                                sym = insert(symtab, yytext, GlobalScope, yylineno, LOCALS, currscopeoffset(), currscopespace());
                                                                localspecified = 0;
                                                                incurrscopeoffset();
                                                        }
                                                        $$ = lvalue_expr(sym);
                                                }
                                                printf("lvalue <- LOCAL ID :line  %d  \n", yylineno);
                                        }
       | SCOPE ID               {
                                        SymbolTableEntry* sym;
                                        if(!lookupInScope(yytext, 0)){
                                                yyerror("Error : ID not found globaly");
                                        }
                                        sym = RetLookupInScope(yytext, 0);
                                        $$ = lvalue_expr(sym);
                                        printf("lvalue <- :: ID :line  %d  \n", yylineno);
                                }
       | member                 {$$ = $1; printf("lvalue <- member :line  %d  \n", yylineno);}
       ; 

member : lvalue DOT ID   {lastlvalue = strdup(yytext);}                              {printf("member <- lvalue.ID :line  %d  \n", yylineno);}
       | lvalue LEFT_BRACKET expr RIGHT_BRACKET        {printf("member <- lvalue[expr] :line  %d  \n", yylineno);}
       | call DOT ID     {lastlvalue = strdup(yytext);}                              {printf("member <- call.ID :line  %d  \n", yylineno);}
       | call LEFT_BRACKET expr RIGHT_BRACKET          {printf("member <- call[expr] :line  %d  \n", yylineno);}
       ;

call : call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS                                            {
                                                                                                        $$ = make_call(symtab,$1, $3);

                                                                                                        printf("call <- call ( elist ) :line  %d  \n", yylineno);
                                                                                                }
     | lvalue {isCalledFunc = 1;}  callsuffix                                                   {       
                                                                                                        isCalledFunc=0;
                                                                                                        
                                                                                                        $1 = emit_iftableitem(symtab, $1);
                                                                                                        if($3->method){
                                                                                                                expr* t = $1;
                                                                                                                $1 = emit_iftableitem(symtab, member_item(symtab, t, $3->name));
                                                                                                                $3->elist->next = t;
                                                                                                        }
                                                                                                        $$ = make_call(symtab, $1, $3->elist);

                                                                                                        printf("call <- lvalue callsuffix :line  %d  \n", yylineno);
                                                                                                }
     | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS      {
                                                                                                        /*expr* func = newexpr(programfunc_e);
                                                                                                        func->sym = $2;
                                                                                                        $$ = make_call(symtab,func, $4);*/

                                                                                                        printf("call <- ( funcdef ) ( elist ) :line  %d  \n", yylineno);
                                                                                                }
     ;

callsuffix : normcall           {$$ = $1; printf("callsuffix <- normcall :line  %d  \n", yylineno);}
           | methodcall         {$$ = $1; printf("callsuffix <- methodcall :line  %d  \n", yylineno);}
           ;

normcall : LEFT_PARENTHESIS elist RIGHT_PARENTHESIS             {
                                                                        $$ = (call_t *)malloc(sizeof(call_t));
                                                                        $$->elist = $2;
                                                                        $$->method = 0;
                                                                        $$->name = NULL;

                                                                        printf("normcall <- ( elist ) :line  %d  \n", yylineno);
                                                                }
         ;

methodcall : DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS     {
                                                                                $$ = (call_t *)malloc(sizeof(call_t));
                                                                                $$->elist = $4;
                                                                                $$->method = 1;
                                                                                $$->name = $2;

                                                                                printf("methodcall <- ..ID(elist) :line  %d  \n", yylineno);
                                                                        }
           ;

elist	: expr elists	                {$$ = $1; $$->next = $2; printf("elist <- expr elists :line  %d  \n", yylineno);}
	|                    	        {$$ = NULL; printf("elist <- empty :line  %d  \n", yylineno);}
	;

elists	: COMMA expr elists             {$$ = $2; $$->next = $3; printf("elists <- COMMA expr elists :line  %d  \n", yylineno);}
	|       	                {$$ = NULL; printf("elist <- empty :line  %d  \n", yylineno);}	
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

block : LEFT_CURLY      {
                                if(comingFromFuncdef==0){
                                        GlobalScope++;
                                }else if(lastCurlyUsed == E_ELSE || lastCurlyUsed == E_IF || lastCurlyUsed == E_LOOP){
                                        GlobalScope++;
                                }
                        }  statements stmt RIGHT_CURLY {
                                                                hide(GlobalScope); 
                                                                GlobalScope--;
                                                                if(inFunct > 0 && lastCurlyUsed == E_FUNCTION) // ALLAGI
                                                                inFunct--;
                                                                else if(inIF>0 &&  lastCurlyUsed == E_FUNCTION)
                                                                inIF--;
                                                                else if(inELSE>0 && lastCurlyUsed == E_ELSE)
                                                                inELSE--;
                                                                else if(inLoop>0 && lastCurlyUsed == E_LOOP)
                                                                inLoop--;
                                                                comingFromFuncdef=0;
                                                                printf("block <- { statements stmt } :line  %d  \n", yylineno);
                                                        }
      | LEFT_CURLY RIGHT_CURLY  {      hide(GlobalScope);
                                        GlobalScope--;
                                        if(inFunct > 0 && lastCurlyUsed == E_FUNCTION) // ALLAGI
                                                inFunct--;
                                        else if(inIF>0 &&  lastCurlyUsed == E_FUNCTION)
                                                inIF--;
                                        else if(inELSE>0 && lastCurlyUsed == E_ELSE)
                                                inELSE--;
                                        else if(inLoop>0 && lastCurlyUsed == E_LOOP)
                                                inLoop--;
                                        comingFromFuncdef=0;
                                        printf("block <- { } :line %d  \n", yylineno);
                                }
      ;

funcdef : funcprefix funcargs funcbody  {
                                                /*exitscopespace();
                                                $1->totalLocals = $3;
                                                int offset= pop_and_top(scopeoffsetStack);
                                                restorecurrscopeoffset(offset);
                                                $$ = $1;
                                                emitQuad(funcend, NULL, $1, NULL, -1, yylineno);*/
                                        }
        ;

funcprefix : FUNCTION ID        {
                                        /*$$ = insert(symtab, yytext, GlobalScope, yylineno, USERFUNC, currscopeoffset(), currscopespace());
                                        $$->iadress = nextquadlabel();
                                        emitQuad(funcstart, NULL, $$, NULL, -1, yylineno);
                                        push(scopeoffsetStack, currscopeoffset());
                                        enterscopespace();
                                        resetformalargoffset();*/
                                }
           | FUNCTION           {
                                        /*$$ = insert(symtab, "", GlobalScope, yylineno, USERFUNC, currscopeoffset(), currscopespace());
                                        $$->iadress = nextquadlabel();
                                        emitQuad(funcstart, NULL, $$, NULL, -1, yylineno);
                                        push(scopeoffsetStack, currscopeoffset());
                                        enterscopespace();
                                        resetformalargoffset();*/
                                }
           ;

funcargs : LEFT_PARENTHESIS     {       GlobalScope++;
                                        inFunct++;
                                        comingFromFuncdef=1;
                                        lastCurlyUsed = E_FUNCTION;
                                }
                                idlist RIGHT_PARENTHESIS        {
                                                                        /*enterscopespace();
                                                                        resetfuntionlocalsoffset();*/
                                                                }
         ;
funcbody : block                {
                                        /*$$ = currscopeoffset();
                                        exitscopespace();*/
                                        printf("funcdef <- FUNCTION (idlist) block :line  %d  \n", yylineno);
                                }
         ;

const : number           {$$ = $1; printf("const <- number :line  %d  \n", yylineno);}
      | STRING           {$$ = newexpr_conststring(yylval.id); printf("const <- STRING :line  %d  \n", yylineno);}
      | NIL              {$$ = newexpr_constsnill(); printf("const <- NIL :line  %d  \n", yylineno);}
      | TRUE             {$$ = newexpr_constbool(1); printf("const <- TRUE :line  %d  \n", yylineno);}
      | FALSE            {$$ = newexpr_constbool(0); printf("const <- FALSE :line  %d  \n", yylineno);}
      ;

number : INTCONST        {$$ = newexpr_constint(yylval.intNum); printf("number <- INTCONST :line  %d  \n", yylineno);}
       | REALCONST       {$$ = newexpr_constreal(yylval.doubleNum); printf("number <- REALCONST :line  %d  \n", yylineno);}
       ;

idlist : ID             {
                                if(inFunct>0){
                                        insert(symtab, yytext, GlobalScope, yylineno, FORMAL, currscopeoffset(), currscopespace()); insertFuncArgs(symtab, yytext, GlobalScope);
                                        } 
                                }
                                idlists    {printf("idlist <- ID idlists :line  %d  \n", yylineno);}
       |                {printf("idlist <- empty :line  %d  \n", yylineno);}
       ;

idlists : COMMA ID      {if(inFunct>0) {insert(symtab, yytext, GlobalScope, yylineno, FORMAL, currscopeoffset(), currscopespace()); insertFuncArgs(symtab, yytext, GlobalScope);} } idlists    {printf("idlists <- ,ID idlists :line  %d  \n", yylineno);}
        |               {printf("idlists <- empty :line  %d  \n", yylineno);}
        ;

ifstmt : ifprefix stmt  %prec LOWER_THAN_ELSE           {patchlabel($$, nextquadlabel()); printf("if(expr) stmt :line  %d  \n", yylineno);}
       | ifprefix stmt elseprefix stmt                  {
                                                                patchlabel($1, $3+1);
                                                                patchlabel($3, nextquadlabel());
                                                                printf("if(expr) stmt else stmt :line  %d  \n", yylineno);
                                                        }
       ;

ifprefix : IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS   {
                                                                inIF++;
                                                                lastCurlyUsed = E_IF; /* ALLAGI */
                                                                emitQuad(if_eq,NULL, $3, newexpr_constbool(1), nextquadlabel()+2, yylineno);
                                                                $$ = nextquadlabel();
                                                                emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                        }
         ;

elseprefix : ELSE       {
                                inELSE++;
                                lastCurlyUsed = E_ELSE; /* ALLAGI */
                                $$ = nextquadlabel();
                                emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                        }
           ;

whilestmt : whilestart whilecond stmt         {
                                                        emitQuad(jump, NULL, NULL, NULL, $1, yylineno);
                                                        patchlabel($2, nextquadlabel());
                                                        patchBrContList($1, nextquadlabel());

                                                        printf("whilestmt <- while(expr) stmt :line  %d  \n", yylineno);
                                                }
          ;

whilestart : WHILE      {$$ = nextquadlabel();}
           ;

whilecond : LEFT_PARENTHESIS expr RIGHT_PARENTHESIS     {
                                                                emitQuad(if_eq, NULL, $2, newexpr_constbool(1), nextquadlabel()+2, yylineno);
                                                                $$ = nextquadlabel();
                                                                emitQuad(jump, NULL, NULL, NULL, 0, yylineno);
                                                                inLoop++; lastCurlyUsed = E_LOOP; /* ALLAGI */
                                                        }
          ;

forstmt : forprefix N elist RIGHT_PARENTHESIS  {       inLoop++;
                                                        lastCurlyUsed = E_LOOP; /* ALLAGI */
                                                }
                                                N stmt N        {
                                                                        patchlabel($1->enter, $6+1);
                                                                        patchlabel($2, nextquadlabel());
                                                                        patchlabel($6, $1->test);
                                                                        patchlabel($8, $2+1);

                                                                        patchBrContList($2+1, nextquadlabel());
                                                                        printf("for(elist;expr;elist) stmt :line  %d  \n", yylineno);
                                                                }
        ;

forprefix : FOR LEFT_PARENTHESIS elist SEMICOLON M  expr SEMICOLON     {
                                                                                $$ = (struct forstruct *) malloc (sizeof(forstruct));
                                                                                $$->test = $5;
                                                                                printf("\n$$->test=%d",$$->test);
                                                                                $$->enter = nextquadlabel();
                                                                                printf("\n$$->enter=%d",$$->enter);
                                                                                emitQuad(if_eq, NULL, $6, newexpr_constbool(1), 0, yylineno);
                                                                        }
           ;

N : {$$ = nextquadlabel(); emitQuad(jump, NULL, NULL, NULL, 0, yylineno);}
  ;

M : {$$ = nextquadlabel();}
  ;

returnstmt : RETURN     {
                                if(inFunct == 0 ||/* ALLAGI */ GlobalScope==0){
                                        yyerror("Cannot return when not in Function.");
                                }
                        } expr SEMICOLON        {
                                                        emitQuad(ret, $3, NULL, NULL, -1, yylineno);
                                                        printf("returnstmt <- return expr; :line  %d  \n", yylineno);
                                                }
           | RETURN     {
                                if(inFunct == 0 ||/* ALLAGI */ GlobalScope==0){
                                        yyerror("Cannot return when not in Function.");
                                }
                        } SEMICOLON             {
                                                        emitQuad(ret, NULL, NULL, NULL, -1, yylineno);
                                                        printf("returnstmt <- return; :line  %d  \n", yylineno);
                                                }
           ;

%%


int yyerror (char* yaccProvideMessage){
        if(strcmp(yaccProvideMessage,"syntax error")==0){
                fprintf(stderr, "\033[1;31mGrammar Error : Before \"%s\" at :line %d\033[0m\n",yytext,yylineno);
        }else{
                fprintf(stderr, "\033[1;31m%s \"%s\" at :line %d\033[0m\n",yaccProvideMessage,yytext,yylineno);
        }
        exit(EXIT_FAILURE);
}


int main(){
        stack = (struct Stack*)createStack(STACK_SIZE);
        symtab = SymTable_new();
        emitFirstDummyQuad();
        yyparse();
        printSymbolTable();
        PrintListOfArgs(symtab);
        printf("\033[1;31m------------------------------PhaseC------------------------------\033[0m\n");
        printf("\033[1;31m                        (Intermediate Code)\033[0m\n");
        printQuads();
}