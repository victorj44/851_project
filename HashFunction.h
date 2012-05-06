#ifndef __HASH_FUNCTION__
#define __HASH_FUNCTION__

#include <string>
using namespace std;

class HashFunction
{
 public:
  HashFunction() { }
  virtual long hash(long key) = 0;
  virtual long hash(string key) = 0;
};

#endif// __HASH_FUNCTION__

