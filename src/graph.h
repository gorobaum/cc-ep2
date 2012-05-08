#ifndef EP2_GRAPH_H_
#define EP2_GRAPH_H_

#include <vector>
#include <queue>
#include "node.h"
#include "path.h"
#include "thread.h"
#include "barrier.h"

namespace ep2 {

class Graph {
  public:

    typedef std::vector<Node::AdjList>  AdjMatrix;
    explicit Graph (AdjMatrix adjmatrix); 

  private:
    std::vector< Node >	nodelist_;
};

}

#endif
