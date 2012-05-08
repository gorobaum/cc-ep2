#ifndef EP2_NODE_H_
#define EP2_NODE_H_

#include <vector>

namespace ep2 {

class Node {
  public:
    
    typedef std::vector<int> AdjList;

    explicit Node (int id, AdjList adjlist):
      id_(id), adjlist_(adjlist) {}

  private:
    unsigned  id_;
    AdjList   adjlist_;
};
}

#endif
