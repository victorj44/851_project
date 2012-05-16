#ifndef __HOPSCOTCH_HASH_H__
#define __HOPSCOTCH_HASH_H__

#include "../HashMapBase.h"

template<typename T>
class HopscotchHash : public HashMapBase<T>
{
 private:
  static const int64 EMPTY = (int64)-1;
  static const int64 MAXH = 32;
  int64 size;
  HashFunction *hf;
  T *values;
  int64 *keys;
  int32 *used;
  int64 nprobes;

  inline bool getBit(int64 pos, int shift) { return (used[pos] >> shift) & 1;}
  inline void setBit(int64 pos, int shift) { used[pos] |= 1 << shift; }
  inline void unsetBit(int64 pos, int shift) { used[pos] &= ~(1 << shift); }

  //shifts everything in the hash table
  //assumes that keys[inith + dist] is empty
  //makes space somewhere in [inith, inith + H - 1]
  //assumes size > H
  int64 reshuffle(int64 inith, int64 dist)
  {
    int64 now;
    while (dist >= MAXH)
      {
	int64 curpos = inith + dist - MAXH + 1;
	bool done = false;

	for (int64 i = 0; i < MAXH && !done; i++)
	  {
	    int64 tmphash = hf->hash(keys[(curpos + i)%size]);
	    //keys[curpos + i] hashed somewhere between [curpos + 1, curpos + H]
	    //curpos + H is empty, so swap these two and mark the appropriate pointers
	    //does everything here have to be mod size? !! make sure it's correct !!
	    if (tmphash >= curpos)
	      {
		keys[ (curpos + MAXH - 1)%size ] = keys[ (curpos + i)%size ];
		values[ (curpos + MAXH - 1)%size ] = values[ (curpos + i)%size ];
		keys[ (curpos + i)%size ] = EMPTY;

		//unsetBit(tmphash, curpos + i - tmphash);
		//setBit(tmphash, curpos + MAXH - tmphash);

		dist -= MAXH - i + 1;

		done = true;
	      }
	  }
	
	//this should not happen unless the table is entirely full
	if (!done)
	  {
	    printf("ERROR! failed to find an element to move\n");
	    return 0;
	  }
      }
    return inith + dist;
  }


 public:
 HopscotchHash(int64 size, HashFunction *hf) : size(size), hf(hf)
  {
    nprobes = 0;
    values = new T[size];
    keys = new int64[size];
    used = new int32[size];
    memset(keys, -1, sizeof(keys) * size); //initializes to EMPTY
    memset(used, 0, sizeof(used) * size);
  }
  
  ~HopscotchHash()
    {
      delete[] values;
    }
  
  void put(int64 key, T value)
  {
    int64 h = hf->hash(key);
    int64 freepos = h;
    int64 dist = 0;
    while (keys[freepos] != EMPTY)
      {
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
	printf("FULL!\n");
	return;
      }

    if (dist >= MAXH)
      freepos = reshuffle(h, dist);

    keys[freepos] = key;
    values[freepos] = value;
    //if (h > freepos)
    //setBit(h, size + freepos - h);
    //else
    //setBit(h, freepos - h); //hm... this needs to be mod size?
    printf("put key = %lld, hash %lld, freepos %lld\n", key, h, freepos);
  }

  bool get(int64 key, T &retValue)
  {
    bool ret = false;

    int64 h = hf->hash(key);
    for (int64 i = 0; i < MAXH; i++)
      {
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

};

#endif __HOPSCOTCH_HASH_H__
