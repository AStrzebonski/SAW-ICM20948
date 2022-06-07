#include "bsp_led.hpp"

#include "stm32f7xx_hal.h"


namespace swaw::bsp {

    void turnOn(LED l) {
         switch (l) {
            case LED::LED1: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); break;
            case LED::LED2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); break;
            case LED::LED3: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); break;
         }
    }


    void turnOff(LED l) {
         switch (l) {
            case LED::LED1: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); break;
            case LED::LED2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); break;
            case LED::LED3: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); break;
         }
    }


    void toggle(LED l)  {
        switch (l) {
            case LED::LED1: HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8); break;
            case LED::LED2: HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9); break;
            case LED::LED3: HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); break;
        }
    }


} // namespace swaw::bsp

