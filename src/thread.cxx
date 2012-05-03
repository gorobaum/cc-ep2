
#include <cstdio>

#include <unistd.h>

#include "thread.h"
#include "log.h"

namespace ep2 {

unsigned Thread::next_id_ = 0;

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

unsigned Thread::id () {
  return id_;
}

long Thread::number_of_processors () {
  return sysconf(_SC_NPROCESSORS_ONLN);
}

}
