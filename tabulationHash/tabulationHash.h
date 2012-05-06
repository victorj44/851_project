#ifndef __TABULATION_HASH__
#define __TABULATION_HASH__

#include "../HashFunction.h"

class TabulationHash : public HashFunction
{
 private:
  int size;
  int64 T[8][1 << 8];
 public:
  TabulationHash(int size);
  int64 hashInt(int64 key);
  int64 hashString(string key);
};

#endif //__TABULATION_HASH__
