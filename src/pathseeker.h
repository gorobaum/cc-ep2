#ifndef EP2_PATHSEEKER_H_
#define EP2_PATHSEEKER_H_

#include <queue>
#include "graph.h"
#include "path.h"
#include "thread.h"
#include "mutex.h"

namespace ep2 {

class PathSeeker {
  public:
    typedef std::queue< Path >  PathQ;
    
    explicit PathSeeker (Graph *graph) :
      graph_(graph) {}

    void seek ();
    void show_paths () const;

  private:
    struct NodeInfo {
      size_t  minpaths;
      Mutex   mutex;
      NodeInfo () : minpaths(0) {}
    };
    Graph *graph_;
    Mutex mutex_;
};

}

#endif
