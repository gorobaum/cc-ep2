#include <cstdio>
#include "ep2.h"

int main(int argc, char** argv) {
  if (!ep2::init(argc, argv)) 
    printf("KEDE O GRAFO? KEDE\n");
  return 0;
}
