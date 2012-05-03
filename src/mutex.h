
#ifndef EP2_MUTEX_H_
#define EP2_MUTEX_H_

#include <pthread.h>

namespace ep2 {

class Mutex {
  public:
    Mutex ();
    ~Mutex ();
  private:
    pthread_mutex_t mutex_;
};

} // namespace ep2

#endif

