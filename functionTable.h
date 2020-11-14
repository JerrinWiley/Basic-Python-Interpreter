#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <map>
#include <string>

using std::map;
using std::string;

class Function;

class FunctionTable {
public:
   Function*& operator[](const string&);
   Function* operator[](const string&) const;

private:
   map<string,Function*> funcTable;
};

#endif
