#ifndef __QUADRATIC_PROBING__
#define __QUADRATIC_PROBING__

#include "../HashMapBase.h"


template<typename T>
class QuadraticProbing : public HashMapBase<T>
{
 private:
  static const int64 EMPTY = (int64)-1;
  int64 size;
  // we will assume c1 = c2 = 1/2
  // double c1;
  // double c2;
  HashFunction *hf;
  int64* keys;
  T* values;
  int64 nprobes;

 public:
  QuadraticProbing(int64 size, HashFunction *hf): size(size), hf(hf)
  {
    values = new T[size];
    keys = new int64[size];
    memset(keys, -1, size * sizeof(int64));
    nprobes = 0;
  }

  ~QuadraticProbing()
  {
    delete[] values;
    delete[] keys;
  }

  void put(int64 key, T value) {
    int64 h = this->hf->hash(key);
    int64 idx = h;
    int i = 1;
    nprobes++;
    while (keys[idx] != EMPTY && keys[idx] != key) {
      idx = (h + (i/2) + (i*i/2) + ((i & 1) == 0 ? 0 : 1)) % size; // if i is odd, add one because of rounding down
      ++i;
      nprobes++;
    }
    keys[idx] = key;
    values[idx] = value;
  }

  // void put(string key, T value);

  bool get(int64 key, T &retValue) {
    int64 h = this->hf->hash(key);
    int64 idx = h;
    int i = 1;
    nprobes++;
    while (keys[idx] != EMPTY && keys[idx] != key) {
      idx = (h + (i/2) + (i*i/2) + ((i & 1) == 0 ? 0 : 1)) % size; // if i is odd, add one because of rounding down
      ++i;
      nprobes++;
    }
    if (keys[idx] == EMPTY) {
      return false;
    }
    retValue = values[idx];
    return true;
  }
  // bool get(string key, T &retValue);
  
  int64 getnprobes() { return nprobes; }
  void print() { }
};

#endif // __QUADRATIC_PROBING__
