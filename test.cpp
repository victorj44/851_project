#include <cstdio>
#include "HashFunction.h"
#include "tabulationHash/tabulationHash.h"

int main()
{
  HashFunction *hf = new TabulationHash(123);
  
  return 0;
}
