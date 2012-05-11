
#ifndef EP2_MULTIPATHSEEKER_H_
#define EP2_MULTIPATHSEEKER_H_

#include <queue>
#include <list>

#include "pathseeker.h"
#include "path.h"

namespace ep2 {

class MultiPathSeeker : public PathSeeker {
  public:
    typedef std::queue< Path >          PathQueue;
    typedef std::priority_queue< Path > PathHeap;
    
    explicit MultiPathSeeker (Graph *graph, size_t k) :
      PathSeeker(graph, k),
      nodeinfo_(graph->n(), NodeInfo(k)) {}

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
        bool  full () const {
          return (paths.size() == maxminpaths);
        }
        void  addminpath (const Path& minpath);
      private:
        size_t        minpaths;
        const size_t  maxminpaths;
        Mutex         mutex;
        PathHeap      paths;
    };
    std::vector< NodeInfo > nodeinfo_;
};

}

#endif
