#pragma once

#include <simpledbus/advanced/Proxy.h>

#include <simplebluez/Device.h>
#include <simplebluez/LEAdvertisement.h>
#include <simplebluez/interfaces/Adapter1.h>
#include <simplebluez/interfaces/LEAdvertisingManager1.h>

#include <functional>
#include <list>

namespace SimpleBluez {

class Adapter : public SimpleDBus::Proxy {
  public:
    typedef Adapter1::DiscoveryFilter DiscoveryFilter;

    Adapter(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    virtual ~Adapter();

    std::string identifier() const;
    std::string address();
    bool discovering();
    bool powered();

    void discovery_filter(const DiscoveryFilter& filter);
    void discovery_start();
    void discovery_stop();

    std::shared_ptr<Device> device_get(const std::string& path);
    void device_remove(const std::string& path);
    void device_remove(const std::shared_ptr<Device>& device);
    std::vector<std::shared_ptr<Device>> device_paired_get();

    void set_on_device_updated(std::function<void(std::shared_ptr<Device> device)> callback);
    void clear_on_device_updated();

    void register_advertisement(std::shared_ptr<LEAdvertisement> advertisement);
    void unregister_advertisement(std::shared_ptr<LEAdvertisement> advertisement);
    std::shared_ptr<LEAdvertisement> new_advertisement();

  private:
    std::shared_ptr<SimpleDBus::Proxy> path_create(const std::string& path) override;
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;

    std::list<std::shared_ptr<LEAdvertisement>> _advertisements;

    std::shared_ptr<Adapter1> adapter1();
    std::shared_ptr<LEAdvertisingManager1> le_advertising_manager1();
};

}  // namespace SimpleBluez
