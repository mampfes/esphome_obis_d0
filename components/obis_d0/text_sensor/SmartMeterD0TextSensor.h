#pragma once

#include <string>

#include "esphome/components/text_sensor/text_sensor.h"

#include "../SmartMeterD0.h"

namespace esphome
{
    namespace obis_d0
    {
        class SmartMeterD0TextSensor : public SmartMeterD0SensorBase, public text_sensor::TextSensor, public Component
        {
        public:
            SmartMeterD0TextSensor(std::string obis_code, std::string value_regex, int timeout_ms);
            void publish_val(const std::string& value) override;
            void publish_invalid() override;

        private:
        };

    } // namespace obis_d0
} // namespace esphome
