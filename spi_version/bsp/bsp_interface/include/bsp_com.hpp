#ifndef BSP_COM_HPP_
#define BSP_COM_HPP_

#include <cstdint>
#include <span>
namespace swaw::bsp {

    enum CommunicationInterfaceKey { SENSOR1, CONTROLLER };


    enum AddressingMode : std::uint8_t { AddressNonRelevant = 0 };

    /**
     * @brief Writes data to selected interface
     *
     * @param[in] data data to be written
     * @param[in] interfaceKey interface key
     * @return remaining data, when at least 1 character was sent, or empty span (with nullptr as data) on write failure
     */
    std::span<char const> write(CommunicationInterfaceKey interfaceKey, std::span<char const> data, std::uint8_t address = AddressNonRelevant);


    /**
     * @brief Reads data from the interface into memory region
     *
     * @param[in] buffer data buffer
     * @param[in] interfaceKey interface key
     * @return subspan of buffer, containing read data, or empty span (with nullptr as data) on read failure
     */
    std::span<char> read(CommunicationInterfaceKey interfaceKey, std::span<char> buffer, std::uint8_t address = AddressNonRelevant);


    /**
     * @brief Flushes input and output buffer (if present) of the interface
     *
     * @param[in] interfaceKey interface key
     */
    void flush(CommunicationInterfaceKey interfaceKey);


} // namespace swaw::bsp

#endif