
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

void* Thread::join () {
  if (!running_) {
    Log().warning("Attempt to join inactive thread.");
    return NULL;
  }
  void *ret = NULL;
  if (pthread_join(thread_, &ret))
    Log().warning("Something bad happed.");
  return ret;
}

long Thread::number_of_processors () {
  return min(sysconf(_SC_NPROCESSORS_ONLN), 2l);
}

void Thread::exit () {
  pthread_exit(NULL);
}

}
