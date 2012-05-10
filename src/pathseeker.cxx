
#include <cstdio>

#include "pathseeker.h"

namespace ep2 {

void PathSeeker::seek () {
  PathQueue pathqueue;
  for (node i = 1; i < graph_->n(); i++)
    if (graph_->is_edge(0, i)) {
      Path path(0);
      path.add_vertex(i);
      pathqueue.push(path);
    }
}

void PathSeeker::show_paths () const {

}

}

