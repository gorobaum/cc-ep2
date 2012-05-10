#include <cstdio>

#include "path.h"

namespace ep2 {

void Path::add_vertex (node vertex) {
  path_.push_back(vertex);
}

void Path::dump () const {
  Path::VertexPath::const_iterator it;

  for (it = path_.begin(); it < path_.end(); it++)
    printf("%d-", (*it));
  printf("\n");
}

bool Path::search_for_vertex (node vertex) {
  Path::VertexPath::iterator it;
  for (it = path_.begin(); it < path_.end(); it++)
    if ((*it) == vertex) return true;
  return false; 
}

bool Path::valid () const {
  Path::VertexPath::const_iterator it;
  for (it = path_.begin(); it+1 < path_.end(); it++)
    if ((*it) == path_.back()) return false;
  return true;
}

}
