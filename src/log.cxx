
#include "log.h"

namespace ep2 {

using std::string;

unsigned  Log::flags_;
Mutex     Log::mutex_;

string itos (int i) {
  char buffer[32];
  sprintf(buffer, "%d", i);
  return buffer;
}

string utos (unsigned i) {
  char buffer[32];
  sprintf(buffer, "%u", i);
  return buffer;
}

Log& Log::print (const string& text) {
  Mutex::Lock lock(mutex_);
  fputs(text.c_str(), output_);
  fputc(10, output_);
  fflush(output_);
  return *this;
}

Log& Log::debug (const string& text) {
  return (flags_ & debug_flag())
    ? print("[DEBUG] " + text)
    : *this;
}

Log& Log::warning (const string& text) {
  return (flags_ & warning_flag())
    ? print("[WARNING] " + text)
    : *this;
}

void Log::set_debug () {
  flags_ |= debug_flag();
}

void Log::set_warning () {
  flags_ |= warning_flag();
}

} // namespace ep2

