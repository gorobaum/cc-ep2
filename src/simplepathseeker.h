
#ifndef EP2_SIMPLEPATHSEEKER_H_
#define EP2_SIMPLEPATHSEEKER_H_

#include <queue>
#include <list>

#include "pathseeker.h"
#include "path.h"
#include "mutex.h"

namespace ep2 {

class SimplePathSeeker : public PathSeeker {
  public:
    typedef std::queue< std::pair< Path, node > >  PathQueue;
    typedef std::list< Path >   PathList;
    
    explicit SimplePathSeeker (Graph *graph, size_t k) :
      PathSeeker(graph, k),
      nodeinfo_(graph->n(), NodeInfo(k)),
      steps_(1) {}

    void seek ();
    void show_paths () const;
    unsigned steps () const { return steps_-1; }

  private:
    struct NodeInfo {
      size_t    minpaths,
                maxminpaths;
      Mutex     mutex;
      PathList  pathlist;
      NodeInfo (size_t k) : minpaths(0),
                            maxminpaths(k) {}
      NodeInfo (const NodeInfo& copy) :
        minpaths(copy.minpaths),
        maxminpaths(copy.maxminpaths) {}
      bool full () const { return (pathlist.size() == maxminpaths); }
      void addminpath (const Path& minpath) {
        pathlist.push_back(minpath); minpaths++;
      }
    };
    std::vector< NodeInfo > nodeinfo_;
    unsigned                steps_;
};

}

#endif
