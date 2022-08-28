import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID

from .. import CONF_SM_D0_ID, CONF_OBIS_CODE, CONF_VALUE_REGEX, SmartMeterD0, obis_code, sm_d0_ns

AUTO_LOAD = ["sml"]

SmartMeterD0TextSensor = sm_d0_ns.class_(
    "SmartMeterD0TextSensor", text_sensor.TextSensor, cg.Component)

CONFIG_SCHEMA = text_sensor.TEXT_SENSOR_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(SmartMeterD0TextSensor),
        cv.GenerateID(CONF_SM_D0_ID): cv.use_id(SmartMeterD0),
        cv.Required(CONF_OBIS_CODE): obis_code,
        cv.Optional(CONF_VALUE_REGEX, default=".*"): cv.string,
    }
)


async def to_code(config):
    var = cg.new_Pvariable(
        config[CONF_ID],
        config[CONF_OBIS_CODE],
        config[CONF_VALUE_REGEX],
    )
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    sm_d0 = await cg.get_variable(config[CONF_SM_D0_ID])
    cg.add(sm_d0.register_sensor(var))
