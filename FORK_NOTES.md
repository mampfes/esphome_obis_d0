# Parser robustness patch

Based on upstream commit `15a98f57fc522763f93db48ef6bdebc481b4f775`.
Related report: https://github.com/mampfes/esphome_obis_d0/issues/23

The parser previously appended all bytes to its 150-byte record buffer while
looking for `/`, without checking the buffer boundary. Noise or booting midway
through a sufficiently long telegram could write beyond the array. Reset also
left the length unchanged after an oversized record.

This patch discards bytes until `/`, resets the record length together with the
parser state, and checks the boundary before record writes. It also corrects
ETX from 0x02 (STX) to 0x03. Existing OBIS parsing and sensor registration stay
unchanged. Each OBIS code still supports only one registered sensor.

The original out-of-bounds access was reproduced in a host regression test;
the patched version passes with memory and bounds instrumentation. This does
not establish that it caused a particular device's API/OTA failures. Hardware
validation on an ESP8266/eBZ DD3 is still pending.

See `tests/obis_d0/README.md` to run the tests. For initial ESP8266 testing use
`optimize_size: true` and a single sensor, keeping a known-good recovery build.
