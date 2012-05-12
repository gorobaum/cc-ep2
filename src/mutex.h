
#ifndef EP2_MUTEX_H_
#define EP2_MUTEX_H_

#include <pthread.h>

namespace ep2 {

class Mutex {
  public:
    class Lock {
      public:
        Lock (Mutex& mutex);
        ~Lock ();
      private:
        Lock (const Lock&);
        Lock& operator = (const Lock&);
        Mutex &mutex_ref_;
    };
    Mutex ();
    ~Mutex ();
    void lock ();
    void unlock ();
  private:
    friend class Lock;
    pthread_mutex_t mutex_;
    Mutex (const Mutex&);
    Mutex& operator = (const Mutex&);
};

} // namespace ep2

#endif

