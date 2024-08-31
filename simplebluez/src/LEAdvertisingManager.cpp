#include <simplebluez/LEAdvertisingManager.h>
#include <simplebluez/interfaces/LEAdvertisingManager1.h>

using namespace SimpleBluez;

LEAdvertisingManager::LEAdvertisingManager(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name,
                                           const std::string& path)
    : Proxy(conn, bus_name, path) {}

LEAdvertisingManager::~LEAdvertisingManager() {}

void LEAdvertisingManager::register_advertisement(std::shared_ptr<LEAdvertisement> advertisement) {
    _advertisements.push_back(advertisement);
    le_advertising_manager1()->RegisterAdvertisement(advertisement->path());
}

void LEAdvertisingManager::unregister_advertisement(std::shared_ptr<LEAdvertisement> advertisement) {
    _advertisements.remove(advertisement);
    le_advertising_manager1()->UnregisterAdvertisement(advertisement->path());
}

std::shared_ptr<LEAdvertisement> LEAdvertisingManager::new_advertisement() {
    return std::make_shared<SimpleBluez::LEAdvertisement>(_conn, "/ad1");
}

std::shared_ptr<SimpleDBus::Interface> LEAdvertisingManager::interfaces_create(const std::string& interface_name) {
    if (interface_name == "org.bluez.LEAdvertisingManager1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<LEAdvertisingManager1>(_conn, _path));
    }

    return Proxy::interfaces_create(interface_name);
}

std::shared_ptr<LEAdvertisingManager1> LEAdvertisingManager::le_advertising_manager1() {
    return std::dynamic_pointer_cast<LEAdvertisingManager1>(interface_get("org.bluez.LEAdvertisingManager1"));
}
