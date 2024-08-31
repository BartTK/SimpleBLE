#pragma once

#include <simpledbus/advanced/Interface.h>

#include <map>
#include <string>

#include "simplebluez/Types.h"

namespace SimpleBluez {

// https://github.com/bluez/bluez/blob/master/doc/org.bluez.LEAdvertisement.rst
class LEAdvertisingManager1 : public SimpleDBus::Interface {
  public:
    LEAdvertisingManager1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    virtual ~LEAdvertisingManager1() = default;

    // ----- METHODS -----
    void RegisterAdvertisement(std::string advertisement);
    void UnregisterAdvertisement(std::string advertisement);
};

}  // namespace SimpleBluez
