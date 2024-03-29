
#include "tabulationHash.h"
#include <ctime>
#include <cstdlib>

TabulationHash::TabulationHash(int64 size)
{
  srand(time(NULL));
  this->size = size;
  this->initRandom();
}

void TabulationHash::initRandom()
{
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < (1<<8); j++)
      T[i][j] = ((int64)rand() << 32) | rand();
}

int64 TabulationHash::hash(int64 key)
{
  int64 ret = 0;
  for (int i = 0; i < 8; i++)
    {
      ret ^= T[i][key & 0xFF];
      key >>= 8;
    }
  return ret % size;
}

int64 TabulationHash::hash(string key)
{
  int64 ret = 0;
  for (unsigned int i = 0; i < key.length(); i++)
    ret ^= T[i & 0x7][(int)key[i]];

  return ret % size;
}
