#include <cstdlib>
#include <string>

#include "esphome/core/log.h"

#include "../SmartMeterD0.h"
#include "SmartMeterD0TextSensor.h"

namespace esphome
{
    namespace obis_d0
    {
        static const char* const TAG = "obis_d0_text_sensor";

        SmartMeterD0TextSensor::SmartMeterD0TextSensor(std::string obis_code, std::string value_regex, int timeout_ms) :
            SmartMeterD0SensorBase{obis_code, value_regex, timeout_ms}
        {
        }

        void SmartMeterD0TextSensor::publish_val(const std::string& value)
        {
            if (check_value(value))
            {
                publish_state(value);
                reset_timeout_counter();
            }
            else
            {
                publish_invalid();
            }
        }

        void SmartMeterD0TextSensor::publish_invalid()
        {
            publish_state("");
        }
    } // namespace obis_d0
} // namespace esphome