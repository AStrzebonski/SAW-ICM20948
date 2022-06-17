#include "bsp_com.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
std::vector<char> controllerOutData{};
std::vector<char> controllerInData{};

namespace swaw::bsp {

    static char const* printableName(CommunicationInterfaceKey x) {
        switch (x) {
            case CommunicationInterfaceKey::SENSOR1: return "SENSOR_1";
            case CommunicationInterfaceKey::CONTROLLER: return "CONTROLLER";
            default: throw std::out_of_range("invalid interface key");
        }
    }


    std::span<char const> write(CommunicationInterfaceKey interfaceKey, std::span<char const> data, std::uint8_t address) {
        std::cout << "writing " << data.size() << " bytes to interface " << printableName(interfaceKey) << "\n";
        if (CommunicationInterfaceKey::CONTROLLER == interfaceKey) {
            controllerOutData.insert(controllerOutData.end(), data.begin(), data.end());
            return data.subspan(data.size());
        }
        return {};
    }


    std::span<char> read(CommunicationInterfaceKey interfaceKey, std::span<char> buffer, std::uint8_t address) {
        std::cout << "reading at most " << buffer.size() << " bytes from interface " << printableName(interfaceKey) << "\n";
        if (CommunicationInterfaceKey::CONTROLLER == interfaceKey) {
            auto toCopy = std::min(buffer.size(), controllerInData.size());
            std::copy_n(controllerInData.begin(), toCopy, buffer.begin());
            return buffer.subspan(toCopy);
        }
        return {};
    }


    void flush(CommunicationInterfaceKey interfaceKey) {
        std::cout << "Flushing interface " << printableName(interfaceKey) << "\n";
        if (CONTROLLER == interfaceKey) {
            controllerOutData.clear();
            controllerInData.clear();
        }
    }

} // namespace swaw::bsp