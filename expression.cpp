#include "symbolTable.h"
#include "function.h"
#include "functionTable.h"
#include "expression.h"
#include <iostream>
#include <cmath>

Number Constant::eval(const SymbolTable &st, const FunctionTable &ft) const {
   return num;
}

Number Identifier::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return st[name];
}

Negation::~Negation() {
   delete op;
}

Number Negation::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return -(op->eval(st, ft));
}

FunctionCallExp::~FunctionCallExp() {
   delete argList;
}

Number FunctionCallExp::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return ft[name]->apply(st, ft, argList);
}

BinaryExpression::~BinaryExpression() {
   delete op1;
   delete op2;
}

Number Addition::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) + op2->eval(st, ft);
}

Number Subtraction::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) - op2->eval(st, ft);
}

Number Multiplication::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) * op2->eval(st, ft);
}

Number Division::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1 -> eval(st, ft) / op2->eval(st, ft);
}

Number Modulus::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) % op2->eval(st, ft);
}

Number Exponent::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) ^ op2->eval(st, ft);
}

Number LessThan::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) < op2->eval(st, ft);
}

Number GreaterThan::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) > op2->eval(st, ft);
}

Number LessThanOrEqualTo::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) <= op2->eval(st, ft);
}

Number GreaterThanOrEqualTo::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) >= op2->eval(st, ft);
}

Number Equals::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) == op2->eval(st, ft);
}

Number NotEquals::eval(const SymbolTable& st, const FunctionTable& ft) const {
   return op1->eval(st, ft) != op2->eval(st, ft);
}

void ExpressionList::add(Expression* exp) {
   expList.push_back(exp);
}

unsigned int ExpressionList::size() const {
   return expList.size();
}

list<Expression*>::const_iterator ExpressionList::begin() const {
   return expList.begin();
}

list<Expression*>::const_iterator ExpressionList::end() const {
   return expList.end();
}

ExpressionList::~ExpressionList() {
   for (list<Expression*>::iterator it = expList.begin(); it != expList.end(); ++it) {
      delete *it;
   }
}
