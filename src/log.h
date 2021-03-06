
#ifndef EP2_LOG_H_
#define EP2_LOG_H_

#include <cstdio>

#include <string>

#include "mutex.h"

namespace ep2 {

std::string itos (int i);
std::string utos (unsigned i);

class Log {
  public:
    explicit Log (FILE *output = stdout) : output_(output) {}
    Log& print (const std::string& text = std::string());
    Log& debug (const std::string& text = std::string());
    Log& warning (const std::string& text = std::string());
    static void set_debug ();
    static void set_warning ();
    bool debug_on() { return flags_ & 0x1; }
  private:
    FILE *output_;
    static unsigned flags_;
    static Mutex    mutex_;
    static unsigned debug_flag () { return 0x1; }
    static unsigned warning_flag () { return 0x2; }
};

} // namespace ep2

#endif

