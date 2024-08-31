#include "simplebluez/interfaces/LEAdvertisingManager1.h"

using namespace SimpleBluez;

LEAdvertisingManager1::LEAdvertisingManager1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.LEAdvertisingManager1") {}

void LEAdvertisingManager1::RegisterAdvertisement(std::string advertisement) {
    auto msg = create_method_call("RegisterAdvertisement");
    msg.append_argument(SimpleDBus::Holder::create_object_path(advertisement), "o");
    // No clue about this dict, bluez code seems to ignore it
    SimpleDBus::Holder optionsDict = SimpleDBus::Holder::create_dict();
    msg.append_argument(optionsDict, "a{sv}");
    _conn->send(msg);
    // auto response = _conn->send_with_reply_and_block(msg);
    // response.get_path();
}

void LEAdvertisingManager1::UnregisterAdvertisement(std::string advertisement) {
    auto msg = create_method_call("UnregisterAdvertisement");
    msg.append_argument(SimpleDBus::Holder::create_object_path(advertisement), "o");
    _conn->send_with_reply_and_block(msg);
}
