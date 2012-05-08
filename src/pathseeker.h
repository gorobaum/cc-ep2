#ifndef EP2_PATHSEEKER_H_
#define EP2_PATHSEEKER_H_

#include <queue>
#include "graph.h"
#include "path.h"
#include "thread.h"

namespace ep2 {

class PathSeeker {
  public:
    typedef std::queue< Path >  PathQ;
    
    explicit PathSeeker (Graph *graph) :
      graph_(graph) {}

    void Dijkstra ();
    void ShowPaths () const;

  private:
    Graph *graph_;
    Mutex mutex_;
};

}

#endif
