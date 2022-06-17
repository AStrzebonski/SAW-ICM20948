#include "bsp_clock.hpp"

#include <thread>
namespace swaw::bsp {

    void delay(std::chrono::milliseconds duration) {
        std::this_thread::sleep_for(duration);
    }


} // namespace swaw::bsp