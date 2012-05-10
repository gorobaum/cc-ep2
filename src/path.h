
#ifndef EP2_PATH_H_
#define EP2_PATH_H_

#include <vector>

#include "node.h"

namespace ep2 {

class Path {
  public:
    typedef std::vector<node> VertexPath;

    explicit Path (node initial_vertex) {
      path_.push_back(initial_vertex);
    }

    void add_vertex (node vertex);
    void dump () const;
    bool search_for_vertex (node vertex);
    bool valid () const;
    node last () const { return path_.back(); } 

  private:
    VertexPath  path_;
};

}

#endif

