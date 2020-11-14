#include "exception.h"
#include "functionTable.h"

Function* FunctionTable::operator[](const string& ident) const {
   // ensure function is defined
   if (funcTable.count(ident) == 0) {
      throw UndefinedFunction();
   }
   // return value
   return funcTable.find(ident)->second;
}

Function*& FunctionTable::operator[](const string& ident) {
   // return reference to entry in funcTable
   return funcTable[ident];
}

