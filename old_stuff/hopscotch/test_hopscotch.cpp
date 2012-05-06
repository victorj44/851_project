#define INTEL64 1

#include "inc/cpp_framework.h"
#include "HopscotchHashMap.h"

int main()
{
  printf("test\n");
  HopscotchHashMap<int, int, HASH_INT, TTASLock, CMDR::Memory> hm;
  
  return 0;
}
