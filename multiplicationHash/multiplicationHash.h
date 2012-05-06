#ifndef __MULTIPLICATION_HASH__
#define __MULTIPLICATION_HASH__

#include "../HashFunction.h"

class MultiplicationHash : public HashFunction
{
 private:
  int size;
  int64 p;
  int64 a, b;
 public:
  MultiplicationHash(int size);
  int64 hash(int64 key);
  int64 hash(string key);
};

#endif //__MULTIPLICATION_HASH__
