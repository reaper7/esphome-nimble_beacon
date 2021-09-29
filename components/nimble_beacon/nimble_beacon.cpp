#include "nimble_beacon.h"
#include "esphome/core/log.h"


namespace aember {

namespace nimble_beacon {


// log tag for ESPHome logging system
static const char *const TAG = "nimble_beacon";


void NimBleBeacon::setup() {
    using namespace esphome;

    ESP_LOGI(TAG, "Initializing NimBLE beacon");
    BLEDevice::init("NimBLE");
    BLEDevice::setPower(ESP_PWR_LVL_N12);

    // configure advertisement
    this->advertising_ = BLEDevice::getAdvertising();
    this->advertising_->setAdvertisementType(BLE_GAP_CONN_MODE_NON);
    this->update_advertisement(this->uuid_);

    // start advertising
    ESP_LOGI(TAG, "Starting BLE advertising");
    this->advertising_->start();
}


void NimBleBeacon::update_advertisement(const std::array<uint8_t, 16> &uuid) {
    using namespace esphome;
    this->set_uuid(uuid);

    // create iBeacon data
    auto beacon = BLEBeacon();
    beacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
    beacon.setMajor(this->major_);
    beacon.setMinor(this->minor_);
    auto nuuid = NimBLEUUID(this->uuid_.data(), this->uuid_.size(), true);
    ESP_LOGD(TAG, "UUID: %s", nuuid.toString().c_str());
    beacon.setProximityUUID(nuuid);
    beacon.setSignalPower(0xC5);    // from esp32_ble_beacon.cpp

    // create advertisement data
    auto data = BLEAdvertisementData();
    data.setFlags(0x04);    // BR_EDR_NOT_SUPPORTED 0x04
    data.setManufacturerData(beacon.getData());

    // configure advertisement
    this->advertising_->setAdvertisementData(data);
}


float NimBleBeacon::get_setup_priority() const {
    return esphome::setup_priority::DATA;
}


void NimBleBeacon::dump_config() {
    using namespace esphome;
    ESP_LOGCONFIG("", "NimBLE Beacon");
    ESP_LOGCONFIG("", "  Version: %s", this->version_.c_str());
    ESP_LOGCONFIG("", "  MAC: %s", BLEDevice::toString().c_str());
    ESP_LOGCONFIG("", "  UUID: %s", NimBLEUUID(this->uuid_.data(), this->uuid_.size(), true).toString().c_str());
}
} // namespace nimble_beacon
} // namespace aember
