#ifndef EP2_NODE_H_
#define EP2_NODE_H_

#include <vector>

namespace ep2 {

class Node {
  public:
    
    typedef std::vector<int> AdjList;

    explicit Node (AdjList adjlist):
      adjlist_(adjlist) {}

  private:
    AdjList adjlist_;
};
}

#endif
