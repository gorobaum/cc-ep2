
#ifndef EP2_PATHSEEKER_H_
#define EP2_PATHSEEKER_H_

#include <queue>
#include <list>

#include "graph.h"
#include "thread.h"
#include "mutex.h"

namespace ep2 {

class PathSeeker {
  public:
    virtual void seek () = 0;
    virtual void show_paths () const = 0;
    virtual unsigned steps () const = 0;

  protected:
    Graph         *graph_;
    const size_t  minpath_num_;
    explicit PathSeeker (Graph *graph, size_t k) :
      graph_(graph) ,
      minpath_num_(k) {}
};

} // namespace ep2

#endif

