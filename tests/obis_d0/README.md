# Parser regression tests

Run `python3 tests/obis_d0/run_tests.py` from the repository root.
Requires Python 3 and g++ with AddressSanitizer and UndefinedBehaviorSanitizer.
No Python packages or ESPHome installation are required.

The real SmartMeterD0.cpp and tiny-regex source are compiled against minimal
UART/framework adapters. Tests cover long garbage streams before a telegram,
record boundaries, oversized records, every two-chunk split of a telegram,
malformed line endings, STX/ETX handling, and recovery to valid readings.
Before the parser bounds fix, the long garbage-stream case fails through the
enabled std::array bounds assertion.

These tests verify parser memory bounds and resynchronization, not actual
ESP8266 UART behavior, firmware builds, API stability, or meter compatibility.
