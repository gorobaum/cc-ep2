
#include <cstdlib>

#include "ep2.h"
#include "log.h"

int main(int argc, char** argv) {
  if (!ep2::init(argc, argv)) {
    ep2::Log().print("Failed to initialize program. Exiting.");
    return EXIT_FAILURE;
  }
  ep2::run();
  ep2::exit();
  // Never reaches here.
  return EXIT_SUCCESS;
}

