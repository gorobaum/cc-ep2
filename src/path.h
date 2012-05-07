#ifndef EP2_PATH_H_
#define EP2_PATH_H_

#include <vector>

namespace ep2 {

class Path {
  public:
    typedef std::vector<int> VertexPath;

    explicit Path (int initial_vertex) {
      path_.push_back(initial_vertex);
    }

    void add_vertex (int vertex);
    void dump ();
    bool search_for_vertex (int vertex);

  private:
    VertexPath  path_;
};

}

#endif
