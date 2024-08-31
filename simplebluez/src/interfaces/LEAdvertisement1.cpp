#include "simplebluez/interfaces/LEAdvertisement1.h"

namespace {
const std::string ManufacturerData = "ManufacturerData";
}

using namespace SimpleBluez;

LEAdvertisement1::LEAdvertisement1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.LEAdvertisement1") {}

void LEAdvertisement1::AppendManufacturerData(uint16_t manufacturerId, ByteArray& data) {
    std::scoped_lock lock(_property_update_mutex);
    auto propertyIt = _properties.find(ManufacturerData);
    if (propertyIt == _properties.end()) {
        _properties[ManufacturerData] = SimpleDBus::Holder::create_dict();
        _property_valid_map[ManufacturerData] = true;
    }
    propertyIt = _properties.find(ManufacturerData);

    auto dataHolder = SimpleDBus::Holder::create_array();
    for (const auto& byte : data) {
        dataHolder.array_append(SimpleDBus::Holder::create_byte(byte));
    }

    propertyIt->second.dict_remove(manufacturerId);
    propertyIt->second.dict_append(SimpleDBus::Holder::Type::UINT16, manufacturerId, dataHolder);

    emit_property_changed(ManufacturerData, propertyIt->second);
}

void LEAdvertisement1::SetInterval(std::chrono::milliseconds min, std::chrono::milliseconds max) {
    std::scoped_lock lock(_property_update_mutex);
    _properties["MinInterval"] = SimpleDBus::Holder::create_uint32(min.count());
    _property_valid_map["MinInterval"] = true;
    _properties["MaxInterval"] = SimpleDBus::Holder::create_uint32(max.count());
    _property_valid_map["MaxInterval"] = true;
}
// void LEAdvertisement1::message_handle(SimpleDBus::Message& msg) {
//     if (msg.get_type() == SimpleDBus::Message::Type::METHOD_CALL) {
//     }

//     SimpleDBus::Message reply = SimpleDBus::Message::create_error(msg, "WIP", "WIP");
//     _conn->send(reply);
// }

// void LEAdvertisement1::Release() {
//     auto msg = create_method_call("Release");
//     _conn->send_with_reply_and_block(msg);
// }

// std::string LEAdvertisement1::Type() {
//     std::scoped_lock lock(_property_update_mutex);
//     return _properties["Type"].get_string();
// }

// std::vector<std::string> LEAdvertisement1::ServiceUUIDs() {
//     std::scoped_lock lock(_property_update_mutex);

//     std::vector<std::string> uuids;
//     for (SimpleDBus::Holder& uuid : _properties["ServiceUUIDs"].get_array()) {
//         uuids.push_back(uuid.get_string());
//     }

//     return uuids;
// }

// std::map<uint16_t, ByteArray> LEAdvertisement1::ManufacturerData(bool refresh) {
//     if (refresh) {
//         property_refresh("ManufacturerData");
//     }

//     // Use the locally cached version to avoid parsing the map multiple times.
//     std::scoped_lock lock(_property_update_mutex);
//     return _manufacturer_data;
// }

// std::vector<std::string> LEAdvertisement1::SolicitUUIDs() {
//     std::scoped_lock lock(_property_update_mutex);

//     std::vector<std::string> uuids;
//     for (SimpleDBus::Holder& uuid : _properties["SolicitUUIDs"].get_array()) {
//         uuids.push_back(uuid.get_string());
//     }

//     return uuids;
// }

// std::map<uint16_t, ByteArray> LEAdvertisement1::ServiceData(bool refresh) {
//     if (refresh) {
//         property_refresh("ServiceData");
//     }

//     // Use the locally cached version to avoid parsing the map multiple times.
//     std::scoped_lock lock(_property_update_mutex);
//     return _service_data;
// }

// bool LEAdvertisement1::IncludeTxPower(bool refresh) {
//     if (refresh) {
//         property_refresh("IncludeTxPower");
//     }

//     std::scoped_lock lock(_property_update_mutex);
//     return _properties["IncludeTxPower"].get_boolean();
// }

// void LEAdvertisement1::property_changed(std::string option_name) {
//     if (option_name == "ManufacturerData") {
//         std::scoped_lock lock(_property_update_mutex);

//         _manufacturer_data.clear();
//         std::map<uint16_t, SimpleDBus::Holder> manuf_data = _properties["ManufacturerData"].get_dict_uint16();
//         // Loop through all received keys and store them.
//         for (auto& [key, value_array] : manuf_data) {
//             ByteArray raw_manuf_data;
//             for (auto& elem : value_array.get_array()) {
//                 raw_manuf_data.push_back(elem.get_byte());
//             }
//             _manufacturer_data[key] = raw_manuf_data;
//         }
//     } else if (option_name == "ServiceData") {
//         std::scoped_lock lock(_property_update_mutex);

//         _service_data.clear();
//         std::map<uint16_t, SimpleDBus::Holder> manuf_data = _properties["ServiceData"].get_dict_uint16();
//         // Loop through all received keys and store them.
//         for (auto& [key, value_array] : manuf_data) {
//             ByteArray raw_service_data;
//             for (auto& elem : value_array.get_array()) {
//                 raw_service_data.push_back(elem.get_byte());
//             }
//             _service_data[key] = raw_service_data;
//         }
//     }
// }
