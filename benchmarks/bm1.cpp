/* **************************************
 * benchmark 1 - pure reads
 * 10^6 elements in hash maps
 * 10^8 gets per hash map
 * - C++11 unordered_map
 * - Boost hash_map
 * - gcc/ext hash_map
 * - linear hashing w/ tabulation
 * - linear hashing w/ mult.hash.
 * - quadr hashing w/ tabulation
 * - quadr hashing w/ mult.hash.
 */
#include <cstdio>
#include <sys/time.h>
#include <unistd.h>
#include <ctime>
#include <tr1/unordered_map>
//#include <boost/unordered_map.hpp>
#include <ext/hash_map>
#include "../tabulationHash/tabulationHash.h"
#include "../multiplicationHash/multiplicationHash.h"
#include "../linearProbing/linearHash.h"
#include "../quadraticProbing/quadraticProbing.h"
#include "../cuckooHashing/cuckooHashing.h"
#include "../hopscotch/hopscotch.h"

const int64 NELEM = 1000*1000;
const int64 HMSIZE = 2*1000*1000; //hash map size; effectively load = NELEM/HMSIZE;
const int64 NREADS = 1;//*1000*1000;

int64 elems[NELEM]; //keys inserted
int64 perm[NELEM]; //random permutation of those keys

double timediff(struct timeval before, struct timeval after)
{
  return ((after.tv_sec * 1000000 + after.tv_usec) - 
	  (before.tv_sec * 1000000 + before.tv_usec))/1000000.0;
}

void testC11um()
{
  std::tr1::unordered_map<int64, int64> hm;
  for (int i = 0; i < NELEM; i++)
    hm[elems[i]] = 10; //we don't care about the value

  struct timeval before, after;

  //start timer;
  gettimeofday(&before, NULL);
  
  int value = 123;
  int ncalls = 0;
  for (int i = 0; i < NREADS; i++)
    for (int j = 0; j < NELEM; j++)
      {
	value = hm[perm[j]];
	ncalls++; //just to make sure the compiler won't optimize us "out"
      }
  
  //finish timer;
  gettimeofday(&after, NULL);
  printf("%lf sec\n", timediff(before, after));

}

void testBoostHm()
{
  //skip boost for now before i figure out how to install it
  printf("boost not tested\n");
}

void testGccExtHm()
{
  //gnu hash_map does not support 64-bit keys... what a fail
  //i hope this would correctly, despite that keys will be downcasted to 32bits
  __gnu_cxx::hash_map<int, long long> hm;
  for (int i = 0; i < NELEM; i++)
    hm[elems[i]] = (int64)10; //we don't care about the value
    

  struct timeval before, after;

  //start timer;
  gettimeofday(&before, NULL);
  
  int value = 123;
  int ncalls = 0;
  for (int i = 0; i < NREADS; i++)
    for (int j = 0; j < NELEM; j++)
      {
	value = hm[perm[j]];
	ncalls++; //just to make sure the compiler won't optimize us "out"
      }
  
  //finish timer;
  gettimeofday(&after, NULL);
  printf("%lf sec\n", timediff(before, after));  
}

void testHMB(HashMapBase<int64> *hm)
{
  for (int i = 0; i < NELEM; i++)
    hm->put(elems[i], 10);
    //hm[elems[i]] = (int64)10; //we don't care about the value
    

  struct timeval before, after;

  //start timer;
  gettimeofday(&before, NULL);
  
  int64 value = 123;
  int ncalls = 0;
  for (int i = 0; i < NREADS; i++)
    for (int j = 0; j < NELEM; j++)
      {
	//value = hm[perm[j]];
	hm->get(perm[j], value);
	ncalls++; //just to make sure the compiler won't optimize us "out"
      }
  
  //finish timer;
  gettimeofday(&after, NULL);
  printf("%lf sec\n", timediff(before, after));  
}

int main(int argc, char *argv[])
{
  printf("***** MAKE SURE IT'S COMPILED WITH -O2!\n");
  srand(time(NULL));
  for (int i = 0; i < NELEM; i++)
    elems[i] = rand(); 
  for (int i = 0; i < NELEM; i++)
    perm[i] = elems[rand() % NELEM]; 

  printf("C++11 Unordered Map:\n");
  testC11um();

  printf("Boost hash_map:\n");
  testBoostHm();
  
  printf("GCC/ext hash_map:\n");
  testGccExtHm();

  HashFunction *tabh = new TabulationHash(HMSIZE);
  HashFunction *mulh = new MultiplicationHash(HMSIZE);

  printf("*** Linear with tabulation:\n");
  HashMapBase<int64> *hm = new LinearHash<int64>(HMSIZE, tabh);
  testHMB(hm);
  delete hm;
  
  hm = new LinearHash<int64>(HMSIZE, mulh);
  printf("*** Linear with multiplication:\n");
  testHMB(hm);
  delete hm;

  hm = new QuadraticProbing<int64>(HMSIZE, tabh);
  printf("**** Quadratic with tabulation:\n");
  testHMB(hm);
  delete hm;

  hm = new QuadraticProbing<int64>(HMSIZE, mulh);
  printf("**** Quadratic with multiplication:\n");
  testHMB(hm);
  delete hm;

  hm = new HopscotchHash<int64>(HMSIZE, tabh);
  printf("***** HopscotchHash with tabulation:\n");
  testHMB(hm);
  delete hm;

  hm = new HopscotchHash<int64>(HMSIZE, mulh);
  printf("**** HopscotchHash with multiplication\n");
  testHMB(hm);
  delete hm;

  int d = 5; // The number of Cuckoo tables
  if (argc == 2) {
    d = atoi(argv[2]);
  }
  else
    d = 5;
  
  /*  HashFunction **tabhArr = new HashFunction*[d];
  HashFunction **mulhArr = new HashFunction*[d];
  for (int i = 0; i < d; ++i) {
    tabhArr[i] = new TabulationHash(HMSIZE);
    mulhArr[i] = new MultiplicationHash(HMSIZE);
  }

  hm = new CuckooHashing<int64>(HMSIZE, tabhArr, d);
  printf("***** Cuckoo with tabulation:\n");
  testHMB(hm);
  delete hm;

  hm = new CuckooHashing<int64>(HMSIZE, mulhArr, d);
  printf("***** Cuckoo with multiplication:\n");
  testHMB(hm);
  delete hm;*/

  int smSize = 1.1 * HMSIZE / d;
  
  HashFunction **tabhSmallArr = new HashFunction*[d];
  HashFunction **mulhSmallArr = new HashFunction*[d];
  for (int i = 0; i < d; ++i) {
    tabhSmallArr[i] = new TabulationHash(smSize);
    mulhSmallArr[i] = new MultiplicationHash(smSize);
  }

  hm = new CuckooHashing<int64>(smSize, tabhSmallArr, d);
  printf("***** Cuckoo with small table and tabulation:\n");
  testHMB(hm);
  delete hm;

  hm = new CuckooHashing<int64>(smSize, mulhSmallArr, d);
  printf("***** Cuckoo with small table and multiplication:\n");
  testHMB(hm);
  delete hm;
  
  return 0;
}
