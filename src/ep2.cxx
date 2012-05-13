
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "ep2.h"
#include "thread.h"
#include "graph.h"
#include "path.h"
#include "pathseeker.h"
#include "simplepathseeker.h"
#include "multipathseeker.h"
#include "log.h"


namespace ep2 {

using std::vector;
using std::string;

static Graph  *graph = NULL;
static size_t num_min_paths;
static bool   use_simple = false;

static void show_usage (const string& progname) {
  Log()
    .print("Usage:")
    .print()
    .print("\t" + progname + " [-debug] [-warning] [-single] <n> <input_file>")
    .print()
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
      if (c != '\n')
        line.push_back(!!(c-'0'));
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
      Log().print();
    } else if (strcmp(*argv, "-warning") == 0) {
      Log::set_warning();
      Log().debug("Warning mode activated.");
    } else if (strcmp(*argv, "-single") == 0) {
      Log().debug("Single-threaded seeker will be used.");
      use_simple = true;
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
  fclose(pFileIn);
  
  return true;
}

void run () {
  PathSeeker *seeker = NULL;
  if (use_simple)
    seeker = new SimplePathSeeker(graph, num_min_paths);
  else
    seeker = new MultiPathSeeker(graph, num_min_paths);
  seeker->seek();
  Log().print("The program has taken "+utos(seeker->steps())+" to terminate.");
  Log().debug("===========Final Paths===========");
  seeker->show_paths();
  delete seeker;
}

void exit () {
  delete graph;
  Path::clearall();
  Thread::exit();
}

} // namespace ep2

