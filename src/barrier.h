#ifndef EP2_BARRIER_H_
#define EP2_BARRIER_H_

#include <vector>

#include "thread.h"

namespace ep2 {

class Barrier {
  public:
    Barrier (long thread_num) :
      arrive_(thread_num, 0) {}
    void synchronize (size_t id);
  private:
    std::vector<unsigned>   arrive_;
};

}

#endif
