#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <list>
#include <iostream>

using std::string;
using std::list;

extern int yylineno;

class SymbolTable;
class FunctionTable;
class Function;
class Expression;
class ExpressionList;

class Statement {
public:
   virtual ~Statement() {};

   virtual void eval(SymbolTable&, FunctionTable&) const = 0;
   virtual int  getLineNumber() const;

protected:
   Statement()      : lineNumber(yylineno-1) { }
   Statement(int i) : lineNumber(i) { }
   int lineNumber;
};


class Assignment: public Statement {
public:
   Assignment(const string& n, Expression *e) : name(n), exp(e) { }
   ~Assignment();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   string      name;
   Expression* exp;
};


class StatementList {
public:
   ~StatementList();

   void eval(SymbolTable&, FunctionTable&) const;
   void add(Statement*);

private:
   list<Statement*> stmtList;
};


class FunctionCall : public Statement {
public:
   FunctionCall(const string& n, ExpressionList* el) : Statement(yylineno), name(n), expList(el) { }
   ~FunctionCall();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   string          name;
   ExpressionList* expList;
};


class FunctionDef : public Statement {
public:
   FunctionDef(const string& n, Function* fun) : name(n), function(fun) { }
   ~FunctionDef();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   string    name;
   Function* function;
};


class IfElse : public Statement {
public:
   IfElse(Expression *cond, StatementList* tList, StatementList* fList) : condition(cond), trueList(tList), falseList(fList) { }
   IfElse(Expression *cond, StatementList* tList) : condition(cond), trueList(tList), falseList(new StatementList()) { }
   ~IfElse();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   Expression*    condition;
   StatementList* trueList;
   StatementList* falseList;
};


class While : public Statement {
public:
   While(Expression* cond, StatementList* sList) : condition(cond), stmtList(sList) { }
   ~While();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   Expression*    condition;
   StatementList* stmtList;
};


class Print : public Statement {
public:
   Print(Expression* e) : exp(e) { }
   Print(Expression* e, char* c) : exp(e), chr(c) { }
   
   ~Print();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   Expression* exp;
   char* chr;	
};


class Return: public Statement {
public:
   Return(Expression* e) : exp(e) { }
   ~Return();

   void eval(SymbolTable&, FunctionTable&) const;

private:
   Expression* exp;
};

#endif
