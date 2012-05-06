#include <cstdio>
#include "HashFunction.h"
#include "tabulationHash/tabulationHash.h"
#include "multiplicationHash/multiplicationHash.h"

int main()
{
  HashFunction *hf = new TabulationHash();
  HashFunction *hf2 = new MultiplicationHash();

  return 0;
}
