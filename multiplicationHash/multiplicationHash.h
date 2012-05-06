#ifndef __MULTIPLICATION_HASH__
#define __MULTIPLICATION_HASH__

#include "../HashFunction.h"

class MultiplicationHash : public HashFunction
{
 public:
  MultiplicationHash();
  int64 hash(int64 key);
  int64 hash(string key);
};

#endif //__MULTIPLICATION_HASH__
