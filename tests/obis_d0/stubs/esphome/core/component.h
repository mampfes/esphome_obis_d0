#pragma once
#include <cstdint>
#include <cstring>
namespace esphome {
inline uint32_t millis() { return 1; }
class Component { public: virtual ~Component() = default; virtual void setup() {} virtual void loop() {} };
}
