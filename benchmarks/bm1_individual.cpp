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
 * - hopscotch w/ tabulation
 * - hopscotch w/ mult. hash.
 * - cuckoo w/ tabulation
 * - cuckoo w/ mult. hash.
 */
#include <cstdio>
#include <sys/time.h>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <tr1/unordered_map>
#include <boost/unordered_map.hpp>
#include <ext/hash_map>
#include "../tabulationHash/tabulationHash.h"
#include "../multiplicationHash/multiplicationHash.h"
#include "../linearProbing/linearHash.h"
#include "../quadraticProbing/quadraticProbing.h"
#include "../cuckooHashing/cuckooHashing.h"
#include "../hopscotch/hopscotch.h"

const int64 HMSIZE = 1000*1000; //hash map size
const int64 NELEM = 0.9*HMSIZE; // Load is 90%
const int64 NREADS = 9; // 9 out of 10 hash table operations are reads

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

  struct timeval before, after;
  //start timer;
  gettimeofday(&before, NULL);

  for (int i = 0; i < NELEM; i++)
    hm[elems[i]] = 10; //we don't care about the value

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
  boost::unordered_map<int64, int64> hm;

  struct timeval before, after;
  //start timer;
  gettimeofday(&before, NULL);

  for (int i = 0; i < NELEM; i++)
    hm[elems[i]] = 10; //we don't care about the value

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

void testGccExtHm()
{
  //gnu hash_map does not support 64-bit keys the keys will be downcasted to 32bits
  __gnu_cxx::hash_map<int, long long> hm;

  struct timeval before, after;
  //start timer;
  gettimeofday(&before, NULL);

  for (int i = 0; i < NELEM; i++)
    hm[elems[i]] = (int64) 10; //we don't care about the value

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
  struct timeval before, after;
  //start timer;
  gettimeofday(&before, NULL);

  for (int i = 0; i < NELEM; i++)
    hm->put(elems[i], 10); //we don't care about the value
    
  int64 value = 123;
  int ncalls = 0;
  for (int i = 0; i < NREADS; i++)
    for (int j = 0; j < NELEM; j++)
      {
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
  
  if (argc == 1) {
    printf("No argumenst specified!\n");
    return 0;
  }

  if (strcmp(argv[1], "--c11") == 0) {
    printf("C++11 Unordered Map:\n");
    testC11um();
    return 0;
  }

  if (strcmp(argv[1], "--boost") == 0) {
    printf("Boost hash_map:\n");
    testBoostHm();
    return 0;
  }
  
  if (strcmp(argv[1], "--gcc") == 0) {
    printf("GCC/ext hash_map:\n");
    testGccExtHm();
    return 0;
  }

  // Create a hash function
  HashFunction *tabh = new TabulationHash(HMSIZE);
  HashFunction *mulh = new MultiplicationHash(HMSIZE);
  HashMapBase<int64> *hm;

  if (strcmp(argv[1], "--lt") == 0) { 
    printf("*** Linear with tabulation:\n");
    hm = new LinearHash<int64>(HMSIZE, tabh);
    testHMB(hm);
    return 0;
  }

  if (strcmp(argv[1], "--lm") == 0) {
    hm = new LinearHash<int64>(HMSIZE, mulh);
    printf("*** Linear with multiplication:\n");
    testHMB(hm);
    return 0;
  }

  if (strcmp(argv[1], "--qt") == 0) {
    hm = new QuadraticProbing<int64>(HMSIZE, tabh);
    printf("**** Quadratic with tabulation:\n");
    testHMB(hm);
    return 0;
  }

  if (strcmp(argv[1], "--qm") == 0) {
    hm = new QuadraticProbing<int64>(HMSIZE, mulh);
    printf("**** Quadratic with multiplication:\n");
    testHMB(hm);
    return 0;
  }

  if (strcmp(argv[1], "--ht") == 0) {
    hm = new HopscotchHash<int64>(HMSIZE, tabh);
    printf("***** HopscotchHash with tabulation:\n");
    testHMB(hm);
    return 0;
  }
  
  if (strcmp(argv[1], "--hm") == 0) {
    hm = new HopscotchHash<int64>(HMSIZE, mulh);
    printf("**** HopscotchHash with multiplication\n");
    testHMB(hm);
    return 0;
  }
  
  int d; // The number of Cuckoo tables
  if (argc == 3) {
    d = atoi(argv[2]); // Take d from the command line if specified
  }
  else
    d = 5;
  
  int smSize = HMSIZE / d; // Scale the size of tables for Cuckoo
  
  // We need an array of hash function
  HashFunction **tabhSmallArr = new HashFunction*[d];
  HashFunction **mulhSmallArr = new HashFunction*[d];
  for (int i = 0; i < d; ++i) {
    tabhSmallArr[i] = new TabulationHash(smSize);
    mulhSmallArr[i] = new MultiplicationHash(smSize);
  }

  if (strcmp(argv[1], "--ct") == 0) {
    hm = new CuckooHashing<int64>(smSize, tabhSmallArr, d);
    printf("***** Cuckoo with small table and tabulation:\n");
    testHMB(hm);
  }

  if (strcmp(argv[1], "--cm") == 0) {
    hm = new CuckooHashing<int64>(smSize, mulhSmallArr, d);
    printf("***** Cuckoo with small table and multiplication:\n");
    testHMB(hm);
  }

  delete hm;

  return 0;
}
