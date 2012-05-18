#ifndef __HOPSCOTCH_HASH_H__
#define __HOPSCOTCH_HASH_H__

#include "../HashMapBase.h"

template<typename T>
class HopscotchHash : public HashMapBase<T>
{
 private:
  static const int64 EMPTY = (int64)-1;
  static const int64 MAXH = 64;
  int64 size;
  HashFunction *hf;
  T *values;
  int64 *keys;
  int64 nprobes;

  //shifts everything in the hash table
  //assumes that keys[inith + dist] is empty
  //makes space somewhere in [inith, inith + H - 1]
  //assumes size > H
  int64 reshuffle(int64 inith, int64 dist)
  {
    while (dist >= MAXH)
    {
      int64 curpos = inith + dist - MAXH + 1;
      bool done = false;
      
      for (int64 i = 0; i < MAXH - 1 && !done; i++)
      {
	int64 tmphash = hf->hash(keys[(curpos + i)%size]);
	//keys[curpos + i] hashed somewhere between [curpos + 1, curpos + H]
	//curpos + H is empty, so swap these two and mark the appropriate pointers
	if (tmphash >= curpos)
	{
	  keys[ (curpos + MAXH - 1)%size ] = keys[ (curpos + i)%size ];
	  values[ (curpos + MAXH - 1)%size ] = values[ (curpos + i)%size ];
	  keys[ (curpos + i)%size ] = EMPTY;
	  
	  dist -= MAXH - i - 1;
	  if (MAXH - i - 1 == 0)
	  {
	    printf("!!!!!!!!! NOT MOVING\n");
	  }
	  
	  done = true;
	}
      }
	
      //this should not happen unless the table is entirely full
      if (!done)
      {
	return EMPTY;
      }
    }
    return (inith + dist) % size;
  }

 public:
 HopscotchHash(int64 size, HashFunction *hf) : size(size), hf(hf)
  {
    nprobes = 0;
    values = new T[size];
    keys = new int64[size];
    memset(keys, -1, sizeof(keys) * size); //initializes to EMPTY
  }
  
  ~HopscotchHash()
    {
      delete[] values;
    }
  
  //returns false if fails to insert
  bool put(int64 key, T value)
  {
    nprobes++;
    int64 h = hf->hash(key);
    int64 freepos = h;
    int64 dist = 0;
    while (keys[freepos] != EMPTY)
      {
	nprobes++;
	freepos++;
	dist++;
	if (dist >= size)
	  break;
	if (freepos >= size)
	  freepos -= size;
      }

    //table full, can't put anything in
    if (dist >= size)
      {
	// Table full
	return false;
      }

    if (dist >= MAXH)
      freepos = reshuffle(h, dist);

    if (freepos >= size)
      {
	// Can't get an empty slot near
	return false;
      }

    keys[freepos] = key;
    values[freepos] = value;
    return true;
  }

  bool get(int64 key, T &retValue)
  {
    bool ret = false;
    int64 h = hf->hash(key);
    for (int64 i = 0; i < MAXH; i++)
    {
      nprobes++;
      if (keys[h] == key)
      {
	retValue = values[h];
	ret = true;
	break;
      }

      h++;
      if (h >= size)
	h -= size;
    }
    
    return ret;
  }

  int64 getnprobes() { return nprobes; }

  void print()
  {
    printf("\n");
    for (int i = 0; i < size; i += 10)
    {
      printf("%d: ", i);
      for (int j = 0; j < 10; j++)
	if (keys[i + j] == EMPTY)
	  printf("E ");
	else
	  printf("%llu ", keys[i + j]);
      printf("\n");
    }
  }

};

#endif //__HOPSCOTCH_HASH_H__
