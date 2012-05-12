#ifndef __CUCKOO_HASHING__
#define __CUCKOO_HASHING__

#include "../HashMapBase.h"
#include <algorithm>

template<typename T>
class CuckooHashing : public HashMapBase<T>
{
 private:
  static const int64 EMPTY = (int64)-1;
  static const int64 LOOP_PER_TABLE = 20;
  int64 size;
  int d;
  HashFunction **hf;
  T **values; // d-ary tables
  int64 **keys; // d-ary tables

  T **newValues;
  int64 **newKeys;

 public:
 CuckooHashing(int64 size, HashFunction **hf, int d): size(size), d(d), hf(hf)
 {
    values = new T*[d];
    keys = new int64*[d];
    newValues = new T*[d];
    newKeys = new int64*[d];
    for (int i = 0; i < d; ++i) 
    {
      values[i] = new T[size];
      keys[i] = new int64[size];
      memset(keys[i], -1, size * sizeof(keys[i]));

      newValues[i] = new T[size];
      newKeys[i] = new int64[size];
      memset(newKeys[i], -1, size * sizeof(newKeys[i]));
    }
  }
  
  ~CuckooHashing()
  {
    for (int i = 0; i < d; ++i)
    {
      delete[] values[i];
      delete[] keys[i];

      delete[] newValues[i];
      delete[] newKeys[i];
    }
    delete[] values;
    delete[] keys;
    
    delete[] newValues;
    delete[] newKeys;
  }

  void put(int64 key, T value)
  {
    while (!putSpecific(key, value, this->keys, this->values)) {
      rehash(true); // if we are in a cycle, rehash and try again
    }
  }

  bool putSpecific(int64 key, T value, int64 **keysDest, T **valuesDest)
  {
    int maxLoop = LOOP_PER_TABLE * d;
    int i = 0;
    while (maxLoop > 0) {
      int64 h = hf[i]->hash(key);
      if (keysDest[i][h] == EMPTY || keysDest[i][h] == key) {
        keysDest[i][h] = key;
	valuesDest[i][h] = value;
        return true;
      }
      // If slot not empty, put in anyway, and kick out what's there to the next table
      swap(key, keysDest[i][h]);
      swap(value, valuesDest[i][h]);
      i = (i + 1) % d;
      --maxLoop;
    }
    return false;
  }

  bool get(int64 key, T &retValue)
  {
    for (int i = 0; i < d; ++i) {
      int64 h = hf[i]->hash(key);
      if (keys[i][h] == EMPTY) return false;
      if (keys[i][h] == key) {
        retValue = values[i][h];
        return true;
      }
    }
    return false;
  }

  void rehash(bool first)
  {
    bool stop = false;
    // printf("Entering rehash\n");
    for (int i = 0; i < d; ++i) 
    {
      hf[i]->initRandom();
      memset(newKeys[i], -1, size * sizeof(newKeys[i]));
    }

    for (int i = 0; i < d && !stop; ++i) {
      for (int64 j = 0; j < size && !stop; ++j) {
	if (keys[i][j] != EMPTY) {
	  if (!putSpecific(keys[i][j], values[i][j], newKeys, newValues)) {
	    rehash(false); // Rehash again, but don't swap the values
	    stop = true;
	  }
	}
      }
    }
    
    if (first) {
      for (int i = 0; i < d; ++i) {
	swap(keys[i], newKeys[i]);
	swap(values[i], newValues[i]);
      }
    }
    //printf("Exiting rehash\n");
  }

};
#endif // __CUCKOO_HASHING__
