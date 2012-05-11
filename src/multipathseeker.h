
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
      barrier_(Thread::number_of_processors()) {}

    void seek ();
    void show_paths () const;

  private:
    class NodeInfo {
      public:
        NodeInfo (size_t k) : minpaths(0),
                              maxminpaths(k) {}
        NodeInfo (const NodeInfo& copy) :
          minpaths(copy.minpaths),
          maxminpaths(copy.maxminpaths) {}
        bool full () const {
          return (paths.size() == maxminpaths);
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
    std::vector< Thread >   threads_;
    void do_seek (PathQueue& initial_queue, size_t id);
    static void* seeking_thread (void *args);
};

}

#endif
