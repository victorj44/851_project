#ifndef __HASH_FUNCTION__
#define __HASH_FUNCTION__

#include <string>
using namespace std;

#define int64 int64_t

class HashFunction
{
 public:
  HashFunction() { }
  virtual int64 hashInt(int64 key) = 0;
  virtual int64 hashString(string key) = 0;
};

#endif// __HASH_FUNCTION__

