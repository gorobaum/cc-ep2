
#include <cstdio>
#include <string>
#include <algorithm>

#include "multipathseeker.h"
#include "log.h"

namespace ep2 {

using std::vector;
using std::string;
using std::pair;
using ep2::itos;

typedef pair<Path,node> candidate;

struct SeekArgs {
  MultiPathSeeker &seeker_;
  Path            initial_path_;
  SeekArgs (MultiPathSeeker &seeker, const Path initial_path) :
    seeker_(seeker), initial_path_(initial_path) {}
};

void MultiPathSeeker::seek () {
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

void MultiPathSeeker::show_paths () const {
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++)
    it->dump(it-nodeinfo_.begin());
}

void MultiPathSeeker::do_seek (const Path& initial_path) {
  // TODO
}

void* MultiPathSeeker::seeking_thread (void *args) {
  SeekArgs *seekargs = static_cast<SeekArgs*>(args);
  seekargs->seeker_.do_seek(seekargs->initial_path_);
  Thread::exit();
  return NULL; // never reaches here
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

