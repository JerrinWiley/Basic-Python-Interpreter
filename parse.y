%error-verbose


%{
#include <iostream>
#include "exception.h"
#include "expression.h"
#include "statement.h"
#include "program.h"
#include "function.h"

using std::cerr;
using std::endl;

extern int yylex();
extern int yylineno;

bool error = false;

int parseResult = 1;

void yyerror(const char* s) {
   // bision seems to call both versions of yyerror, check a flag to supress the duplicate message
   if (!error) {
      cerr << "error (line " << yylineno << "): " << s << endl;
   }
}

void yyerror(const char* s, char c) {
   cerr << "error (line " << yylineno << "): " << s << " \"" << c << "\"" << endl;
   error = true;
}

%}

%union {
   int             intVal;
   double          floatVal;
   char*           ident;
   char*           string;
   Expression*     exp;
   Statement*      stmt;
   StatementList*  stmtList;
   ParameterList*  paramList;
   ExpressionList* expList;
}

%token<intVal>   INTNUM    "int"
%token<floatVal> FLOATNUM  "float"
%token<ident>    IDENT     "identier"
%token<string>	 STRING     "string"
%token PLUSEQ  "+="
%token MINUSEQ "-="
%token MULTEQ  "*="
%token DIVEQ   "/="
%token MODEQ   "%="
%token POWEQ   "^="
%token INC     "++"
%token DEC     "--"
%token LE      "<="
%token GE      ">="
%token EQ      "=="
%token NE      "!="
%token IF      "if"
%token ELSE    "else"
%token WHILE   "while"
%token DEF     "def"
%token PRINT   "print"
%token RETURN  "return"
%token END     "end"
%token QUOTE	"\""
%token DOUBLENEWLINE "\n\n"

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left '<' LE '>' GE EQ NE
%left '+' '-'
%left '*' '/' '%' '^'
%nonassoc UMINUS

%type<exp>       expression
%type<exp>       func_call_exp
%type<stmt>      statement
%type<stmt>      assignment
%type<stmt>      print
%type<stmt>      function_def
%type<stmt>      function_call
%type<stmt>      if_else
%type<stmt>      while
%type<stmt>      return
%type<stmtList>  statement_list
%type<paramList> parameter_list
%type<expList>   expression_list

%%
program         : /* empty */
                | statement_list 
                     { Program($1).eval(); }
                ;

statement_list  : statement_list statement
                     { $1->add($2); $$ = $1; }
                | statement 
                     { StatementList* sl = new StatementList; sl->add($1); $$ = sl; }
                ;

statement       : assignment
                | print
                | function_def
                | if_else
                | while
                | return
                | function_call
                ;

assignment      : IDENT '=' expression
                     { $$ = new Assignment($1, $3);
                       delete [] $1;
                     }
             | IDENT '=' expression DOUBLENEWLINE
             { $$ = new Assignment($1, $3);
               delete [] $1;
             }
                | IDENT PLUSEQ expression
                     { $$ = new Assignment($1, new Addition(new Identifier($1), $3));
                       delete [] $1;
                     }
                | IDENT MINUSEQ expression
                     { $$ = new Assignment($1, new Subtraction(new Identifier($1), $3));
                       delete [] $1;
                     }
                | IDENT MULTEQ expression
                     { $$ = new Assignment($1, new Multiplication(new Identifier($1), $3));
                       delete [] $1;
                     }
                | IDENT DIVEQ expression
                     { $$ = new Assignment($1, new Division(new Identifier($1), $3));
                       delete [] $1;
                     }
                | IDENT MODEQ expression
                     { $$ = new Assignment($1, new Modulus(new Identifier($1), $3));
                       delete [] $1;
                     }
                | IDENT POWEQ expression
                     { $$ = new Assignment($1, new Exponent(new Identifier($1), $3));
                       delete [] $1;
                     }
                | INC IDENT
                     { $$ = new Assignment($2, new Addition(new Identifier($2), new Constant(1)));
                       delete [] $2;
                     } 
                | IDENT INC
                     { $$ = new Assignment($1, new Addition(new Identifier($1), new Constant(1)));
                       delete [] $1;
                     } 
                | DEC IDENT
                     { $$ = new Assignment($2, new Subtraction(new Identifier($2), new Constant(1)));
                       delete [] $2;
                     } 
                | IDENT DEC
                     { $$ = new Assignment($1, new Subtraction(new Identifier($1), new Constant(1)));
                       delete [] $1;
                     } 
                ;

print           : PRINT '(' STRING ',' expression')'
                     { $$ = new Print($5, $3);}
                 | PRINT '(' STRING ',' expression')' DOUBLENEWLINE
                     { $$ = new Print($5, $3);}
                ;

function_def    : DEF IDENT '(' parameter_list ')' ':' statement_list  DOUBLENEWLINE
                     {$$ = new FunctionDef($2, new Function($4, $7));
                       delete [] $2;
                     }
                | DEF IDENT '(' parameter_list ')' ':'  DOUBLENEWLINE
                     { $$ = new FunctionDef($2, new Function($4, new StatementList()));
                       delete [] $2;
                     }
                | DEF IDENT '(' ')' ':' statement_list DOUBLENEWLINE
                     { $$ = new FunctionDef($2, new Function(new ParameterList(), $6));
                       delete [] $2;
                     }
                | DEF IDENT '(' ')' ':'  DOUBLENEWLINE
                     { $$ = new FunctionDef($2, new Function(new ParameterList(), new StatementList()));
                       delete [] $2;
                     }
                ;

function_call   : IDENT '(' expression_list ')'
                     { $$ = new FunctionCall($1, $3);
                       delete [] $1;
                     }
                   ;

if_else         : IF expression ':' statement_list ELSE ':' statement_list 
                     { $$ = new IfElse($2, $4, $7); }
                | IF expression ':' ELSE ':' statement_list 
                     { $$ = new IfElse($2, new StatementList(), $6); }
                | IF expression ':' statement_list ELSE ':' 
                     { $$ = new IfElse($2, $4, new StatementList()); }
                | IF expression ':' ELSE ':' 
                     { $$ = new IfElse($2, new StatementList(), new StatementList()); }
                | IF expression ':' statement_list 
                     { $$ = new IfElse($2, $4); }
                | IF expression ':' 
                     { $$ = new IfElse($2, new StatementList()); }
                ;

while           : WHILE expression ':' statement_list DOUBLENEWLINE
                     { $$ = new While($2, $4); }
                | WHILE expression ':' DOUBLENEWLINE
                     { $$ = new While($2, new StatementList()); }
                ;

return          : RETURN expression
                     { $$ = new Return($2); }
                ;

parameter_list  : parameter_list ',' IDENT
                     { $1->add($3);
                       $$ = $1;
                       delete [] $3;
                     }
                | IDENT
                     { ParameterList* pl = new ParameterList();
                       pl->add($1); $$ = pl;
                       delete [] $1;
                     }
                ;
expression      : '(' expression ')'
                     { $$ = $2; }
                | QUOTE expression '=' QUOTE ',' expression
                     { $$ = $2; }
                | INTNUM
                     { $$ = new Constant($1); }
                | FLOATNUM
                     { $$ = new Constant($1); }
                | IDENT
                     { $$ = new Identifier($1);
                       delete [] $1;
                     }
                | expression '+' expression
                     { $$ = new Addition($1, $3); }
                | expression '-' expression
                     { $$ = new Subtraction($1, $3); }
                | expression '*' expression
                     { $$ = new Multiplication($1, $3); }
                | expression '/' expression
                     { $$ = new Division($1, $3); }
                | expression '%' expression
                     { $$ = new Modulus($1, $3); }
                | expression '^' expression
                     { $$ = new Exponent($1, $3); }
                | expression '<' expression
                     { $$ = new LessThan($1, $3); }
                | expression '>' expression
                     { $$ = new GreaterThan($1, $3); }
                | expression LE expression
                     { $$ = new LessThanOrEqualTo($1, $3); }
                | expression GE expression
                     { $$ = new GreaterThanOrEqualTo($1, $3); }
                | expression EQ expression
                     { $$ = new Equals($1, $3); }
                | expression NE expression
                     { $$ = new NotEquals($1, $3); }
                | '-' expression %prec UMINUS
                     { $$ = new Negation($2); }
                | func_call_exp
                ;

func_call_exp   : IDENT '(' expression_list ')'
                     { $$ = new FunctionCallExp($1, $3);
                       delete [] $1;
                     }
                ;

expression_list : /* empty*/
                     { $$ = new ExpressionList(); }
                | expression_list ',' expression
                     { $1->add($3);
                       $$ = $1;
                     }
                | expression
                     { ExpressionList* el = new ExpressionList();
                       el->add($1);
                       $$ = el;
                     }
                ;
%%

