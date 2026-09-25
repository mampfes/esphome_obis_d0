#pragma once
#include <vector>
namespace esphome { template<typename... T> class Trigger { public: void trigger(T...) {} }; }
