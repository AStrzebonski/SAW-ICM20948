#include "bsp_led.hpp"

#include <array>
#include <iostream>
#include <stdexcept>
namespace swaw::bsp {


    std::array<bool, 3> ledState{};

    /**
     * @brief Prints state of the given LED
     *
     * @param[in] x led key
     */
    static void printState(LED x) {
        auto const printableState = [](bool s) { return s ? "on" : "off"; };

        switch (x) {
            case LED::LED1: std::cout << "LED1 is " << printableState(ledState[0]) << '\n'; break;
            case LED::LED2: std::cout << "LED2 is " << printableState(ledState[1]) << '\n'; break;
            case LED::LED3: std::cout << "LED3 is " << printableState(ledState[2]) << '\n'; break;
            default: throw std::out_of_range("invalid led key");
        }
    }


    void turnOn(LED l) {
        switch (l) {
            case LED::LED1: ledState[0] = 1; break;
            case LED::LED2: ledState[1] = 1; break;
            case LED::LED3: ledState[2] = 1; break;
            default: throw std::out_of_range("invalid led key");
        }
        printState(l);
    }


    void turnOff(LED l) {
        switch (l) {
            case LED::LED1: ledState[0] = 0; break;
            case LED::LED2: ledState[1] = 0; break;
            case LED::LED3: ledState[2] = 0; break;
            default: throw std::out_of_range("invalid led key");
        }
        printState(l);
    }


    void toggle(LED l) {
        switch (l) {
            case LED::LED1: ledState[0] ^= 1; break;
            case LED::LED2: ledState[1] ^= 1; break;
            case LED::LED3: ledState[2] ^= 1; break;
            default: throw std::out_of_range("invalid led key");
        }
        printState(l);
    }


} // namespace swaw::bsp
