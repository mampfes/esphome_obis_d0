#pragma once

#include <string>

#include "esphome/components/sensor/sensor.h"

#include "../SmartMeterD0.h"

namespace esphome
{
    namespace sm_d0
    {
        class SmartMeterD0Sensor : public SmartMeterD0SensorBase, public sensor::Sensor, public Component
        {
        public:
            SmartMeterD0Sensor(std::string obis_code, std::string value_regex, ValueFormat format);
            void publish_val(const std::string& value) override;

        protected:
            void publish_float(const std::string& value);
            void publish_hex(const std::string& value);

        private:
            using PublishFct = void (SmartMeterD0Sensor::*)(const std::string&);
            PublishFct publish_{nullptr};
        };

    } // namespace sm_d0
} // namespace esphome
