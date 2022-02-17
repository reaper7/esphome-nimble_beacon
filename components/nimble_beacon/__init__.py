from typing import Optional
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_TYPE,
    CONF_UUID,
    ESP_PLATFORM_ESP32,
)


""" Component configuration
"""
NIMBLE_BEACON_VERSION = "1.0.0"
LIB_NIMBLE_ARDUINO_VERSION = "1.3.1"
ESP_PLATFORMS = [PLATFORM_ESP32]
CODEOWNERS = ["akomelj"]


"""NimBLE beacon configuration keys
"""
CONF_MAJOR = "major"
CONF_MINOR = "minor"


"""NimBLE beacon namespace and class declarations

Namespace: aember::nimble_beacon
Class: NimBleBeacon
"""
nimble_ns = cg.global_ns.namespace("aember").namespace("nimble_beacon")
NimBleBleacon = nimble_ns.class_("NimBleBeacon", cg.Component)


"""NimBLE beacon configuration schema

"""
CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(NimBleBleacon),
        cv.Required(CONF_TYPE): cv.one_of("IBEACON", upper=True),
        cv.Required(CONF_UUID): cv.uuid,
        cv.Optional(CONF_MAJOR, default=10167): cv.uint16_t,
        cv.Optional(CONF_MINOR, default=61958): cv.uint16_t,
    }
)


async def to_code(config):
    """Converts NimBLE beacon configuration to code.

    - requests dependencies
    - creates the beacon (component)
    - sets configuration parameters
    - registers the component
    """
    
    # depends on NimBLE-Arduino library
    cg.add_library("NimBLE-Arduino", LIB_NIMBLE_ARDUINO_VERSION)
    
    # configure the component
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_version(NIMBLE_BEACON_VERSION))
    cg.add(var.set_major(config[CONF_MAJOR]))
    cg.add(var.set_minor(config[CONF_MINOR]))

    # set beacon proximity UUID
    uuid = config[CONF_UUID].hex
    uuid_arr = [
        cg.RawExpression("0x{}".format(uuid[i : i + 2])) for i in range(0, len(uuid), 2)
    ]
    cg.add(var.set_uuid(uuid_arr))
    
    # register the component
    await cg.register_component(var, config)
