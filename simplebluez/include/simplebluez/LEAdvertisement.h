#pragma once

#include <simpledbus/advanced/Proxy.h>

#include <simplebluez/interfaces/LEAdvertisement1.h>

namespace SimpleBluez {

class LEAdvertisement : public SimpleDBus::Proxy {
  public:
    LEAdvertisement(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& path);
    virtual ~LEAdvertisement();

    void AppendManufacturerData(uint16_t manufacturerId, ByteArray& data);
    void SetInterval(std::chrono::milliseconds min, std::chrono::milliseconds max);

  private:
    std::shared_ptr<LEAdvertisement1> le_advertisement1();
};

}  // namespace SimpleBluez
