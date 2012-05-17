#ifndef __HASH_MAP_BASE__
#define __HASH_MAP_BASE__

#include "HashFunction.h"
#include <cstring>

template<typename T>
class HashMapBase
{
 public:
  HashMapBase() { }
  
  virtual bool put(int64 key, T value) = 0;
  //virtual void put(string key, T value) = 0;
  virtual bool get(int64 key, T &retValue) = 0;
  virtual int64 getnprobes() = 0;
  virtual void print() = 0;
  //virtual bool find(int64 key);
  //virtual bool get(string key, T &retValue) = 0;
};


#endif //__HASH_MAP_BASE__
