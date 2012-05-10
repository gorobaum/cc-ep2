
#include <string>

#include "path.h"
#include "log.h"

namespace ep2 {

using std::string;

void Path::add_vertex (node vertex) {
  path_.push_back(vertex);
}

const char *seps[2] = {
  " - ",
  ""
};

void Path::dump () const {
  Path::VertexPath::const_iterator it;
  string output;

  output += "(" + ep2::utos(path_.size()-1) + ") ";
  for (it = path_.begin(); it < path_.end(); it++)
    output += utos(*it) + seps[it+1==path_.end()];
  Log().print(output);
}

bool Path::search_for_vertex (node vertex) {
  Path::VertexPath::iterator it;
  for (it = path_.begin(); it < path_.end(); it++)
    if ((*it) == vertex) return true;
  return false; 
}

bool Path::valid () const {
  Path::VertexPath::const_iterator it;
  for (it = path_.begin(); it+1 < path_.end(); it++)
    if ((*it) == path_.back()) return false;
  return true;
}

}
