#ifndef __HOPSCOTCH_HASH_H__
#define __HOPSCOTCH_HASH_H__

#include "../HashMapBase.h"

template<typename T>
class HopscotchHash : public HashMapBase<T>
{
 private:
  int64 size;
  HashFunction *hf;
  T *values;
  int64 nprobes;
 public:
 HopscotchHash(int64 size, HashFunction *hf) : size(size), hf(hf)
  {
    nprobes = 0;
  }
  
  ~HopscotchHash()
    {
      delete[] values;
    }
  
  void put(int64 key, T value)
  {
    
  }

  bool get(int64 key, T &retValue)
  {
    return false;
  }

  int64 getnprobes() { return nprobes; }

};

#endif __HOPSCOTCH_HASH_H__
