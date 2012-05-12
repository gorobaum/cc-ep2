
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
    bool has (node vertex) const;
    node last () const { return link_->last(); } 
    void dump () const;
    bool operator< (const Path& rhs) const {
      return link_->size() < rhs.link_->size();
    }
    bool operator<= (const Path& rhs) const {
      return link_->size() <= rhs.link_->size();
    }
    operator std::string () const;
  private:
    class Link {
      public:
        Link (size_t n) :
          last_(first_node()),
          parent_(NULL),
          set_(n, false),
          size_(0) {
          set_[first_node()] = true;
        }
        Link (const Link *parent, node last) :
          last_(last),
          parent_(parent),
          set_(parent->set_),
          size_(parent->size_+1) {
          set_[last] = true;
        }
        const Link* parent () const { return parent_; }
        node last () const { return last_; }
        size_t size() const { return size_; }
        bool has (node vertex) const { return set_[vertex]; }
        std::string dump_set () const;
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

