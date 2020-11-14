#include <iostream>
#include <cstdlib>
#include "exception.h"
#include "number.h"
#include "symbolTable.h"
#include "functionTable.h"
#include "expression.h"
#include "function.h"
#include "exception.h"
#include "statement.h"

using std::cout;
using std::cerr;
using std::endl;

int Statement::getLineNumber() const {
   return lineNumber;
}

Assignment::~Assignment() {
   delete exp;
}

void Assignment::eval(SymbolTable& st, FunctionTable& ft) const {
   st[name] = exp->eval(st, ft);
}


FunctionCall::~FunctionCall() {
   delete expList;
}

void FunctionCall::eval(SymbolTable& st, FunctionTable& ft) const {
   // semi-hack: create const FunctionTable to ensure only accessor
   // operator[] is used - don't want to get a NULL function*
   const FunctionTable cft(ft);
   
   cft[name]->apply(st, ft, expList);
}


FunctionDef::~FunctionDef() {
   delete function;
}

void FunctionDef::eval(SymbolTable& st, FunctionTable& ft) const {
   ft[name] = function;
}

IfElse::~IfElse() {
   delete condition;
   delete trueList;
   delete falseList;
}

void IfElse::eval(SymbolTable& st, FunctionTable& ft) const {
   if (condition->eval(st, ft) > 0) {
      trueList->eval(st, ft);
   } else {
      falseList->eval(st, ft);
   }
}

While::~While() {
   delete condition;
   delete stmtList;
}

void While::eval(SymbolTable& st, FunctionTable& ft) const {
   while (condition->eval(st, ft) > 0) {
      stmtList->eval(st, ft);
   }
}

Print::~Print() {
   delete exp;
}

void Print::eval(SymbolTable& st, FunctionTable& ft) const {
   Number n(exp->eval(st, ft));
   cout  << chr << n << endl;
}

Return::~Return() {
   delete exp;
}

void Return::eval(SymbolTable& st, FunctionTable& ft) const {
   throw ReturnValue(exp->eval(st, ft), lineNumber);
}


StatementList::~StatementList() {
   for (list<Statement*>::const_iterator it = stmtList.begin(); it != stmtList.end(); ++it) {
      delete *it;
   }
}

void StatementList::add(Statement* stmt) {
   stmtList.push_back(stmt);
}

void StatementList::eval(SymbolTable& st, FunctionTable& ft) const {
   // eval() each statement in statement list
   list<Statement*>::const_iterator it;
   try {
      for (it = stmtList.begin(); it != stmtList.end(); ++it) {
         (*it)->eval(st, ft);
      }
   } catch (ParseException e) {
      // if we catch an exception indicating a semantic error, print it and bail out
      cerr << "error (line " << (*it)->getLineNumber() << "): " << e.what() << endl;
      exit(2);
   }
}
