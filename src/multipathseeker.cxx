
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
  Barrier                     *barrier_;
  Thread                      *thread_;
  SeekArgs (MultiPathSeeker *seeker, Barrier *barrier, Thread *thread) :
    seeker_(seeker), barrier_(barrier), thread_(thread) {}
};

void MultiPathSeeker::seek () {
  PathQueue pathqueue;
  Path path(first_node());
  for (node i = 1; i < graph_->n(); i++)
    if (graph_->is_edge(first_node(), i))
      pathqueue.push(candidate(path,i));
  const size_t np = Thread::number_of_processors();
  vector<Thread>    threads;
  vector<SeekArgs>  seekargs; 
  Barrier           barrier(np);
  for (size_t it = 0; it < np; it++) {
    threads.push_back(Thread(seeking_thread));
    Log().debug("Created thread "+utos(threads[it].id()));
    seekargs.push_back(SeekArgs(this, &barrier, &threads[it]));
  }
  for (size_t it = 0; !pathqueue.empty(); it=(it+1)%np ) {
    seekargs[it].initial_queue_.push(pathqueue.front());
    pathqueue.pop();
  }
  for (size_t it = 0; it < np; it++)
    threads[it].run(static_cast<void*>(&seekargs[it]));
  for (size_t it = 0; it < np; it++)
    threads[it].join();
}

void MultiPathSeeker::show_paths () const {
  vector<NodeInfo>::const_iterator it;
  for (it = nodeinfo_.begin()+1; it < nodeinfo_.end(); it++)
    it->dump(it-nodeinfo_.begin());
}

void MultiPathSeeker::do_seek (PathQueue& initial_queue, Barrier &barrier,
                               Thread &thread) {
  while (!initial_queue.empty()) {
    candidate path = initial_queue.front();
    initial_queue.pop();
    if (!path.first.has(path.second)) {
      Path minpath = path.first+path.second;
      bool success = false;
      if (!nodeinfo_[path.second].full())
        success = nodeinfo_[path.second].addminpath(minpath);
      if (success)
        for (node i = 1; i < graph_->n(); i++)
          if (graph_->is_edge(path.second, i))
            initial_queue.push(candidate(minpath, i));
    }
    Log().debug("Thread "+utos(thread.id())+" has arrived at the barrier.");
    barrier.synchronize(thread);
  }
}

void* MultiPathSeeker::seeking_thread (void *args) {
  SeekArgs *seekargs = static_cast<SeekArgs*>(args);
  seekargs->seeker_->do_seek(
    seekargs->initial_queue_,
    *seekargs->barrier_,
    *seekargs->thread_
  );
  Thread::exit();
  return NULL; // never reaches here
}

bool MultiPathSeeker::NodeInfo::addminpath (const Path& minpath) {
  Mutex::Lock lock(mutex);
  Log().debug("Trying to add path: "+(string)minpath);
  if (full()) {
    if (paths.front() < minpath) return false;
    else pop_heap(paths.begin(), paths.end());
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

