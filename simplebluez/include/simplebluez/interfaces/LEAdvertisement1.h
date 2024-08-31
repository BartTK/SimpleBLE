#pragma once

#include <simpledbus/advanced/Interface.h>

#include <map>
#include <string>
#include <vector>

#include "simplebluez/Types.h"

namespace SimpleBluez {

// https://github.com/bluez/bluez/blob/master/doc/org.bluez.LEAdvertisement.rst
class LEAdvertisement1 : public SimpleDBus::Interface {
  public:
    // ----- TYPES -----

    // ----- CONSTRUCTORS -----
    LEAdvertisement1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    virtual ~LEAdvertisement1() = default;

    // ----- METHODS -----
    // void Release();

    // // ----- PROPERTIES -----
    // std::string Type();
    // std::vector<std::string> ServiceUUIDs();
    void AppendManufacturerData(uint16_t manufacturerId, ByteArray& data);
    void SetInterval(std::chrono::milliseconds min, std::chrono::milliseconds max);
    // std::vector<std::string> SolicitUUIDs();
    // std::map<uint16_t, ByteArray> ServiceData(bool refresh = true);
    // bool IncludeTxPower(bool refresh = true);

  protected:
    // void message_handle(SimpleDBus::Message& msg) override;

    // void property_changed(std::string option_name) override;

    // std::map<uint16_t, ByteArray> _manufacturer_data;
    // std::map<uint16_t, ByteArray> _service_data;
};

}  // namespace SimpleBluez
