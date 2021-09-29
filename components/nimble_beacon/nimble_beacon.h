#pragma once

#include "esphome/core/component.h"
#include "NimBLEDevice.h"
#include "NimBLEBeacon.h"


namespace aember {

namespace nimble_beacon {


class NimBleBeacon : public esphome::Component {
public:
    void setup() override;

    float get_setup_priority() const override;

    void dump_config() override;


    /**
     * Sets the component version (for logging purposes).
     * 
     */
    void set_version(const char *version) { this->version_ = version; }
    
    void set_major(const uint16_t major) { this->major_ = major; }
    void set_minor(const uint16_t minor) { this->minor_ = minor; }
    void set_uuid(const std::array<uint8_t, 16> &uuid) { this->uuid_ = uuid; }
    
    void update_advertisement(const std::array<uint8_t, 16> &uuid);



protected:
    std::string version_{"unknown"};
    std::array<uint8_t, 16> uuid_;
    uint16_t major_{0};
    uint16_t minor_{0};

    BLEAdvertising *advertising_{nullptr};
};

} // namespace nimble_beacon
} // namespace aember
