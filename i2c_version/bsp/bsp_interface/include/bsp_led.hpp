#ifndef BSP_LED_HPP_
#define BSP_LED_HPP_

namespace swaw::bsp {

    /// Defines possible LED keys
    enum class LED { LED1, LED2, LED3 };

    /**
     * @brief Toggles state of one of the LEDs
     * @param[in] l key of LED to be toggled
     */
    void toggle(LED l);

    /**
     * @brief Turns on of one of the LEDs
     * @param[in] l key of LED to be toggled
     */
    void turnOn(LED l);

    /**
     * @brief Turns off of one of the LEDs
     * @param[in] l key of LED to be toggled
     */
    void turnOff(LED l);

} // namespace swaw::bsp

#endif