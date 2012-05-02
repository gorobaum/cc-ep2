
#ifndef EP2_THREAD_H_
#define EP2_THREAD_H_

#include <tr1/memory>

#include <pthread.h>

namespace ep2 {

bool init_threads ();

class Thread {
  public:
    typedef void* (*Routine) (void*);
    typedef std::tr1::shared_ptr<Thread>      Ptr;
    static Ptr create (Routine routine) {
      return Ptr(new Thread(routine));
    }
    void  run (void *arg);
    void* join ();
  private:
    Routine   routine_;
    pthread_t thread_;
    explicit Thread (Routine routine) : routine_(routine) {}
};

} // namespace ep2

#endif

