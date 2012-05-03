
#ifndef EP2_LOG_H_
#define EP2_LOG_H_

#include <cstdio>

#include <string>
#include <bitset>

namespace ep2 {

class Log {
  public:
    explicit Log (FILE *output = stdout) : output_(output) {}
    Log& print (const std::string& text);
    Log& debug (const std::string& text);
    Log& warning (const std::string& text);
    static void set_debug () { mode_ |= debug_flag(); }
    static void set_warning () { mode_ |= warning_flag(); }
  private:
    FILE *output_;
    static std::bitset<2> mode_;
    static size_t debug_flag () { return 0; }
    static size_t warning_flag () { return 1; }
};

} // namespace ep2

#endif

