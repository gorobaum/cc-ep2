
#include <cstdio>

#include <unistd.h>

#include "thread.h"

namespace ep2 {

bool init_threads () {
  return false;
}

void Thread::run (void *arg) {
  if (!running_) {
    pthread_create(&thread_, NULL, routine_, arg);
    running_ = true;
  }
}

void* Thread::join () {
  if (!running_) {
    puts("Attempt to join inactive thread.");
  }
  void *ret = NULL;
  if (pthread_join(thread_, &ret))
    puts("Something bad happed.");
  return ret;
}

long Thread::number_of_processors () {
  return sysconf(_SC_NPROCESSORS_ONLN);
}

}
