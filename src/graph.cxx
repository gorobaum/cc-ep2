#include "graph.h"

namespace ep2 {

void Graph::DijkstraConc (int path_num) {

}

Graph::Graph (Graph::AdjMatrix adjmatrix) {
  for (unsigned i = 0; i < adjmatrix.size(); i++)
    nodelist_.push_back(Node(adjmatrix[i]));
}

}
