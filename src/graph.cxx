#include "graph.h"

namespace ep2 {

Graph::Graph (Graph::AdjMatrix adjmatrix) {
  for (unsigned i = 0; i < adjmatrix.size(); i++)
    nodelist_.push_back(Node(i, adjmatrix[i]));
}

}
