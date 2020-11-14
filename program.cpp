#include <iostream>
#include <cstdlib>
#include "exception.h"
#include "statement.h"
#include "function.h"
#include "program.h"

using std::cerr;
using std::endl;

Program::~Program() {
   delete statementList;
}

int Program::eval() {
   try {
      // execute all statements in program
      statementList->eval(st, ft);
   
      // call the main function, if defined
      Function* main = ft["main"];
      if (main != NULL) {
         main->apply(st, ft);
      }
   } catch (ParseException e) {
      cerr << "error (line " << e.getLineNumber() << "): " << e.what() << endl;
      return 2;
   } catch (ReturnValue e) {
      cerr << "error (line " << e.getLineNumber() << "): " << "return statement outside of function" << endl;
      return 2;
   }
   return 0;
}

