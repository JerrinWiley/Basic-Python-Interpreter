#include "exception.h"

const char* ParseException::what() const throw() {
   return msg;
}

int ParseException::getLineNumber() const {
   return lineNumber;
}

const char* ReturnValue::what() const throw() {
   return "a function returned a value (no error occurred)";
}

Number ReturnValue::getValue() const {
   return value;
}

int ReturnValue::getLineNumber() const {
   return lineNumber;
}
