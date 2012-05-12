#ifndef __HASH_FUNCTION__
#define __HASH_FUNCTION__

#include <string>
#include <cstdlib>
using namespace std;

#define int64 unsigned long long

class HashFunction
{
 public:
  HashFunction() { }
  virtual int64 hash(int64 key) = 0;
  virtual void initRandom() = 0;
  // virtual int64 hash(string key) = 0;
};

#endif// __HASH_FUNCTION__

