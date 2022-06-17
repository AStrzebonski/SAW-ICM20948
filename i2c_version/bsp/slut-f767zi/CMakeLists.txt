add_library(bsp src/bsp.cpp src/bsp_led.cpp src/bsp_clock.cpp src/bsp_com.cpp)

add_subdirectory(cubeMX)
add_subdirectory(RTT)

target_include_directories(bsp PUBLIC include)

target_include_directories(
  bsp
  PUBLIC Core/Inc Drivers/STM32F7xx_HAL_Driver/Inc
         Drivers/STM32F7xx_HAL_Driver/Inc/Legacy
         Drivers/CMSIS/Device/ST/STM32F7xx/Include Drivers/CMSIS/Include)

target_link_libraries(
  bsp
  PUBLIC bsp_interface
  PUBLIC segger_rtt
  PUBLIC stm32_hal
  INTERFACE stm32_hal)
