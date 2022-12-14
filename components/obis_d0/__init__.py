import re

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

CODEOWNERS = ["@mampfes"]

DEPENDENCIES = ["uart"]

obis_d0_ns = cg.esphome_ns.namespace("obis_d0")
SmartMeterD0 = obis_d0_ns.class_("SmartMeterD0", cg.Component, uart.UARTDevice)
MULTI_CONF = True

CONF_OBIS_D0_ID = "obis_d0_id"
CONF_OBIS_CODE = "obis_code"
CONF_VALUE_REGEX = "value_regex"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SmartMeterD0),
    }
).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)


def obis_code(value):
    value = cv.string(value)
    #match = re.match(r"^\d{1,3}-\d{1,3}:\d{1,3}\.\d{1,3}\.\d{1,3}$", value)
    # if match is None:
    #    raise cv.Invalid(f"{value} is not a valid OBIS code")
    return value
