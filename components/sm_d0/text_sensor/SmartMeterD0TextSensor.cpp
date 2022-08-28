#include <cstdlib>
#include <string>

#include "esphome/core/log.h"

#include "../SmartMeterD0.h"
#include "SmartMeterD0TextSensor.h"

namespace esphome
{
    namespace sm_d0
    {
        static const char* const TAG = "sm_d0_text_sensor";

        SmartMeterD0TextSensor::SmartMeterD0TextSensor(std::string obis_code, std::string value_regex) :
            SmartMeterD0SensorBase{obis_code, value_regex}
        {
        }

        void SmartMeterD0TextSensor::publish_val(const std::string& value)
        {
            if (check_value(value))
            {
                publish_state(value);
            }
            else
            {
                publish_state("");
            }
        }
    } // namespace sm_d0
} // namespace esphome