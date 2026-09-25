#!/usr/bin/env python3
"""Run the real parser with a fake UART and host memory/bounds checks."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
TEST = ROOT / "tests" / "obis_d0"
COMPONENT = ROOT / "components" / "obis_d0"
with tempfile.TemporaryDirectory(prefix="obis-d0-test-") as tmp:
    binary = str(Path(tmp) / "parser_test")
    subprocess.run([
        "g++", "-std=c++17", "-g", "-fsanitize=address,undefined",
        "-D_GLIBCXX_ASSERTIONS", "-DCOMPONENT_OBIS_D0_OPTIMIZE_SIZE=1",
        "-I" + str(TEST / "stubs"), "-I" + str(COMPONENT),
        str(TEST / "parser_test.cpp"), str(COMPONENT / "SmartMeterD0.cpp"),
        str(COMPONENT / "re.cpp"), "-o", binary,
    ], check=True)
    subprocess.run([binary], check=True, env={
        **os.environ, "ASAN_OPTIONS": "detect_leaks=0",
        "UBSAN_OPTIONS": "halt_on_error=1",
    })
