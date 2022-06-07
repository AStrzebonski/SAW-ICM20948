#include "bsp_clock.hpp"

// Nasty (but functional) way of suppresing C libraries warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wvolatile"
#pragma GCC diagnostic ignored "-Wconversion"
#include "stm32f7xx_hal.h"
#pragma GCC diagnostic pop
#include <cstdio>

namespace swaw::bsp {

    void delay(std::chrono::milliseconds duration) {
        HAL_Delay(duration.count());
    }


} // namespace swaw::bsp