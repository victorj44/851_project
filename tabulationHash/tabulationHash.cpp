#include "tabulationHash.h"
#include <ctime>
#include <cstdlib>

TabulationHash::TabulationHash(int size)
{
  srand(time(NULL));
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < (1<<8); j++)
      T[i][j] = ((int64)rand() << 32) | rand();
}

int64 TabulationHash::hashInt(int64 key)
{
  int64 ret = 0;
  for (int i = 0; i < 8; i++)
    {
      ret ^= T[i][key % (1<<8)];
      key >>= 8;
    }
  return ret;
}

int64 TabulationHash::hashString(string key)
{
  int64 ret = 0;
  for (int i = 0; i < key.length(); i++)
    ret ^= T

  return ret;
}
