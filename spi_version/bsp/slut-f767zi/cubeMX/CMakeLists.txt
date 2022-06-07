# Tworzymy bibliotekę - interfejs: nie buduje ona nic, ale załącza "publiczny
# interfejs biblioteki stm32_hal_obj", a także wymusza linkowanie ze wszystkimi
# plikami obiektowymi biblioteki stm32_hal_obj (zamiast tworzyć pojedynczą
# bibliotekę statyczną) Dzięki temu, podczas tworzenia biblioteki, nie zostaną
# usunięte "pozornie" nieużywane symbole.
add_library(stm32_hal INTERFACE)
target_link_libraries(stm32_hal INTERFACE stm32_hal_obj
                                          $<TARGET_OBJECTS:stm32_hal_obj>)

add_library(
  stm32_hal_obj OBJECT
  Core/Src/main.c
  Core/Src/stm32f7xx_it.c
  Core/Src/stm32f7xx_hal_msp.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c
  #Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ramfunc.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c
  Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c
  Core/Src/system_stm32f7xx.c
  startup_stm32f767xx.s)

# Dodajemy foldery nagłówków, tak jak w CubeMX Makefile
target_include_directories(
  stm32_hal_obj
  PUBLIC Core/Inc Drivers/STM32F7xx_HAL_Driver/Inc
         Drivers/STM32F7xx_HAL_Driver/Inc/Legacy
         Drivers/CMSIS/Device/ST/STM32F7xx/Include Drivers/CMSIS/Include)

# Dodajemy definicje, tak jak w CubeMX Makefile
target_compile_definitions(stm32_hal_obj PUBLIC USE_HAL_DRIVER STM32F767xx)
