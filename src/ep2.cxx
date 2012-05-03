
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "ep2.h"
#include "graph.h"
#include <string>
#include "log.h"

namespace ep2 {

Graph::AdjMatrix make_matrix_from_file(FILE *pFileIn) {
 
  int i;
  char c;
  Graph::AdjMatrix adjmatrix;

  i = 0;
  c = fgetc(pFileIn);
  adjmatrix.push_back(Node::AdjList());
  while (c != EOF) {
    if (c != ' ') {
      if (c != '\n') {
        adjmatrix[i].push_back(c-'0');
        printf("M[%d] = %d\n", i, adjmatrix[i].back());
      }
      else {
        i++;
        adjmatrix.push_back(Node::AdjList());
      }
    }
    c = fgetc(pFileIn);
  }
   
  return adjmatrix;
}

bool init (int argc, char** argv) {
  FILE *pFileIn;
  size_t num_min_paths;
  Graph::AdjMatrix teste;
  
  if (argc < 2) {
    printf("Voce precisa passar o numero de caminhos minimos.\n");   
    return false;
  }
  if (strcmp(argv[1], "-debug") == 0) {
    Log::set_debug();
    Log().debug("Modo debug ativado.");
    argc--;
    if (argv[2] == NULL) {
      printf("Voce precisa passar o nome de um arquivo como entrada do programa.\n");
      return false;
    }
    strcpy(argv[1], argv[2]);
    strcpy(argv[2], argv[3]);
  }
  num_min_paths = atoi(argv[1]);

  pFileIn = fopen(argv[2], "r");
  if (pFileIn == NULL) {
    printf("Voce precisa passar o nome de um arquivo como entrada do programa.\n");
    return false;
  }

  teste = make_matrix_from_file(pFileIn);
  Graph graph(teste);
  
  return true;
}  

}

