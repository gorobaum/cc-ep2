
#ifndef EP2_THREAD_H_
#define EP2_THREAD_H_

#include <pthread.h>

namespace ep2 {

class Thread {
  public:
    typedef void* (*Routine) (void*);
    Thread (Routine routine) : 
      running_(false), routine_(routine) {}
    bool running () const { return running_; }
    void  run (void *arg);
    void join ();
    static long number_of_processors ();
    static void exit();
  private:
    bool      running_;
    Routine   routine_;
    pthread_t thread_;
};

} // namespace ep2

#endif

