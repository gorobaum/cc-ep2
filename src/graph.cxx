#include "graph.h"

namespace ep2 {

class Graph {
  public:
    
    Graph (AdjMatrix adjmatrix) {
      int i;
      for (i = 0; i < adjmatrix.size(); i++)
        nodeslist_.push_back(Node(adjmatrix[i]));
    }
}

}
