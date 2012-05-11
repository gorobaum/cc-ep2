
#include <string>

#include "path.h"
#include "log.h"

namespace ep2 {

using std::string;

Path Path::operator+ (node vertex) const {
  return Path(new Link(link_), vertex);
}

bool Path::search_for_vertex (node vertex) const {
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
  for (Link *it = link_; it; it = it->parent())
    pathstring = seps[!it->parent()] + utos(it->last()) + pathstring;
  pathstring = "(" + ep2::utos(path_.size()) + ") " + pathstring;
  return pathstring;
}

} // namespace ep2
