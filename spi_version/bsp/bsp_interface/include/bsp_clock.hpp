#ifndef BSP_CLOCK_HPP_
#define BSP_CLOCK_HPP_

#include <chrono>

namespace swaw::bsp {

    /**
     * @brief Blocks program execution for desired duration
     *
     * @param[in] duration duration to wait
     */
    void delay(std::chrono::milliseconds duration);


} // namespace swaw::bsp


#endif