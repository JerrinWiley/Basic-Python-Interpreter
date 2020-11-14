#ifndef FUNCTION_H
#define FUNCTION_H

#include <list>
#include <string>

using std::list;
using std::string;

class SymbolTable;
class FunctionTable;
class ExpressionList;
class StatementList;
class FunctionTable;
class Number;

class ParameterList {
public:
   unsigned int size() const;
   void add(const string&);

   list<string>::const_iterator begin() const;
   list<string>::const_iterator end()   const;

private:
   list<string> paramList;
};

class Function {
public:
   Function(ParameterList* pList, StatementList* sList) : paramList(pList), stmtList(sList) { }
   ~Function();
   
   Number apply(const SymbolTable&, const FunctionTable&, ExpressionList*) const;
   Number apply(const SymbolTable& st, const FunctionTable& ft) const;

private:
   ParameterList* paramList;
   StatementList* stmtList;
};

#endif
