
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
  MultiPathSeeker             *seeker_;
  MultiPathSeeker::PathQueue  initial_queue_;
  size_t                      id_;
  SeekArgs (MultiPathSeeker *seeker, size_t id) :
    seeker_(seeker), id_(id) {}
};

void MultiPathSeeker::seek () {
  PathQueue pathqueue;
  Path path(graph_->n());
  for (node i = 1; i < graph_->n(); i++)
    if (graph_->is_edge(first_node(), i))
      pathqueue.push(candidate(path,i));
  const size_t np = Thread::number_of_processors();
  Log().debug("Found "+utos(np)+" available cores.");
  vector<SeekArgs>  seekargs; 
  for (size_t it = 0; it < np; it++) {
    threads_.push_back(Thread(seeking_thread));
    seekargs.push_back(SeekArgs(this, it));
  }
  for (size_t it = 0; !pathqueue.empty(); it=(it+1)%np ) {
    seekargs[it].initial_queue_.push(pathqueue.front());
    pathqueue.pop();
  }
  for (size_t it = 0; it < np; it++)
    threads_[it].run(static_cast<void*>(&seekargs[it]));
  for (size_t it = 0; it < np; it++)
    threads_[it].join();
}

void MultiPathSeeker::show_paths () const {
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++) 
    it->dump(it-nodeinfo_.begin());
}

void MultiPathSeeker::do_seek (PathQueue& initial_queue, size_t id) {
  string name = "Thread "+utos(id)+" ";
  while (!initial_queue.empty()) {
    Log().debug(name+"is searching for a new path...");
    candidate path = initial_queue.front();
    initial_queue.pop();
    if (!path.first.has(path.second)) {
      Path minpath = path.first+path.second;
      NodeInfo &info = nodeinfo_[path.second];
      bool success = false;
      if (!info.full() || info.max() > minpath.size())
        success = nodeinfo_[path.second].addminpath(minpath);
      if (success) {
        Log().debug(name+"found a new shortest path to node "+
                    utos(path.second));
        for (node i = 1; i < graph_->n(); i++)
          if (graph_->is_edge(path.second, i)) {
            initial_queue.push(candidate(minpath, i));
          }
      } else Log().debug(name+"did not find any paths.");
    } else Log().debug(name+"did not find any paths.");
    first_to_arrive(id);
    barrier_.synchronize(id);
    print_infos(id);
    barrier_p.synchronize(id);
  }
  Log().debug(name+"has finished its job.");
  barrier_.disconsider(id);
  barrier_p.disconsider(id);
}

void* MultiPathSeeker::seeking_thread (void *args) {
  SeekArgs *seekargs = static_cast<SeekArgs*>(args);
  seekargs->seeker_->do_seek(seekargs->initial_queue_, seekargs->id_);
  Thread::exit();
  return NULL; // never reaches here
}

void MultiPathSeeker::first_to_arrive (int id) {
  Mutex::Lock lock(mutexp);
  if (first_ == -1) first_ = id;
}

void MultiPathSeeker::print_infos (int id) {
  Mutex::Lock lock(mutexp);
  if (first_ == id) {
        barrier_.print_order(); 
    if (Log().debug_on() == true) {
      Log().debug("Current paths:");
      show_paths();
    }
    Log().debug("==========End of iteration "+utos(steps_)+"==========");
    steps_++;
    first_ = -1;
  }
}

bool MultiPathSeeker::NodeInfo::addminpath (const Path& minpath) {
  Mutex::Lock lock(mutex);
  if (full()) {
    if (paths.front() <= minpath)
      return false;
    else {
      pop_heap(paths.begin(), paths.end());
      paths.pop_back();
    }
  }
  paths.push_back(minpath);
  push_heap(paths.begin(), paths.end());
  return true;
}

void MultiPathSeeker::NodeInfo::dump (node vertex) const {
  PathHeap::const_iterator it;
  Log().print("Para o vertice "+utos(vertex)+":");
  PathHeap sorted(paths);
  sort_heap(sorted.begin(), sorted.end());
  for (it = sorted.begin(); it < sorted.end(); it++) {
    it->dump();
  }
  Log().print();
}

} // namespace ep2

