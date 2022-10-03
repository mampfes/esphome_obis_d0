#include <cmath>
#include <cstdlib>
#include <string>

#include "esphome/core/log.h"

#include "../SmartMeterD0.h"
#include "SmartMeterD0Sensor.h"

namespace esphome
{
    namespace obis_d0
    {
        static const char* const TAG = "obis_d0_sensor";

        SmartMeterD0Sensor::SmartMeterD0Sensor(std::string obis_code, std::string value_regex, ValueFormat format) :
            SmartMeterD0SensorBase{obis_code, value_regex}
        {
            switch (format)
            {
                case ValueFormat_Float:
                    publish_ = &SmartMeterD0Sensor::publish_float;
                    break;

                case ValueFormat_Hex:
                    publish_ = &SmartMeterD0Sensor::publish_hex;
                    break;
            }
        }

        void SmartMeterD0Sensor::publish_val(const std::string& value)
        {
            if (check_value(value))
            {
                (this->*publish_)(value);
            }
            else
            {
                publish_state(NAN);
            }
        }

        void SmartMeterD0Sensor::publish_float(const std::string& value)
        {
            char* end;
            double val = strtod(value.c_str(), &end);
            if (val == HUGE_VAL)
            {
                ESP_LOGD(TAG, "OBIS code %s float out of range: %s", obis_code_.c_str(), value.c_str());
                return;
            }

            if (end == value.c_str())
            {
                ESP_LOGD(TAG, "OBIS code %s invalid float: %s", obis_code_.c_str(), value.c_str());
                return;
            }

            publish_state(val);
        }

        void SmartMeterD0Sensor::publish_hex(const std::string& value)
        {
            char* end;
            unsigned long long val = strtoull(value.c_str(), &end, 16);
            if (val == HUGE_VAL)
            {
                ESP_LOGD(TAG, "OBIS code %s hex out of range: %s", obis_code_.c_str(), value.c_str());
                return;
            }

            if (end == value.c_str())
            {
                ESP_LOGD(TAG, "OBIS code %s invalid hex: %s", obis_code_.c_str(), value.c_str());
                return;
            }

            publish_state(val);
        }
    } // namespace obis_d0
} // namespace esphome