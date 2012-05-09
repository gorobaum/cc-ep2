
#include <cstdio>
#include <algorithm>

#include "graph.h"

namespace ep2 {

using std::vector;

void Graph::AddEdge (node i, node j) {
  adj_matrix_[i][j] = true;
}

bool Graph::IsEdge (node i, node j) const {
  return adj_matrix_[i][j];
}

void Graph::Dump () const {
  AdjMatrix::const_iterator it;
  for (it = adj_matrix_.begin(); it != adj_matrix_.end(); ++it) {
    vector<bool>::const_iterator jt;
    for (jt = it->begin(); jt != it->end(); ++jt)
      printf("%d ", (*jt));
    putchar(10);
  }
}

}
