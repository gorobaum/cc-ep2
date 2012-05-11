
#include <cstdio>
#include <string>

#include "multipathseeker.h"
#include "log.h"

namespace ep2 {

using std::vector;
using std::string;
using ep2::itos;

void MultiPathSeeker::seek () {
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

void MultiPathSeeker::show_paths () const {
  /*
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++) {
    PathList::const_iterator jt;
    Log().print("Para o vertice "+itos(it-nodeinfo_.begin())+":");
    for (jt = it->paths.begin(); jt != it->paths.end(); jt++) {
      jt->dump();
    }
  }
  */
}

void MultiPathSeeker::NodeInfo::addminpath (const Path& minpath) {
  Mutex::Lock lock(mutex);
  if (full()) {
    if (paths.top() < minpath) return;
    else paths.pop();
  }
  paths.push(minpath);
}

} // namespace ep2

