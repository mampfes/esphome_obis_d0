#pragma once
#include <deque>
#include <string>
#include <cstdint>
namespace esphome { namespace uart {
class UARTDevice {
 public:
  void feed(const std::string &s) { bytes_.insert(bytes_.end(), s.begin(), s.end()); }
  int available() { return bytes_.size(); }
  bool read_byte(uint8_t *out) {
   if (bytes_.empty()) return false;
   *out = bytes_.front(); bytes_.pop_front(); return true;
  }
 private: std::deque<uint8_t> bytes_;
};
}}
