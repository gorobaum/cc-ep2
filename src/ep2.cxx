#include <cstdio>
#include <cstring>
#include "ep2.h"
#include "graph.h"

namespace ep2 {
 
bool init (int argc, char** argv) {
  FILE *pFileIn;
  Graph::AdjMatrix teste;
  
  if (argc < 2) {
    printf("você precisa passar o nome de um arquivo como entrada do programa.1\n");   
    return false;
  }
  if (strcmp(argv[1], "-debug") == 0) {
    printf("Modo debug ativado.\n");
    argc--;
    if (argv[2] == NULL) {
      printf("você precisa passar o nome de um arquivo como entrada do programa.2\n");
      return false;
    }
    strcpy(argv[1], argv[2]);
  }
  pFileIn = fopen(argv[1], "r");

  if (pFileIn == NULL) {
    printf("você precisa passar o nome de um arquivo como entrada do programa.3\n");
    return false;
  }

  teste[0][0] = 1;
  Graph graph(teste);
  
  return true;
}  

}

