#ifndef NUMBER_H
#define NUMBER_H

#include <iosfwd>
#include<cmath>

using std::ostream;

typedef enum Type {
   INT,
   FLOAT
} Type;

typedef union Value {
   Value(int    _i) : i(_i) { }
   Value(double _f) : f(_f) { }

   int    i;
   double f;
} Value;

class Number {
public:
   Number()                 : type(INT),   value(0)   { }
   Number(const int    val) : type(INT),   value(val) { }
   Number(const double val) : type(FLOAT), value(val) { }

   friend ostream& operator<< (ostream&,      const Number&);
   friend bool     operator== (const Number&, const Number&);
   friend bool     operator!= (const Number&, const Number&);
   friend bool     operator<  (const Number&, const Number&);
   friend bool     operator>  (const Number&, const Number&);
   friend bool     operator<= (const Number&, const Number&);
   friend bool     operator>= (const Number&, const Number&);

   Number& operator=  (const Number&);
   Number& operator+= (const Number&);
   Number& operator-= (const Number&);
   Number& operator*= (const Number&);
   Number& operator/= (const Number&);
   Number& operator%= (const Number&);
   Number& operator^= (const Number&);

   Number  operator+  (const Number&) const;
   Number  operator-  (const Number&) const;
   Number  operator*  (const Number&) const;
   Number  operator/  (const Number&) const;
   Number  operator%  (const Number&) const;
   Number  operator^  (const Number&) const;
   Number  operator-  () const;

private:
   Type  type;
   Value value;
};

#endif
