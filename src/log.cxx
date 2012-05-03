
#include "log.h"

namespace ep2 {

using std::string;
using std::bitset;

std::bitset<2> Log::mode_;

Log& Log::print (const string& text) {
  fputs(text.c_str(), output_);
  return *this;
}

Log& Log::debug (const string& text) {
  return mode_[debug_flag()]
    ? print("[DEBUG] " + text)
    : *this;
}

Log& Log::warning (const string& text) {
  return mode_[warning_flag()]
    ? print("[WARNING] " + text)
    : *this;
}

} // namespace ep2

