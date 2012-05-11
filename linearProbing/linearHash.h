#ifndef __LINEAR_PROBING_HASH__
#define __LINEAR_PROBING_HASH__

#include "../HashMapBase.h"

template<typename T>
class LinearHash : public HashMapBase<T>
{
 private:
  int64 size;
  HashFunction *hf;
  T *table;
 public:
 LinearHash(int64 size, HashFunction *hf) : size(size), hf(hf)
  {
    table = new T[size]; //?
  }
  
  ~LinearHash()
    {
      delete[] table;
    }
  
  void put(int64 key, T value)
  {
    
  }

  bool get(int64 key, T &retValue)
  {
    return false;
  }
};

#endif //__LINEAR_PROBING_HASH__
