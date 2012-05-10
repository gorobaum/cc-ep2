
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "ep2.h"
#include "thread.h"
#include "graph.h"
#include "pathseeker.h"
#include "simplepathseeker.h"
#include "log.h"


namespace ep2 {

using std::vector;
using std::string;

static Graph   *graph = NULL;
static size_t  num_min_paths;

static void show_usage (const string& progname) {
  Log()
    .print("Usage:")
    .print("\t" + progname + " [-debug] [-warning] <n> <input_file>")
    .print("Where <n> is the number of minimum paths desired and <input_file>")
    .print("is the path to the file describing the graph.");
}

static void insert_line (Graph *graph, const vector<bool>& line, size_t i) {
  for (vector<bool>::const_iterator it = line.begin(); it != line.end(); ++it)
    if (*it) graph->add_edge(i, it-line.begin());
}

static Graph* make_matrix_from_file(FILE *pFileIn) {
 
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
  string progname(argv[0]);
  argc--, argv++;
  while (argc && *argv[0] == '-') {
    if (strcmp(*argv, "-debug") == 0) {
      Log::set_debug();
      Log().debug("Debug mode activated.");
    } else if (strcmp(*argv, "-warning") == 0) {
      Log::set_warning();
      Log().debug("Warning mode activated.");
    }
    argc--; argv++;
  }
  if (argc < 2) {
    show_usage(progname);
    return false;
  }
  num_min_paths = atoi(*argv);
  argc--, argv++;
  FILE *pFileIn = fopen(*argv, "r");
  if (pFileIn == NULL) {
    Log().print("Could not open file '" + string(*argv) + "'.");
    return false;
  }

  graph = make_matrix_from_file(pFileIn);
  //graph->Dump();
  
  return true;
}

void run () {
  PathSeeker *seeker = new SimplePathSeeker(graph, num_min_paths);
  seeker->seek();
  seeker->show_paths();
  delete seeker;
}

void exit () {
  delete graph;
  Thread::exit();
}

} // namespace ep2

