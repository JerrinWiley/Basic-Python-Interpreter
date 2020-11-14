#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>
#include "number.h"

using std::map;
using std::string;

class SymbolTable {
public:
   Number  operator[](const string&) const;
   Number& operator[](const string&);

private:
   map<string,Number> symTable;
};

#endif
