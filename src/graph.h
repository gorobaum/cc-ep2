#include "node.h"

namespace ep2 {

class Graph {
  public:

    typedef std::vector< int >      AdjList;
    typedef std::vector< AdjList >  AdjMatrix;

    explicit Graph (AdjMatrix adjmatrix); 

  private:
    typedef std::vector< Node >   nodeslist_;
 }

}
