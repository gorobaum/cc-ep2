
#include <string>

#include "path.h"
#include "log.h"

namespace ep2 {

using std::string;

Path Path::operator+ (node vertex) const {
  return Path(new Link(link_, vertex));
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
  return pathstring + " " + link_->dump_set();
}

string Path::Link::dump_set () const {
  VertexSet::const_iterator it;
  string output;
  for (it = set_.begin(); it < set_.end(); it++)
    output += '0'+(*it);
  return output;
}

} // namespace ep2
