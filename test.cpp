#include <cstdio>
#include "HashFunction.h"
#include "tabulationHash/tabulationHash.h"
#include "multiplicationHash/multiplicationHash.h"
#include <iostream>
using namespace std;

int main()
{
  HashFunction *hf = new TabulationHash(200);
  HashFunction *hf2 = new MultiplicationHash(200);


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

  for (int i = 0; i < 100; i++)
    cout << i << " -> " << hf->hash(i) << endl;

  cout << "a" << " -> " << hf2->hash("a") << endl;
  cout << "ab" << " -> " << hf2->hash("ab") << endl;
  cout << "abc" << " -> " << hf2->hash("abc") << endl;
  cout << "abcd" << " -> " << hf2->hash("abcd") << endl;
  cout << "abcde" << " -> " << hf2->hash("abcde") << endl;
  cout << "abcdef" << " -> " << hf2->hash("abcdef") << endl;
  cout << "abcdefa" << " -> " << hf2->hash("abcdefa") << endl;
  cout << "abcdefab" << " -> " << hf2->hash("abcdefab") << endl;

  return 0;
}
