
#include <string>

#include "path.h"
#include "log.h"

namespace ep2 {

using std::string;
using std::vector;

vector<Path::Link*> Path::allocated_;

Path Path::operator+ (node vertex) const {
  return Path(new_link(link_, vertex));
}

bool Path::has (node vertex) const {
  return link_->has(vertex);
}

const char *seps[2] = {
  " - ",
  ""
};

void Path::dump () const {
  Log().print(*this);
}

Path::operator string () const {
  string pathstring;
  for (const Link *it = link_; it; it = it->parent())
    pathstring = seps[!it->parent()] + utos(it->last()) + pathstring;
  pathstring = "(" + ep2::utos(link_->size()) + ") " + pathstring;
  return pathstring;
}

void Path::clearall () {
  vector<Link*>::iterator it;
  for (it = allocated_.begin(); it < allocated_.end(); it++)
    delete *it;
  allocated_.clear();
}

Path::Link* Path::new_link (size_t n) {
  Link *link = new Link(n);
  allocated_.push_back(link);
  return link;
}

Path::Link* Path::new_link (const Link *parent, node last) {
  Link *link = new Link(parent, last);
  allocated_.push_back(link);
  return link;
}

string Path::Link::dump_set () const {
  VertexSet::const_iterator it;
  string output;
  for (it = set_.begin(); it < set_.end(); it++)
    output += '0'+(*it);
  return output;
}

} // namespace ep2
