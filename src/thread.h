
#ifndef EP2_THREAD_H_
#define EP2_THREAD_H_

#include <pthread.h>

namespace ep2 {

class Thread {
  public:
    typedef void* (*Routine) (void*);
    // TODO: Make thread pool.
    Thread (Routine routine) : 
      running_(false), routine_(routine),
      id_(next_id_++) {}
    bool running () const { return running_; }
    void  run (void *arg);
    void* join ();
    unsigned id ();
    static long number_of_processors ();
    static void exit();
  private:
    bool      running_;
    Routine   routine_;
    unsigned  id_;
    pthread_t thread_;
    static unsigned next_id_;
};

} // namespace ep2

#endif

