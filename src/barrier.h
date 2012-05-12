#ifndef EP2_BARRIER_H_
#define EP2_BARRIER_H_

#include <vector>

#include "thread.h"
#include "mutex.h"

namespace ep2 {

class Barrier {
  public:
    typedef std::vector<int>  ThreadOrder;
    Barrier (long thread_num) :
      arrive_(thread_num, 0),
      threadorder_()  {}
    void synchronize (size_t id);
    void disconsider (size_t id);
    void print_order ();
  private:
    std::vector<unsigned> arrive_;
    ThreadOrder           threadorder_;
    Mutex                 mutex_;
    void push_new_thread (int id);
};

}

#endif
