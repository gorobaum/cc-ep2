#ifndef EP2_GRAPH_H_
#define EP2_GRAPH_H_

#include <vector>
#include "node.h"

namespace ep2 {

class Graph {
  public:

    typedef std::vector< Node::AdjList >  AdjMatrix;

    explicit Graph (AdjMatrix adjmatrix); 

  private:
    typedef std::vector< Node >   NodeList;
    NodeList                      nodelist_;
    
};

}

#endif
