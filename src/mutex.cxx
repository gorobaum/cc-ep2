
#include "mutex.h"
#include "log.h"

namespace ep2 {

Mutex::Mutex () {
  if (pthread_mutex_init(&mutex_, NULL))
    Log().warning("Mutex may not have been correctly initialized.");
}

Mutex::~Mutex () {
  if (pthread_mutex_destroy(&mutex_))
    Log().warning("Mutex may not have been correctly destroyed.");
}

Mutex::Lock::Lock (Mutex& mutex) :
  mutex_ref_(mutex) {
  if (pthread_mutex_lock(&mutex_ref_.mutex_))
    Log().warning("Mutex lock failed.");
}

Mutex::Lock::~Lock () {
  if (pthread_mutex_unlock(&mutex_ref_.mutex_))
    Log().warning("Mutex unlock failed.");
}

} // namespace ep2

