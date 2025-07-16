import re

import esphome.codegen as cg
import esphome.config_validation as cv
# from esphome.cpp_helpers import setup_entity
from esphome.components import uart
from esphome.const import CONF_ID, CONF_TRIGGER_ID
from esphome import automation

CODEOWNERS = ["@mampfes"]

DEPENDENCIES = ["uart"]

obis_d0_ns = cg.esphome_ns.namespace("obis_d0")
SmartMeterD0 = obis_d0_ns.class_("SmartMeterD0", cg.Component, uart.UARTDevice)
MULTI_CONF = True

CONF_OBIS_D0_ID = "obis_d0_id"
CONF_OBIS_CODE = "obis_code"
CONF_VALUE_REGEX = "value_regex"
CONF_ON_TELEGRAM = "on_telegram"
CONF_OPTIMIZE_SIZE = "optimize_size"

# Triggers
TelegramTrigger = obis_d0_ns.class_("TelegramTrigger", automation.Trigger.template())

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SmartMeterD0),
        cv.Optional(CONF_ON_TELEGRAM): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(TelegramTrigger),
            }
        ),
        cv.Optional(CONF_OPTIMIZE_SIZE, False): cv.boolean
    }
).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for conf in config.get(CONF_ON_TELEGRAM, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID])
        cg.add(var.register_telegram_trigger(trigger))
        await automation.build_automation(trigger, [], conf)

    if config[CONF_OPTIMIZE_SIZE]:
        cg.add_define("COMPONENT_OBIS_D0_OPTIMIZE_SIZE", "1")

def obis_code(value):
    value = cv.string(value)
    #match = re.match(r"^\d{1,3}-\d{1,3}:\d{1,3}\.\d{1,3}\.\d{1,3}$", value)
    # if match is None:
    #    raise cv.Invalid(f"{value} is not a valid OBIS code")
    return value
