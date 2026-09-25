#include "SmartMeterD0.h"
#include <cassert>
#include <iostream>
using namespace esphome::obis_d0;
class Capture : public ISmartMeterD0Sensor {
 public:
  std::string code = "1-0:1.8.0*255";
  std::vector<std::string> values;
  void publish_val(const std::string &s) override { values.push_back(s); }
  void publish_invalid() override {}
  bool has_timed_out() override { return false; }
  const std::string &get_obis_code() const override { return code; }
};
int main() {
 SmartMeterD0 meter; Capture sensor; meter.register_sensor(&sensor);
 const std::string telegram = "/TEST\r\n1-0:1.8.0*255(20321.13690000*kWh)\r\n!\r\n";
 auto feed = [&](const std::string &s) { meter.feed(s); meter.loop(); };
 auto good = [&]() {
  auto n = sensor.values.size(); feed(telegram);
  assert(sensor.values.size() == n+1);
  assert(sensor.values.back() == "20321.13690000*kWh");
 };
 // A boot in the middle of a telegram, or noise without a start marker.
 feed(std::string(10000, 'x')); good();
 for (size_t length : {149, 150, 151, 2000}) {
  feed("/TEST\r\n" + std::string(length, 'x') + "\r\n!\r\n"); good();
 }
 // Every possible split across two UART reads.
 for (size_t split=0; split <= telegram.size(); ++split) {
  auto n=sensor.values.size();
  feed(telegram.substr(0,split)); feed(telegram.substr(split));
  assert(sensor.values.size()==n+1);
 }
 // Invalid line endings do not publish the broken value.
 auto n=sensor.values.size(); feed("/TEST\r\n1-0:1.8.0*255(999*kWh)\n!\r\n");
 assert(sensor.values.size()==n); good();
 // STX and ETX must both be ignored within records.
 n=sensor.values.size();
 feed(std::string("/TEST\r\n") + char(2) + "1-0:1.8.0*255(20321.13690000*kWh)" + char(3) + "\r\n!\r\n");
 assert(sensor.values.size()==n+1); good();
 // Repeated telegrams and long garbage runs between them stay synchronized.
 for (int i=0;i<1000;++i) { feed(std::string(200,'x')); good(); }
 std::cout << "PASS: noise, buffer boundaries, oversized records, split reads, malformed lines, STX/ETX, recovery\n";
}
