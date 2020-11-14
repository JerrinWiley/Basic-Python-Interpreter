#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "number.h"

extern int yylineno;

class ParseException  {
public:
   virtual int getLineNumber() const;
   virtual const char* what() const throw();

protected:
   ParseException(const char* m) : msg(m), lineNumber(yylineno) { }
   const char* msg;
   int lineNumber;
};


class DivideByZero : public ParseException {
public:
   DivideByZero() : ParseException("divide by zero") { }
};


class ModByZero : public ParseException {
public:
   ModByZero() : ParseException("mod by zero") { }
};


class FloatingPointMod : public ParseException {
public:
   FloatingPointMod() : ParseException("mod on floating point value") { }
};


class UnknownType : public ParseException {
public:
   UnknownType() : ParseException("operand has unknown type") { }
};


class ParameterMismatch : public ParseException {
public:
   ParameterMismatch() : ParseException("number of parameters passed differs from function signature") { }
};


class UnboundIdentifier : public ParseException {
public:
   UnboundIdentifier() : ParseException("use of unbound identfier") { }
};


class UndefinedFunction : public ParseException {
public:
   UndefinedFunction() : ParseException("call of undefined function") { }
};


class ReturnStatementOutsideOfFunction : public ParseException {
public:
   ReturnStatementOutsideOfFunction() : ParseException("return statement exists outside of a function") { }
};


class ReturnValue {
public:
   ReturnValue(const Number& num, int line) : value(num), lineNumber(line) { }
   
   const char* what() const throw();
   Number getValue() const;
   int getLineNumber() const;

private:
   Number value;
   int    lineNumber;
};

#endif
