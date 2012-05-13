
#ifndef EP2_MULTIPATHSEEKER_H_
#define EP2_MULTIPATHSEEKER_H_

#include <queue>
#include <vector>
#include <utility>

#include "pathseeker.h"
#include "graph.h"
#include "path.h"
#include "thread.h"
#include "barrier.h"

namespace ep2 {

class MultiPathSeeker : public PathSeeker {
  public:
    typedef std::queue< std::pair< Path, node > >  PathQueue;
    typedef std::vector< Path > PathHeap;
    
    explicit MultiPathSeeker (Graph *graph, size_t k) :
      PathSeeker(graph, k),
      nodeinfo_(graph->n(), NodeInfo(k)),
      barrier_(Thread::number_of_processors()),
      barrier_p(Thread::number_of_processors()),
      steps_(1),
      first_(-1) {}

    void seek ();
    void show_paths () const;
    unsigned steps () const { return steps_-1; }

  private:
    class NodeInfo {
      public:
        NodeInfo (size_t k) : minpaths(0),
                              maxminpaths(k) {}
        NodeInfo (const NodeInfo& copy) :
          minpaths(copy.minpaths),
          maxminpaths(copy.maxminpaths) {}
        bool full () const {
          return (paths.size() >= maxminpaths);
        }
        size_t max () const {
          return paths.size() ? paths.front().size() : 0;
        }
        bool addminpath (const Path& minpath);
        void dump (node vertex) const;
      private:
        size_t        minpaths;
        const size_t  maxminpaths;
        Mutex         mutex;
        PathHeap      paths;
    };
    std::vector< NodeInfo > nodeinfo_;
    Barrier                 barrier_;
    Barrier                 barrier_p;
    Mutex                   mutexp;
    std::vector< Thread >   threads_;
    std::vector<int>        threads_order_;
    unsigned                steps_;
    int                     first_;
    void do_seek (PathQueue& initial_queue, size_t id);
    static void* seeking_thread (void *args);
    void first_to_arrive (int id);
    void print_infos (int id);
};

}

#endif
