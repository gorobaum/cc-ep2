
#include <cstdio>

#include "thread.h"

namespace ep2 {

bool init_threads () {
  return false;
}

void Thread::run (void *arg) {
  pthread_create(&thread_, NULL, routine_, arg);
}

void* Thread::join () {
  void *ret = NULL;
  if (pthread_join(thread_, &ret))
    puts("Something bad happed.");
  return ret;
}

}
