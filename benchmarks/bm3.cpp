/* **************************************
 * benchmark 2 - reads running time vs. load
 * 10^6 elements in hash maps
 * 10^8 gets per hash map
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

const int64 NELEM = 1000*1000;
const int64 BUCKETSIZE = 10000;
const int64 HMSIZE = NELEM; // must be >= NELEM
const int64 NREADS = 100;//each time frame ~ 1M reads

int64 elems[NELEM]; //keys inserted
int64 perm[NELEM]; //random permutation of those keys

double timediff(struct timeval before, struct timeval after)
{
  return ((after.tv_sec * 1000000 + after.tv_usec) - 
	  (before.tv_sec * 1000000 + before.tv_usec))/1000000.0;
}

void testHMB(HashMapBase<int64> *hm)
{
    struct timeval before, after;

  //start timer;
  gettimeofday(&before, NULL);
  
  int64 value = 123;

  for (int round = 1; round < NELEM/BUCKETSIZE; round++)
    {
      int sz = BUCKETSIZE * round;
      for (int i = 0; i < BUCKETSIZE; i++)
	hm->put(elems[sz - i - 1], value);

      //random permutate reads
      for (int i = 0; i < sz; i++)
	perm[i] = elems[rand() % sz];

      gettimeofday(&before, NULL);
      //do NREADS * BUCKETSIZE reads
      for (int j = 0; j < NREADS; j++)
	{
	  double ncalls = 0;
	  for (int i = 0; i < BUCKETSIZE; i++)
	    {
	      hm->get(perm[i], value);
	      ncalls++;
	    }
	}
      gettimeofday(&after, NULL);

      printf("%lf\n", timediff(before, after));
    }

  
  //finish timer;
  gettimeofday(&after, NULL);
  printf("\n%lf sec\n", timediff(before, after));  
}

int main()
{
  srand(time(NULL));
  for (int i = 0; i < NELEM; i++)
    elems[i] = rand(); 
  for (int i = 0; i < NELEM; i++)
    perm[i] = elems[rand() % NELEM]; 

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

  int d = 2; // The number of Cuckoo tables
  HashFunction **tabhArr = new HashFunction*[d];
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
  delete hm;

  return 0;
}