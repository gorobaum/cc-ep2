
#include <unistd.h>
#include <cmath>

#include "barrier.h"
#include "log.h"

#define SKIP //{sched_yield();}

namespace ep2 {

static unsigned log_2 (unsigned n) {
  if (n == 0) {
    Log().warning("0 processadores!?");
  }
  return (unsigned)ceil(log2(n));
}

void Barrier::push_new_thread (int id) {
  threadorder_.push_back(id);
  Log().debug("Thread "+utos(id)+" pushed");
}

void Barrier::print_order () {
  ThreadOrder::iterator it;
  
  for (it = threadorder_.begin(); it < threadorder_.end(); it++)
    Log().debug("Thread "+utos((*it))+" arrived at the barrier. YEAH");
  threadorder_ = ThreadOrder();
}

void Barrier::synchronize (size_t id) {
  unsigned num_stages = log_2(arrive_.size());
  push_new_thread(id);
  for (unsigned s = 0; s < num_stages; s++) {
    //Log().debug("("+utos(id)+") === At stage "+utos(s));
    arrive_[id]++;
    size_t another = (id+(1<<s))%arrive_.size();
    while (arrive_[another] < arrive_[id]) SKIP;
  }
  //Log().debug("("+utos(id)+") === Leaving the barrier. ");
}

void Barrier::disconsider (size_t id) {
  arrive_[id] = -1;
}

} // namespace ep2

