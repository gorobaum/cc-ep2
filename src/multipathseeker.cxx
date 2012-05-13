
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
  vector<SeekArgs>  seekargs; 
  for (size_t it = 0; it < np; it++) {
    threads_.push_back(Thread(seeking_thread));
    seekargs.push_back(SeekArgs(this, it));
    Log().debug("Created thread "+utos(it));
  }
  for (size_t it = 0; !pathqueue.empty(); it=(it+1)%np ) {
    Log().debug(
      "Path {"+string(pathqueue.front().first)+" + "+
      utos(pathqueue.front().second)+"} do thread "+utos(it)+"."
    );
    seekargs[it].initial_queue_.push(pathqueue.front());
    pathqueue.pop();
  }
  for (size_t it = 0; it < np; it++) {
    Log().debug("Dispatching thread "+utos(it));
    threads_[it].run(static_cast<void*>(&seekargs[it]));
  }
  for (size_t it = 0; it < np; it++)
    threads_[it].join();
}

void MultiPathSeeker::show_paths () const {
  vector<NodeInfo>::const_iterator it;
  if (Log().debug_on() == false) Log().print("The program has take "
      +utos(steps_-1)+" iterations to terminate.");
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++)
    it->dump(it-nodeinfo_.begin());

}

static string from (size_t id) {
  return "("+utos(id)+") ";
}

void MultiPathSeeker::do_seek (PathQueue& initial_queue, size_t id) {
  //Log().debug(from(id)+"Thread dispatched!");
  while (!initial_queue.empty()) {
    candidate path = initial_queue.front();
    initial_queue.pop();
    //Log().debug(from(id)+"New candidate: "+string(path.first)+" (+"+utos(path.second)+")");
    if (!path.first.has(path.second)) {
      //Log().debug(from(id)+"It should be a path.");
      Path minpath = path.first+path.second;
      bool success = false;
      //if (!nodeinfo_[path.second].full()) {
        //Log().debug(from(id)+"Trying to add path: "+(string)minpath);
        success = nodeinfo_[path.second].addminpath(minpath);
      //}
      if (success) {
        //Log().debug(from(id)+"Successfully added!");
        for (node i = 1; i < graph_->n(); i++)
          if (graph_->is_edge(path.second, i)) {
            //Log().debug(from(id)+"Queued +"+utos(i));
            initial_queue.push(candidate(minpath, i));
          }
      } else; //Log().debug(from(id)+"Failed.");
    } else; //Log().debug(from(id)+"Cycle detected!");
    //Log().debug(from(id)+"=== Arrived at the barrier.");
    first_to_arrive(id);
    barrier_.synchronize(id);
    print_infos(id);
    barrier_p.synchronize(id);
  }
  //Log().debug("Thread "+utos(id)+" finished its job.");
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
    Log().debug("==========Iteration "+utos(steps_)+"==========");
    barrier_.print_order(); 
    if (Log().debug_on() == true) show_paths();
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
  for (it = sorted.begin(); it < sorted.end(); it++)
    it->dump();
}

} // namespace ep2

