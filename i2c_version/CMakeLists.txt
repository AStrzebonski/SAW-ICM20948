cmake_minimum_required(VERSION 3.19)

# Notce that including "toolchain.cmake" file is ommited - now the cmake doesn't know, which compiler to use.
# To correct for that, you should pass toolchain file as a command line argument for cmake : -DCMAKE_TOOLCHAIN_FILE:STRING=<path_to_your_toolchain_file>
# Alternatively, you can inform your IDE, which toolchain file to pass - in VSCode it is done, using cmake-kits.json file

project(swaw_lab4 CXX C ASM)

# Hence we are using C++20 features, we need to set appropriate compiler options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(bsp/bsp_interface) # Add library that provides bsp common interface
add_subdirectory(sensors/sensor_interface) # Add library that provides bsp common interface
add_subdirectory(sensors/icm-20948) # Add library that provides bsp common interface
add_subdirectory(slutcom) # Add library that provides packet communication interface

if(CMAKE_SYSTEM_PROCESSOR STREQUAL arm)
    message("Building application for NUCLEO-F767ZI")
    add_subdirectory(bsp/slut-f767zi) # Add implementation of bsp library for slut-f767zi
    set(CMAKE_EXECUTABLE_SUFFIX .elf) # Select executable extension for NUCLEO target

else()
    message("Building application for PC")
    add_subdirectory(bsp/x86_64) # Add implementation of bsp library for PC
    set(CMAKE_EXECUTABLE_SUFFIX .exe) # Select executable extension for x86_64 target

endif()



add_executable(swaw_lab4_act3 main.cpp )
target_link_libraries(swaw_lab4_act3 bsp icm-20948 slutcom)