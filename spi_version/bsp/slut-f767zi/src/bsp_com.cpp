#include "bsp_com.hpp"

// Nasty (but functional) way of suppresing C libraries warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wvolatile"
#pragma GCC diagnostic ignored "-Wconversion"
#include "main.h"
#include "stm32f7xx_hal.h"

#pragma GCC diagnostic pop

extern "C" UART_HandleTypeDef huart3;
extern "C" SPI_HandleTypeDef  hspi3;


namespace swaw::bsp {
    std::span<char const> write(CommunicationInterfaceKey interfaceKey, std::span<char const> data, std::uint8_t address) {
        if (CommunicationInterfaceKey::SENSOR1 == interfaceKey) {
            HAL_GPIO_WritePin(SENS1_CS_GPIO_Port, SENS1_CS_Pin, GPIO_PIN_RESET);
            auto s1 = HAL_SPI_Transmit(&hspi3, const_cast<uint8_t*>(&address), 1, 1000);
            auto s2 = HAL_SPI_Transmit(&hspi3, const_cast<uint8_t*>(reinterpret_cast<std::uint8_t const*>(data.data())), data.size(), 1000);
            HAL_GPIO_WritePin(SENS1_CS_GPIO_Port, SENS1_CS_Pin, GPIO_PIN_SET);
            if ((HAL_OK == s1) && (HAL_OK == s2)) {
                return data.subspan(data.size());
            }
        }
        if (CommunicationInterfaceKey::CONTROLLER == interfaceKey) {
            if (HAL_OK == HAL_UART_Transmit(&huart3, const_cast<uint8_t*>(reinterpret_cast<uint8_t const*>(data.data())), data.size(), 10000)) {
                return data.subspan(data.size());
            }
        }
        return {};
    }

    std::span<char> read(CommunicationInterfaceKey interfaceKey, std::span<char> buffer, std::uint8_t address) {
        if (CommunicationInterfaceKey::SENSOR1 == interfaceKey) {
            HAL_GPIO_WritePin(SENS1_CS_GPIO_Port, SENS1_CS_Pin, GPIO_PIN_RESET);
            auto s1 = HAL_SPI_Transmit(&hspi3, const_cast<uint8_t*>(&address), 1, 1000);
            auto s2 = HAL_SPI_Receive(&hspi3, reinterpret_cast<std::uint8_t*>(buffer.data()), buffer.size(), 1000);
            HAL_GPIO_WritePin(SENS1_CS_GPIO_Port, SENS1_CS_Pin, GPIO_PIN_SET);
            if ((HAL_OK == s1) && (HAL_OK == s2)) {
                return buffer;
            }
        }
        if (CommunicationInterfaceKey::CONTROLLER == interfaceKey) {
            if (HAL_OK == HAL_UART_Receive(&huart3, reinterpret_cast<uint8_t*>(buffer.data()), buffer.size(), 10000)) {
                return buffer;
            }
        }
        return {};
    }

    void flush(CommunicationInterfaceKey interfaceKey) {
        // Nothing to do (so far)
    }

} // namespace swaw::bsp