
#include <cstdio>
#include <string>

#include "simplepathseeker.h"
#include "log.h"

namespace ep2 {

using std::vector;
using std::string;
using std::pair;

typedef pair<Path,node> candidate;

void SimplePathSeeker::seek () {
  PathQueue pathqueue;
  Path path(first_node());
  for (node i = 1; i < graph_->n(); i++)
    if (graph_->is_edge(first_node(), i))
      pathqueue.push(candidate(path,i));
  while (!pathqueue.empty()) {
    candidate path = pathqueue.front();
    pathqueue.pop();
    if (!nodeinfo_[path.second].full() && !path.first.has(path.second)) {
      Path minpath = path.first+path.second;
      nodeinfo_[path.second].addminpath(minpath);
      for (node i = 1; i < graph_->n(); i++)
        if (graph_->is_edge(path.second, i))
          pathqueue.push(candidate(minpath, i));
    }
  }
}

void SimplePathSeeker::show_paths () const {
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++) {
    PathList::const_iterator jt;
    Log().print("Para o vertice "+ep2::itos(it - nodeinfo_.begin())+":");
    for (jt = it->pathlist.begin(); jt != it->pathlist.end(); jt++) {
      jt->dump();
    }
  }
}

} // namespace ep2

