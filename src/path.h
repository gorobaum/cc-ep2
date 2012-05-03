#ifndef EP2_PATH_H_
#define EP2_PATH_H_

namespace ep1 {

class Path {
  public:
    typedef std::vector<int> Path;

    explicit Path (int initial_vertex) {
      path_.push_back(initial_vertex);
    }

    void add_vertex (int vertex);
  private:
    Path  path_;
};

}

#endif
