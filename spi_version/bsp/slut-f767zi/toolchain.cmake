set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)


set(CPU_COMPILE_FLAGS "-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffunction-sections -fdata-sections  -Wl,-T${CMAKE_CURRENT_LIST_DIR}/cubeMX/STM32F767ZITx_FLASH.ld -specs=nosys.specs")

set(CMAKE_ASM_COMPILER "arm-none-eabi-g++" CACHE STRING "Assembler binary" FORCE)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc" CACHE STRING "C Compiler binary" FORCE)
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++" CACHE STRING "C++ Compiler binary" FORCE)
set(CMAKE_LINKER "arm-none-eabi-g++" CACHE STRING "Linker binary" FORCE)
set(CMAKE_RANLIB "arm-none-eabi-gcc-ranlib" CACHE STRING "Ranlib binary" FORCE)
set(CMAKE_AR "arm-none-eabi-gcc-ar" CACHE STRING "Archiver binary" FORCE)
set(CMAKE_NM "arm-none-eabi-gcc-nm" CACHE STRING "NM binary" FORCE)

set(CMAKE_C_FLAGS ${CPU_COMPILE_FLAGS} CACHE STRING "CFLAGS" FORCE)
set(CMAKE_CXX_FLAGS ${CPU_COMPILE_FLAGS} CACHE STRING "CXXFLAGS" FORCE)
set(CMAKE_ASM_FLAGS ${CPU_COMPILE_FLAGS} CACHE STRING "ASMFLAGS" FORCE)

