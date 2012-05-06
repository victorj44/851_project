#include "multiplicationHash.h"

MultiplicationHash::MultiplicationHash(int size)
{
  srand(time(NULL));
  this->size = size;
  this->p = 2305843009213693951ULL;
  this->a = (((int64)rand() << 32) | rand()) % (p-1) + 1; // guaranteed to be > 0 and < p
  this->b = (((int64)rand() << 32) | rand()) % p;
}

int64 MultiplicationHash::hash(int64 key)
{
  return ((a * key + b) % p) % size;
}

int64 MultiplicationHash::hash(string key)
{
  int64 a2 = (((int64)rand() << 32) | rand()) % (p-1) + 1;
  int64 pow = 1;
  int64 sum = 0;
  for (unsigned int i = 0; i < key.length(); i++) {
    sum += key[i] * pow % p;
    pow *= a2;
  }
  return this->hash(sum);
}
