#include <iostream>
#include <cstdio>

using std::cerr;
using std::endl;

extern int yyparse();
extern int parseResult;
extern FILE* yyin;

int main(int argc, char** argv) {
   
   // if a filename was passed on the command line, attempt to open handle for parsing
   if (argc > 1) {
      yyin = fopen(argv[1], "r+");
   
      if (yyin == NULL) {
         cerr << "error: could not open file \"" << argv[1] << "\" for reading" << endl;
         return 3;
      }
   }

   // else, we are reading from STDIN
   yyparse();
   
   return parseResult;
}
