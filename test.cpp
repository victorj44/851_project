#include <cstdio>
#include "HashFunction.h"
#include "tabulationHash/tabulationHash.h"
#include "multiplicationHash/multiplicationHash.h"
#include <iostream>
using namespace std;

int main()
{
  HashFunction *hf = new TabulationHash(200);
  HashFunction *hf2 = new MultiplicationHash();


  //for (int i = 0; i < 100; i++)
  //cout << i << " -> " << hf->hash(i) << endl;
  cout << "a" << " -> " << hf->hash("a") << endl;
  cout << "ab" << " -> " << hf->hash("ab") << endl;
  cout << "abc" << " -> " << hf->hash("abc") << endl;
  cout << "abcd" << " -> " << hf->hash("abcd") << endl;
  cout << "abcde" << " -> " << hf->hash("abcde") << endl;
  cout << "abcdef" << " -> " << hf->hash("abcdef") << endl;
  cout << "abcdefa" << " -> " << hf->hash("abcdefa") << endl;
  cout << "abcdefab" << " -> " << hf->hash("abcdefab") << endl;

  return 0;
}
