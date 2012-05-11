
#include "barrier.h"
#include "log.h"

#define SKIP {}

namespace ep2 {

static unsigned log_2 (unsigned n) {
  if (n == 0) {
    Log().warning("0 processadores!?");
  }
  unsigned count = 0;
  while (n) n >>= 1, ++count;
  return count;
}

void Barrier::synchronize (size_t id) {
  // num_stages = ceil(log2(n)), where n is the number of threads.
  unsigned num_stages = log_2(arrive_.size())+1;

  for (unsigned s = 0; s < num_stages; s++) {
    arrive_[id]++;
    // algoritmo magico
    size_t another = (id+(1<<s))%arrive_.size();
    while (arrive_[another] < arrive_[id]) SKIP;
  }
}

}
