#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <regex>
#include <string>

#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"

namespace esphome
{
    namespace sm_d0
    {
        // input string formats for float/int sensors
        enum ValueFormat : uint8_t
        {
            ValueFormat_Float,
            ValueFormat_Hex,
        };

        class ISmartMeterD0Sensor
        {
        public:
            virtual ~ISmartMeterD0Sensor() = default;

            virtual void publish_val(const std::string& value) = 0;
            virtual const std::string& get_obis_code() const = 0;
        };

        class SmartMeterD0SensorBase : public ISmartMeterD0Sensor
        {
        public:
            SmartMeterD0SensorBase(std::string obis_code, std::string value_regex) :
                obis_code_{std::move(obis_code)},
                value_regex_{value_regex}
            {
            }

            const std::string& get_obis_code() const override { return obis_code_; }

        protected:
            std::string obis_code_;

            bool check_value(const std::string& value);

        private:
            std::regex value_regex_;
        };

        class SmartMeterD0 : public Component,
                             public uart::UARTDevice
        {
        public:
            SmartMeterD0();

            void setup() override
            {
                // nothing to do here
            }

            void loop() override;

            void register_sensor(ISmartMeterD0Sensor* sensor);

        protected:
            void reset();

            void searchStartOfTelegram();
            void searchEndOfRecord();

            void parseRecord();
            void parseIdentification();
            void parseObis();

        private:
            std::array<uint8_t, 150> buffer_;
            uint16_t length_{0}; // used bytes in buffer_

            using SearchFct = void (SmartMeterD0::*)();
            SearchFct search_{nullptr};

            std::map<std::string, ISmartMeterD0Sensor*> sensors_;
        };

    } // namespace sm_d0
} // namespace esphome

#if 0
            cv.Optional(CONF_EXPORT_REACTIVE_ENERGY): sensor.sensor_schema(
                unit_of_measurement=UNIT_KILOVOLT_AMPS_REACTIVE_HOURS,
                accuracy_decimals=2,
                state_class=STATE_CLASS_TOTAL_INCREASING,
#endif