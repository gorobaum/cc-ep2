#ifndef EP2_GRAPH_H_
#define EP2_GRAPH_H_

#include <vector>
#include <queue>
#include "path.h"
#include "thread.h"
#include "barrier.h"

namespace ep2 {

typedef size_t node;

class Graph {
  public:
    typedef std::vector< std::vector< bool > >  AdjMatrix;
    explicit Graph (size_t n) :
      adj_matrix_(n, std::vector<bool>(n, false)) {}
    size_t n () { return adj_matrix_.size(); }
    void AddEdge (node i, node j);
    bool IsEdge (node i, node j) const;
    void Dump () const;
  private:
    AdjMatrix adj_matrix_;
};

}

#endif
