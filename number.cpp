#include <iostream>
#include <cstdlib>
#include <cmath>
#include "exception.h"
#include "number.h"

using std::ostream;
using std::fixed;

ostream& operator<<(ostream& out, const Number& num) {
   if (num.type == INT) {   
      return out << num.value.i;
   } else if (num.type == FLOAT) {
      return out << fixed << num.value.f;
   } else {
      throw UnknownType();
   }
}

bool operator==(const Number& lhs, const Number& rhs) {
   if (lhs.type == INT && rhs.type == INT) {
      return lhs.value.i == rhs.value.i;
   } else if (lhs.type == FLOAT && rhs.type == FLOAT) {
      return lhs.value.f == rhs.value.f;
   } else if (lhs.type == INT && rhs.type == FLOAT) {
      return lhs.value.i == rhs.value.f;
   } else if (lhs.type == FLOAT && rhs.type == INT) {
      return lhs.value.f == rhs.value.i;
   } else {
      throw UnknownType();
   }
}

bool operator!=(const Number& lhs, const Number& rhs) {
   return !(lhs == rhs);
}

bool operator<(const Number& lhs, const Number& rhs) {
   if (lhs.type == INT && rhs.type == INT) {
      return lhs.value.i < rhs.value.i;
   } else if (lhs.type == FLOAT && rhs.type == FLOAT) {
      return lhs.value.f < rhs.value.f;
   } else if (lhs.type == INT && rhs.type == FLOAT) {
      return lhs.value.i < rhs.value.f;
   } else if (lhs.type == FLOAT && rhs.type == INT) {
      return lhs.value.f < rhs.value.i;
   } else {
      throw UnknownType();
   }
}

bool operator>(const Number& lhs, const Number& rhs) {
   if (lhs.type == INT && rhs.type == INT) {
      return lhs.value.i > rhs.value.i;
   } else if (lhs.type == FLOAT && rhs.type == FLOAT) {
      return lhs.value.f > rhs.value.f;
   } else if (lhs.type == INT && rhs.type == FLOAT) {
      return lhs.value.i > rhs.value.f;
   } else if (lhs.type == FLOAT && rhs.type == INT) {
      return lhs.value.f > rhs.value.i;
   } else {
      throw UnknownType();
   }
}

bool operator<=(const Number& lhs, const Number& rhs) {
   return !(lhs > rhs);
}

bool operator>=(const Number& lhs, const Number& rhs) {
   return !(lhs < rhs);
}

Number& Number::operator=(const Number& rhs) {
   type  = rhs.type;
   value = rhs.value;
   return *this;
}

Number& Number::operator+=(const Number& rhs) {
   *this = *this + rhs;
   return *this;
}

Number& Number::operator-=(const Number& rhs) {
   *this = *this - rhs;
   return *this;
}

Number& Number::operator*=(const Number& rhs) {
   *this = *this * rhs;
   return *this;
}

Number& Number::operator/=(const Number& rhs) {
   *this = *this / rhs;
   return *this;
}

Number& Number::operator%=(const Number& rhs) {
   *this = *this % rhs;
   return *this;
}

Number& Number::operator^=(const Number& rhs) {
   *this = *this ^ rhs;
   return *this;
}

Number Number::operator+(const Number& rhs) const {
   if (type == INT && rhs.type == INT) {
      return Number(value.i + rhs.value.i);
   } else if (type == FLOAT && rhs.type == FLOAT) {
      return Number(value.f + rhs.value.f);
   } else if (type == INT && rhs.type == FLOAT) {
      return Number(value.i + rhs.value.f);
   } else if (type == FLOAT && rhs.type == INT) {
      return Number(value.f + rhs.value.i);
   } else {
      throw UnknownType();
   }
}

Number Number::operator-(const Number& rhs) const {
   if (type == INT && rhs.type == INT) {
      return Number(value.i - rhs.value.i);
   } else if (type == FLOAT && rhs.type == FLOAT) {
      return Number(value.f - rhs.value.f);
   } else if (type == INT && rhs.type == FLOAT) {
      return Number(value.i - rhs.value.f);
   } else if (type == FLOAT && rhs.type == INT) {
      return Number(value.f - rhs.value.i);
   } else {
      throw UnknownType();
   }
}

Number Number::operator*(const Number& rhs) const {
   if (type == INT && rhs.type == INT) {
      return Number(value.i * rhs.value.i);
   } else if (type == FLOAT && rhs.type == FLOAT) {
      return Number(value.f * rhs.value.f);
   } else if (type == INT && rhs.type == FLOAT) {
      return Number(value.i * rhs.value.f);
   } else if (type == FLOAT && rhs.type == INT) {
      return Number(value.f * rhs.value.i);
   } else {
      throw UnknownType();
   }
}

Number Number::operator/(const Number& rhs) const {
   if (type == INT && rhs.type == INT) {
      if (rhs.value.i == 0) {
         throw DivideByZero();
      }
      return Number((value.i / rhs.value.i));
   } else if (type == FLOAT && rhs.type == FLOAT) {
      return Number(value.f / rhs.value.f);
   } else if (type == INT && rhs.type == FLOAT) {
      return Number(value.i / rhs.value.f);
   } else if (type == FLOAT && rhs.type == INT) {
      return Number(value.f / rhs.value.i);
   } else {
      throw UnknownType();
   }
}

Number Number::operator%(const Number& rhs) const {
   if (type == INT && rhs.type == INT) {
      if (rhs.value.i == 0) {
         throw ModByZero();
      }
      return Number(value.i % rhs.value.i);
   } else {
      throw FloatingPointMod();
   }
}

Number Number::operator^(const Number& rhs) const {
   if (type == INT && rhs.type == INT) {
      return Number((int) pow(value.i, rhs.value.i));
   } else if (type == FLOAT && rhs.type == FLOAT) {
      return Number(pow(value.f, rhs.value.f));
   } else if (type == INT && rhs.type == FLOAT) {
      return Number(pow(value.i, rhs.value.f));
   } else if (type == FLOAT && rhs.type == INT) {
      return Number(pow(value.f, rhs.value.i));
   } else {
      throw UnknownType();
   }
}

Number Number::operator-() const {
   if (type == INT) {
      return Number(-value.i);
   } else if (type == FLOAT) {
      return Number(-value.f);
   } else {
      throw UnknownType();
   }
}
