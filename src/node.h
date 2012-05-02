

namespace ep2 {

class Node {
  public:
    
    typedef std::vector< int > AdjList;

    explicit Node (AdjList adjlist):
      adjlist_(adjlist) {}

  private:
    AdjList adjlist_;
}
}
