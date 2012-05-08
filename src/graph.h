#ifndef EP2_GRAPH_H_
#define EP2_GRAPH_H_

#include <vector>
#include <queue>
#include "path.h"
#include "thread.h"
#include "barrier.h"

namespace ep2 {

class Graph {
  public:

    typedef std::vector< std::vector< bool > >  AdjMatrix;
    explicit Graph (size_t n) :
      adj_matrix_(n, std::vector<bool>(n, false)) {}
    void AddEdge (size_t i, size_t j);
    void Dump () const;

  private:
    AdjMatrix adj_matrix_;
};

}

#endif
