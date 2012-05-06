#ifndef __TABULATION_HASH__
#define __TABULATION_HASH__

#include "../HashFunction.h"

class TabulationHash : public HashFunction
{
 private:
  int64 size;
  int64 T[8][1 << 8];
 public:
  TabulationHash(int64 size);
  int64 hash(int64 key);
  int64 hash(string key);
};

#endif //__TABULATION_HASH__
