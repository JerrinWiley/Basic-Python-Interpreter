#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <list>
#include "number.h"

using std::string;
using std::list;

class SymbolTable;
class FunctionTable;
class ExpressionList;
class Number;

class Expression {
public:
   virtual ~Expression() {};
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const = 0;

protected:
   Expression() { };
};


class Constant : public Expression {
public:
   Constant(const Number& n) : num(n) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;

private:
   Number num;
};


class Identifier : public Expression {
public:
   Identifier(const string& n) : name(n) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;

private:
   string name;
};


class Negation : public Expression {
public:
   Negation(Expression* e) : op(e) { }
   ~Negation();
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;

private:
   Expression* op;
};


class FunctionCallExp : public Expression {
public:
   FunctionCallExp(string n, ExpressionList* aList) : name(n), argList(aList) { }
   ~FunctionCallExp();
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;

private:
   string name;
   ExpressionList* argList;
};


class BinaryExpression : public Expression {
public:
   ~BinaryExpression();
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const = 0;

protected:
   BinaryExpression(Expression* e1, Expression* e2) : op1(e1), op2(e2) { }
   Expression* op1;
   Expression* op2;
};


class Addition : public BinaryExpression {
public:
   Addition(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class Subtraction : public BinaryExpression {
public:
   Subtraction(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class Multiplication : public BinaryExpression {
public:
   Multiplication(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class Division : public BinaryExpression {
public:
   Division(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class Modulus : public BinaryExpression {
public:
   Modulus(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class Exponent : public BinaryExpression {
public:
   Exponent(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class LessThan : public BinaryExpression {
public:
   LessThan(Expression* e1, Expression *e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class GreaterThan : public BinaryExpression {
public:
   GreaterThan(Expression* e1, Expression *e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
   
};


class LessThanOrEqualTo : public BinaryExpression {
public:
   LessThanOrEqualTo(Expression* e1, Expression *e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class GreaterThanOrEqualTo : public BinaryExpression {
public:
   GreaterThanOrEqualTo(Expression* e1, Expression *e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class Equals : public BinaryExpression {
public:
   Equals(Expression* e1, Expression *e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};


class NotEquals : public BinaryExpression {
public:
   NotEquals(Expression* e1, Expression *e2) : BinaryExpression(e1, e2) { }
   
   virtual Number eval(const SymbolTable&, const FunctionTable&) const;
};

class ExpressionList {
public:
   ExpressionList() { }
   ~ExpressionList();

   void add(Expression* exp); 

   unsigned int size() const;
   
   list<Expression*>::const_iterator begin() const;
   list<Expression*>::const_iterator end()   const;

private:
   list<Expression*> expList;
};

#endif
