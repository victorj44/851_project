#ifndef __LINEAR_PROBING_HASH__
#define __LINEAR_PROBING_HASH__

#include "../HashMapBase.h"

template<typename T>
class LinearHash : public HashMapBase<T>
{
 private:
  static const int64 EMPTY = (int64)-1;
  int64 size;
  HashFunction *hf;
  T *values;
  int64 *keys;
  int64 nprobes;
 public:
 LinearHash(int64 size, HashFunction *hf) : size(size), hf(hf)
  {
    keys = new int64[size];
    values = new T[size];
    memset(keys, -1, sizeof(keys) * size);
    nprobes = 0;
  }
  
  ~LinearHash()
    {
      delete[] values;
      delete[] keys;
    }
  
  void put(int64 key, T value)
  {
    int64 h = hf->hash(key);
    nprobes++;
    while (keys[h] != EMPTY && keys[h] != key)
      {
	nprobes++;
	h++;
	if (h >= size)
	  h -= size;
      }
    keys[h] = key;
    values[h] = value;
  }

  bool get(int64 key, T &retValue)
  {
    int64 h = hf->hash(key);
    bool ret = false;

    nprobes++;
    while (keys[h] != EMPTY)
      {
	nprobes++;
	if (keys[h] == key)
	  {
	    ret = true;
	    retValue = values[h];
	    break;
	  }

	h++;
	if (h >= size)
	  h -= size;
      }

    return ret;
  }
  
  int64 getnprobes() { return nprobes; }
};

#endif //__LINEAR_PROBING_HASH__
