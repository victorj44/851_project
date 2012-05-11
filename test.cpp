#include <cstdio>
#include "HashFunction.h"
#include "tabulationHash/tabulationHash.h"
#include "multiplicationHash/multiplicationHash.h"
#include "HashMapBase.h"
#include "linearProbing/linearHash.h"
#include <iostream>
#include <map>
#include <ctime>
using namespace std;

const int testSize = 1*1000*1000;

int main()
{
  HashFunction *hf = new TabulationHash(testSize);
  HashFunction *hf2 = new MultiplicationHash(testSize);

  //key = {string, int64}; value = <T>
  //super not intuitive
  HashMapBase<int64> *hm = new LinearHash<int64>(testSize, hf);

  srand(time(NULL));
  map<int64, int64> truth;
  printf("starting the test\n");
for (int i = 0; i < 10; i++)
    {
      int64 key = rand();
      int64 value = rand();
      truth[key] = value;
      hm->put(key, value);
    }

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
