
// Nasty (but functional) way of suppresing C libraries warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wvolatile"
#pragma GCC diagnostic ignored "-Wconversion"
extern "C" {
    #include "main.h"
}
#pragma GCC diagnostic pop


extern "C" void SystemClock_Config(void);
namespace swaw::bsp {


    void init() {
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_I2C1_Init();
        MX_USART3_UART_Init();
    }


} // namespace swaw::bsp
