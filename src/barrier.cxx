
#include <unistd.h>
#include <cmath>

#include "barrier.h"
#include "log.h"

#define SKIP //{sched_yield();}

namespace ep2 {

static unsigned log_2 (unsigned x) {
  if (x == 0) {
    Log().warning("0 processadores!?");
  }
  return (unsigned)ceil(log2(x));
}

static unsigned pow_2 (unsigned e) {
  return (1 << e); // powers of two are easy
}

void Barrier::push_new_thread (int id) {
  Mutex::Lock lock(mutex_);
  threadorder_.push_back(id);
}

void Barrier::print_order () {
  ThreadOrder::iterator it;
  
  for (it = threadorder_.begin(); it < threadorder_.end(); it++)
    Log().debug("Thread "+utos((*it))+" arrived at the barrier.");
  threadorder_.clear();
}

void Barrier::synchronize (size_t id) {
  unsigned num_stages = log_2(arrive_.size());
  push_new_thread(id);
  for (unsigned s = 0; s < num_stages; s++) {
    arrive_[id]++;
    size_t another = (id+pow_2(s))%arrive_.size();
    while (arrive_[another] < arrive_[id]) SKIP;
  }
}

void Barrier::disconsider (size_t id) {
  arrive_[id] = -1;
}

} // namespace ep2

