#ifndef BSP_HPP_
#define BSP_HPP_

namespace swaw::bsp {

    /**
     * @brief Initialize Board Support Package
     */
    void init();

} // namespace swaw::bsp

#include "bsp_led.hpp"
#include "bsp_clock.hpp"
#include "bsp_com.hpp"

#endif