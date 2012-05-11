
#include <cstdio>
#include <string>
#include <algorithm>

#include "multipathseeker.h"
#include "log.h"

namespace ep2 {

using std::vector;
using std::string;
using ep2::itos;

struct SeekArgs {
  MultiPathSeeker &seeker_;
  Path            initial_path_;
  SeekArgs (MultiPathSeeker &seeker, const Path initial_path) :
    seeker_(seeker), initial_path_(initial_path) {}
};

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
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++)
    it->dump(it-nodeinfo_.begin());
}

void* MultiPathSeeker::seeking_thread (void *args) {
  // TODO
  Thread::exit();
  return NULL; // never reaches
}

void MultiPathSeeker::NodeInfo::addminpath (const Path& minpath) {
  Mutex::Lock lock(mutex);
  if (full()) {
    if (paths.front() < minpath) return;
    else pop_heap(paths.begin(), paths.end());
  }
  paths.push_back(minpath);
  push_heap(paths.begin(), paths.end());
}

void MultiPathSeeker::NodeInfo::dump (node vertex) const {
  PathHeap::const_iterator it;
  Log().print("Para o vertice "+utos(vertex)+":");
  PathHeap sorted(paths);
  sort_heap(sorted.begin(), sorted.end());
  for (it = sorted.begin(); it < sorted.end(); it++)
    it->dump();
}

} // namespace ep2

