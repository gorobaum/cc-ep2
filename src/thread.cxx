
#include <cstdio>
#include <unistd.h>

#include <algorithm>

#include "thread.h"
#include "log.h"

namespace ep2 {

using std::min;

void Thread::run (void *arg) {
  if (!running_) {
    pthread_create(&thread_, NULL, routine_, arg);
    running_ = true;
  }
}

void Thread::join () {
  if (!running_) {
    Log().warning("Attempt to join inactive thread.");
    return;
  }
  if (pthread_join(thread_, NULL))
    Log().warning("Something bad happed.");
}

long Thread::number_of_processors () {
  return max(sysconf(_SC_NPROCESSORS_ONLN), 2l);
}

void Thread::exit () {
  pthread_exit(NULL);
}

}
