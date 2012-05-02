
#include <cstdio>

#include "ep2.h"
#include "thread.h"

int main(int argc, char** argv) {
  if (!ep2::init(argc, argv)) 
    printf("KEDE O GRAFO? KEDE\n");
  if (!ep2::init_threads()) 
    printf("KEDE AS THREADS? KEDE\n");
  return 0;
}
