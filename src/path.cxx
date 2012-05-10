#include <cstdio>

#include "path.h"

namespace ep2 {

void Path::add_vertex (node vertex) {
  path_.push_back(vertex);
}

void Path::dump () {
  Path::VertexPath::iterator it;

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

}
