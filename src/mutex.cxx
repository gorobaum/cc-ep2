
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

void Mutex::lock () {
  if (pthread_mutex_lock(&mutex_))
    Log().warning("Mutex lock failed.");
}

void Mutex::unlock () {
  if (pthread_mutex_unlock(&mutex_))
    Log().warning("Mutex unlock failed.");
}

Mutex::Lock::Lock (Mutex& mutex) :
  mutex_ref_(mutex) {
  mutex.lock();
}

Mutex::Lock::~Lock () {
  mutex_ref_.unlock();
}

} // namespace ep2

