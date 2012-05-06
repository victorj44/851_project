#ifndef __TABULATION_HASH__
#define __TABULATION_HASH__

#include "../HashFunction.h"

class TabulationHash : public HashFunction
{
 public:
  TabulationHash();
  long hash(long key);
  long hash(string key);
};

#endif //__TABULATION_HASH__
