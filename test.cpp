#include <cstdio>
#include "HashFunction.h"
#include "tabulationHash/tabulationHash.h"
#include "multiplicationHash/multiplicationHash.h"
#include "HashMapBase.h"
#include "linearProbing/linearHash.h"
#include "hopscotch/hopscotch.h"
#include <iostream>
#include <map>
#include <ctime>
using namespace std;

const int testSize = 80;

int main()
{
  HashFunction *hf = new TabulationHash(testSize);

  //key = {string, int64}; value = <T>
  //super not intuitive
  HashMapBase<int64> *hm = new HopscotchHash<int64>(testSize, hf);

  srand(time(NULL));
  map<int64, int64> truth;
  printf("starting the test\n");
  for (int i = 0; i < 70; i++)
    {
      int64 key = i + 1; //rand();
      int64 value = rand();
      truth[key] = value;
      hm->put(key, value);
      if (i % 6 == 0)
	printf("\n");
    }

  hm->print();
  printf("reading the values\n");
  for (map<int64, int64>::iterator I = truth.begin(); I != truth.end(); I++)
    {
      int64 key = I->first;
      int64 value = I->second;

      int64 myvalue = 0;
      bool in = hm->get(key, myvalue);
      if (!in || myvalue != value)
	{
	  printf("!!! ERROR\n");
	  printf("(%lld %lld) not found; in = %d, myvalue = %lld\n", key, value, in, myvalue);
	}
    }

  printf("everything ok\n");
  return 0;
}
