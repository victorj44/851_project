#ifndef __HASH_FUNCTION__
#define __HASH_FUNCTION__

#include <string>
#include <cstdlib>
using namespace std;

typedef unsigned long long int64;
typedef unsigned int int32;

class HashFunction
{
 public:
  HashFunction() { }
  virtual int64 hash(int64 key) = 0;
  virtual void initRandom() = 0;
  // virtual int64 hash(string key) = 0;
};

#endif// __HASH_FUNCTION__

