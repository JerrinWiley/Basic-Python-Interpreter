#ifndef PROGRAM_H
#define PROGRAM_H

#include "symbolTable.h"
#include "functionTable.h"

class StatementList;

class Program {
public:
   Program(StatementList* stmtList) : statementList(stmtList) { }
   ~Program();
   int eval();

private:
   StatementList* statementList;
   SymbolTable    st;
   FunctionTable  ft;
};

#endif
