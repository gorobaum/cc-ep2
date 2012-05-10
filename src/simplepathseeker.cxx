
#include <cstdio>
#include <string>

#include "simplepathseeker.h"
#include "log.h"

namespace ep2 {

using std::vector;
using std::string;

void SimplePathSeeker::seek () {
  PathQueue pathqueue;
  for (node i = 1; i < graph_->n(); i++)
    if (graph_->is_edge(0, i)) {
      Path path(0);
      path.add_vertex(i);
      pathqueue.push(path);
    }
  while (!pathqueue.empty()) {
    Path path = pathqueue.front();
    pathqueue.pop();
    if (!nodeinfo_[path.last()].full() && path.valid()) {
      nodeinfo_[path.last()].addminpath(path);
      for (node i = 1; i < graph_->n(); i++)
        if (graph_->is_edge(path.last(), i)) {
          Path candidate = path;
          candidate.add_vertex(i);
          pathqueue.push(candidate);
        }
    }
  }
}

void SimplePathSeeker::show_paths () const {
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin(); it < nodeinfo_.end(); it++) {
    PathList::const_iterator jt;
    printf("Para o vertice %d:\n", (it - nodeinfo_.begin()));
    for (jt = it->pathlist.begin(); jt != it->pathlist.end(); jt++) {
      jt->dump();
    }
  }
}

} // namespace ep2

