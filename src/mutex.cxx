
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

} // namespace ep2

