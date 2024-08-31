#include <simplebluez/LEAdvertisement.h>
#include <simplebluez/interfaces/LEAdvertisement1.h>
#include <simpledbus/interfaces/ObjectManager.h>

using namespace SimpleBluez;

LEAdvertisement::LEAdvertisement(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& path)
    : Proxy(conn, "org.bluez", path) {
    _interfaces["org.freedesktop.DBus.ObjectManager"] = std::static_pointer_cast<SimpleDBus::Interface>(
        std::make_shared<SimpleDBus::ObjectManager>(_conn, _bus_name, _path));
    _interfaces["org.bluez.LEAdvertisement1"] = std::static_pointer_cast<SimpleDBus::Interface>(
        std::make_shared<LEAdvertisement1>(_conn, _path));
}

LEAdvertisement::~LEAdvertisement() {}

void LEAdvertisement::AppendManufacturerData(uint16_t manufacturerId, ByteArray& data) {
    le_advertisement1()->AppendManufacturerData(manufacturerId, data);
}

void LEAdvertisement::SetInterval(std::chrono::milliseconds min, std::chrono::milliseconds max) {
    le_advertisement1()->SetInterval(min, max);
}

std::shared_ptr<LEAdvertisement1> LEAdvertisement::le_advertisement1() {
    return std::dynamic_pointer_cast<LEAdvertisement1>(interface_get("org.bluez.LEAdvertisement1"));
}
