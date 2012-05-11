
#ifndef EP2_PATH_H_
#define EP2_PATH_H_

#include <vector>

#include "node.h"

namespace ep2 {

class Path {
  public:
    typedef std::vector<bool> VertexSet;

    Path (size_t n) : link_(new Link(n)) {}

    Path operator+ (node vertex) const;
    bool search_for_vertex (node vertex) const;
    node last () const { return link_->last(); } 
    void dump () const;
    bool operator< (const Path& rhs) const {
      return path_.size() < rhs.path_.size();
    }
    operator std::string () const;
  private:
    class Link {
        Link (size_t n) :
          last_(0), parent_(NULL), set_(n, false), size_(0) {
          set_[last_] = true;
        }
        Link (const Link *parent, node last) :
          last_(last), parent_(parent), set_(parent->set_), size_(parent->size_+1) {
          set_[last_] = true;
        }
        const Link* parent () const { return parent_; }
        node last () const { return last; }
        size_t size() const { return size_; }
        bool has (node vertex) const { return set_[vertex]; }
      private:
        const node    last_;
        const Link    *parent_;
        VertexSet     set_;
        const size_t  size_;
    };
    Link *link_;
    explicit Path (Link *link) : link_(link) {}
};

}

#endif

