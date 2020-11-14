#include "exception.h"
#include "symbolTable.h"
#include "functionTable.h"
#include "statement.h"
#include "expression.h"
#include "function.h"

unsigned int ParameterList::size() const {
   return paramList.size();
}

void ParameterList::add(const string& s) {
   paramList.push_back(s);
}

list<string>::const_iterator ParameterList::begin() const {
   return paramList.begin();
}

list<string>::const_iterator ParameterList::end() const {
   return paramList.end();
}

Function::~Function() {
   delete paramList;
   delete stmtList;
}

Number Function::apply(const SymbolTable& st, const FunctionTable& ft) const {
   // create dummy empty expressionList to pass to no-arg function
   ExpressionList* el = new ExpressionList();

   // evaluate the function
   Number n = apply(st, ft, el);
   delete el;
   return n;
}

Number Function::apply(const SymbolTable& st, const FunctionTable& ft, ExpressionList* argList) const {

   // copy existing symbol and function tables into local tables
   SymbolTable localST(st);
   FunctionTable localFT(ft);

   // ensure the correct number of args were passed
   if (paramList->size() != argList->size()) {
      throw ParameterMismatch();
   }

   // bind passed arguments to formal parameters in local symbol table
   list<string>::const_iterator      formalIt = paramList->begin();
   list<Expression*>::const_iterator argIt    = argList->begin();

   while (formalIt != paramList->end()) {
      localST[*formalIt] = (*argIt)->eval(st, ft);
      ++formalIt;
      ++argIt;
   } 

   // execute all statements in function. If the function throws a return value, return it
   try {
      stmtList->eval(localST, localFT);
   } catch (ReturnValue r) {
      return r.getValue();
   }
   
   // else, the function had no return statement. Return default 0.
   return Number(0);
}
