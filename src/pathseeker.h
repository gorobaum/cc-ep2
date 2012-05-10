#ifndef EP2_PATHSEEKER_H_
#define EP2_PATHSEEKER_H_

#include <queue>
#include <list>
#include "graph.h"
#include "path.h"
#include "thread.h"
#include "mutex.h"

namespace ep2 {

class PathSeeker {
  public:
    typedef std::queue< Path >  PathQueue;
    typedef std::list< Path >   PathList;
    
    explicit PathSeeker (Graph *graph, size_t k) :
      graph_(graph) ,
      nodeinfo_(graph->n(), NodeInfo(k)) {}

    void seek ();
    void show_paths () const;

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
      bool  full () const { return (pathlist.size() == maxminpaths); }
      void  addminpath (const Path& minpath) { pathlist.push_back(minpath); }
    };
    Graph                     *graph_;
    std::vector< NodeInfo >   nodeinfo_;
    Mutex                     mutex_;
};

}

#endif
