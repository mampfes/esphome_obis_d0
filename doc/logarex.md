# Logarex LK11 Drehstromzähler, LK13 Wechselstromzähler

UART configuration: 9600 Baud, 7E1

This device has an optical D0 interface at the front. To enable the output of  complete data records (full resolution and all available values), the ```INF``` parameter has to be set to ```on```.

## Example

```yaml
external_components:
  - source: github://mampfes/esphome_obis_d0

uart:
  id: my_uart
  rx_pin: GPIO16
  baud_rate: 9600
  data_bits: 7
  parity: EVEN
  stop_bits: 1

obis_d0:
  id: my_sm
  uart_id: my_uart

sensor:
  - !include common/sensor/wifi.yaml
  - !include common/sensor/uptime.yaml

  - platform: obis_d0
    name: "Consumed Energy"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*255"
    unit_of_measurement: kWh
    accuracy_decimals: 4
    state_class: total_increasing
    device_class: energy
    value_regex: "\\d{6}\\.\\d{4}\\*kWh"

  #  - platform: obis_d0
  #    name: "Consumed Energy Tariff 1"
  #    obis_d0_id: my_sm
  #    obis_code: "1-0:1.8.1*255"
  #    unit_of_measurement: kWh
  #    accuracy_decimals: 4
  #    state_class: total_increasing
  #    device_class: energy
  #    value_regex: "\\d{6}\\.\\d{4}\\*kWh"

  #  - platform: obis_d0
  #    name: "Consumed Energy Tariff 2"
  #    obis_d0_id: my_sm
  #    obis_code: "1-0:1.8.2*255"
  #    unit_of_measurement: kWh
  #    accuracy_decimals: 4
  #    state_class: total_increasing
  #    device_class: energy
  #    value_regex: "\\d{6}\\.\\d{4}\\*kWh"

  - platform: obis_d0
    name: "Provided Energy"
    obis_d0_id: my_sm
    obis_code: "1-0:2.8.0*255"
    unit_of_measurement: kWh
    accuracy_decimals: 4
    state_class: total_increasing
    device_class: energy
    value_regex: "\\d{6}\\.\\d{4}\\*kWh"

  - platform: obis_d0
    name: "Power"
    obis_d0_id: my_sm
    obis_code: "1-0:16.7.0*255"
    unit_of_measurement: W
    accuracy_decimals: 0
    state_class: measurement
    device_class: power
    value_regex: "-?\\d{6}\\*W"

  - platform: obis_d0
    name: "Voltage L1"
    obis_d0_id: my_sm
    obis_code: "1-0:32.7.0*255"
    unit_of_measurement: V
    accuracy_decimals: 1
    state_class: measurement
    device_class: voltage
    value_regex: "\\d{3}\\.\\d{1}\\*V"

  - platform: obis_d0
    name: "Voltage L2"
    obis_d0_id: my_sm
    obis_code: "1-0:52.7.0*255"
    unit_of_measurement: V
    accuracy_decimals: 1
    state_class: measurement
    device_class: voltage
    value_regex: "\\d{3}\\.\\d{1}\\*V"

  - platform: obis_d0
    name: "Voltage L3"
    obis_d0_id: my_sm
    obis_code: "1-0:72.7.0*255"
    unit_of_measurement: V
    accuracy_decimals: 1
    state_class: measurement
    device_class: voltage
    value_regex: "\\d{3}\\.\\d{1}\\*V"

  - platform: obis_d0
    name: "Current L1"
    obis_d0_id: my_sm
    obis_code: "1-0:31.7.0*255"
    unit_of_measurement: A
    accuracy_decimals: 2
    state_class: measurement
    device_class: current
    value_regex: "-?\\d{3}\\.\\d{2}\\*A"

  - platform: obis_d0
    name: "Current L2"
    obis_d0_id: my_sm
    obis_code: "1-0:51.7.0*255"
    unit_of_measurement: A
    accuracy_decimals: 2
    state_class: measurement
    device_class: current
    value_regex: "-?\\d{3}\\.\\d{2}\\*A"

  - platform: obis_d0
    name: "Current L3"
    obis_d0_id: my_sm
    obis_code: "1-0:71.7.0*255"
    unit_of_measurement: A
    accuracy_decimals: 2
    state_class: measurement
    device_class: current
    value_regex: "-?\\d{3}\\.\\d{2}\\*A"

  - platform: obis_d0
    name: "Phase Angle UL2-UL1"
    obis_d0_id: my_sm
    obis_code: "1-0:81.7.1*255"
    unit_of_measurement: °
    accuracy_decimals: 0
    state_class: measurement
    value_regex: "\\d{3}\\*deg"

  - platform: obis_d0
    name: "Phase Angle UL3-UL1"
    obis_d0_id: my_sm
    obis_code: "1-0:81.7.2*255"
    unit_of_measurement: °
    accuracy_decimals: 0
    state_class: measurement
    value_regex: "\\d{3}\\*deg"

  - platform: obis_d0
    name: "Phase Angle IL1-UL1"
    obis_d0_id: my_sm
    obis_code: "1-0:81.7.4*255"
    unit_of_measurement: °
    accuracy_decimals: 0
    state_class: measurement
    value_regex: "\\d{3}\\*deg"

  - platform: obis_d0
    name: "Phase Angle IL2-UL2"
    obis_d0_id: my_sm
    obis_code: "1-0:81.7.15*255"
    unit_of_measurement: °
    accuracy_decimals: 0
    state_class: measurement
    value_regex: "\\d{3}\\*deg"

  - platform: obis_d0
    name: "Phase Angle IL3-UL3"
    obis_d0_id: my_sm
    obis_code: "1-0:81.7.26*255"
    unit_of_measurement: °
    accuracy_decimals: 0
    state_class: measurement
    value_regex: "\\d{3}\\*deg"

  - platform: obis_d0
    name: "Power Frequency"
    obis_d0_id: my_sm
    obis_code: "1-0:14.7.0*255"
    unit_of_measurement: Hz
    accuracy_decimals: 1
    state_class: measurement
    device_class: frequency
    value_regex: "\\d{2}\\.\\d{1}\\*deg"

  - platform: obis_d0
    name: "Consumed Power last 1d"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*96"
    unit_of_measurement: kWh
    accuracy_decimals: 1
    state_class: measurement
    device_class: energy
    value_regex: "\\d{5}\\.\\d{1}\\*kWh"

  - platform: obis_d0
    name: "Consumed Power last 7d"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*97"
    unit_of_measurement: kWh
    accuracy_decimals: 1
    state_class: measurement
    device_class: energy
    value_regex: "\\d{5}\\.\\d{1}\\*kWh"

  - platform: obis_d0
    name: "Consumed Power last 30d"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*98"
    unit_of_measurement: kWh
    accuracy_decimals: 1
    state_class: measurement
    device_class: energy
    value_regex: "\\d{5}\\.\\d{1}\\*kWh"

  - platform: obis_d0
    name: "Consumed Power last 365d"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*99"
    unit_of_measurement: kWh
    accuracy_decimals: 1
    state_class: measurement
    device_class: energy
    value_regex: "\\d{5}\\.\\d{1}\\*kWh"

  - platform: obis_d0
    name: "Consumed Power last reset"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*100"
    unit_of_measurement: kWh
    accuracy_decimals: 1
    state_class: measurement
    device_class: energy
    value_regex: "\\d{5}\\.\\d{1}\\*kWh"

  - platform: obis_d0
    name: "CRC"
    obis_d0_id: my_sm
    obis_code: "1-0:96.90.2*255"
    value_regex: "[0-9a-fA-F]{4}"
    format: hex

  - platform: obis_d0
    name: "Status"
    obis_d0_id: my_sm
    obis_code: "1-0:97.97.0*255"
    value_regex: "[0-9a-fA-F]{8}"
    format: hex

text_sensor:
  - platform: obis_d0
    name: "Firmware Version"
    obis_d0_id: my_sm
    obis_code: "1-0:0.2.0*255"
    entity_category: diagnostic
    value_regex: "\\w{20}"

  - platform: obis_d0
    name: "Device Identification"
    obis_d0_id: my_sm
    obis_code: "1-0:96.1.0*255"
    entity_category: diagnostic
    value_regex: "\\w{16}"
```
