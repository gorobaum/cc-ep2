
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
    typedef std::vector< std::vector< bool > >  AdjMatrix;
    explicit Graph (size_t n) :
      adj_matrix_(n, std::vector<bool>(n, false)) {}
    size_t n () { return adj_matrix_.size(); }
    void add_edge (node i, node j);
    bool is_edge (node i, node j) const;
    void dump () const;
  private:
    AdjMatrix adj_matrix_;
};

}

#endif
