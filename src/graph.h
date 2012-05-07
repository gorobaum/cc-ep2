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
    std::queue< Path >	pathqueue_;
    std::queue< Path >  resultpaths_;

    void DijkstraConc (int path_num);
};

}

#endif
