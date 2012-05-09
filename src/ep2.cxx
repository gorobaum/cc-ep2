
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <vector>

#include "ep2.h"
#include "thread.h"
#include "graph.h"
#include "log.h"


namespace ep2 {

using std::vector;

static void insert_line (Graph *graph, const vector<bool>& line, size_t i) {
  for (vector<bool>::const_iterator it = line.begin(); it != line.end(); ++it)
    if (*it) graph->AddEdge(i, it-line.begin());
}

Graph* make_matrix_from_file(FILE *pFileIn) {
 
  size_t i;
  char c;
  Graph *graph = NULL;
  vector<bool> line;

  i = 0;
  c = fgetc(pFileIn);
  while (c != EOF) {
    if (c != ' ') {
      if (c != '\n') {
        line.push_back(!!(c-'0'));
        //printf("M[%d] = %d\n", i, adjmatrix[i].back());
      }
      else {
        if (!graph) {
          graph = new Graph(line.size());
        }
        insert_line(graph, line, i);
        line.clear();
        i++;
      }
    }
    c = fgetc(pFileIn);
  }
   
  return graph;
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

  Graph *graph = make_matrix_from_file(pFileIn);
  //graph->Dump();
  delete graph;
  
  return true;
}  

void run () {

}

void exit () {
  Thread::exit();
}

}

