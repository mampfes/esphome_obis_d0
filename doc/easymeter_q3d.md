# EasyMeter Q3D

Tested configuration: EasyMeter Q3DA3002 V3.04

UART configuration: 9600 Baud, 7E1

## Example

```yaml
external_components:
  - source: github://mampfes/esphome_obis_d0
  
uart:
  id: uart_bus
  rx_pin: GPIO16
  baud_rate: 9600
  data_bits: 7
  parity: EVEN
  stop_bits: 1

obis_d0:
  id: my_sm
  uart_id: uart_bus

sensor:
  - platform: obis_d0
    name: "Zaehlerstand"
    obis_d0_id: my_sm
    obis_code: "1-0:1.8.0*255"
    unit_of_measurement: kWh
    accuracy_decimals: 3
    state_class: total_increasing
    device_class: energy
    value_regex: "\d{8}\.\d{7}\*kWh"

  - platform: obis_d0
    name: "Gesamtleistung"
    obis_d0_id: my_sm
    obis_code: "1-0:1.7.0*255"
    unit_of_measurement: W
    accuracy_decimals: 0
    device_class: power
    state_class: measurement

  - platform: obis_d0
    name: "Leistung L1"
    obis_d0_id: my_sm
    obis_code: "1-0:21.7.0*255"
    unit_of_measurement: W
    accuracy_decimals: 0
    device_class: power
    state_class: measurement

  - platform: obis_d0
    name: "Leistung L2"
    obis_d0_id: my_sm
    obis_code: "1-0:41.7.0*255"
    unit_of_measurement: W
    accuracy_decimals: 0
    device_class: power
    state_class: measurement

  - platform: obis_d0
    name: "Leistung L3"
    obis_d0_id: my_sm
    obis_code: "1-0:61.7.0*255"
    unit_of_measurement: W
    accuracy_decimals: 0
    device_class: power
    state_class: measurement

text_sensor:
  - platform: obis_d0
    name: "Device Identification"
    obis_d0_id: my_sm
    obis_code: "0-0:96.1.255*255"
    entity_category: diagnostic
    value_regex: "\w{14}"

  - platform: obis_d0
    name: "Manufacturer ID"
    obis_d0_id: my_sm
    obis_code: "id"
    entity_category: diagnostic
```
