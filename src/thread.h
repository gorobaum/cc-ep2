
#ifndef EP2_THREAD_H_
#define EP2_THREAD_H_

#include <pthread.h>

namespace ep2 {

bool init_threads ();

class Thread {
  public:
    typedef void* (*Routine) (void*);
    Thread (Routine routine) : routine_(routine) {}
    void  run (void *arg);
    void* join ();
    static long number_of_processors ();
  private:
    Routine   routine_;
    pthread_t thread_;
};

} // namespace ep2

#endif

