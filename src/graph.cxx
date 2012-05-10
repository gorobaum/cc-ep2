
#include <string>
#include <algorithm>

#include "graph.h"
#include "log.h"

namespace ep2 {

using std::vector;
using std::string;

void Graph::add_edge (node i, node j) {
  adj_matrix_[i][j] = true;
}

bool Graph::is_edge (node i, node j) const {
  return adj_matrix_[i][j];
}

void Graph::dump () const {
  AdjMatrix::const_iterator it;
  for (it = adj_matrix_.begin(); it != adj_matrix_.end(); ++it) {
    vector<bool>::const_iterator jt;
    string output;
    for (jt = it->begin(); jt != it->end(); ++jt)
      output += itos(*jt) + " ";
    Log().print(output);
  }
}

}
