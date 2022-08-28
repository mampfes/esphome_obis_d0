import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_FORMAT, CONF_ID

from .. import CONF_SM_D0_ID, CONF_OBIS_CODE, CONF_VALUE_REGEX, SmartMeterD0, obis_code, sm_d0_ns

AUTO_LOAD = ["sm_d0"]

ValueFormat = sm_d0_ns.enum("ValueFormat")
VALUE_FORMAT_TYPES = {
    "float": ValueFormat.ValueFormat_Float,
    "hex": ValueFormat.ValueFormat_Hex,
}

SmartMeterD0Sensor = sm_d0_ns.class_(
    "SmartMeterD0Sensor", sensor.Sensor, cg.Component)


CONFIG_SCHEMA = sensor.sensor_schema().extend(
    {
        cv.GenerateID(): cv.declare_id(SmartMeterD0Sensor),
        cv.GenerateID(CONF_SM_D0_ID): cv.use_id(SmartMeterD0),
        cv.Required(CONF_OBIS_CODE): obis_code,
        cv.Optional(CONF_VALUE_REGEX, default=".*"): cv.string,
        cv.Optional(CONF_FORMAT, default="float"): cv.enum(VALUE_FORMAT_TYPES, lower=True),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(
        config[CONF_ID], config[CONF_OBIS_CODE], config[CONF_VALUE_REGEX], config[CONF_FORMAT]
    )
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    sm_d0 = await cg.get_variable(config[CONF_SM_D0_ID])
    cg.add(sm_d0.register_sensor(var))
