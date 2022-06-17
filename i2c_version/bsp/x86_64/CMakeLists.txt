add_library(bsp src/bsp.cpp src/bsp_led.cpp src/bsp_clock.cpp src/bsp_com.cpp)

target_include_directories(bsp PUBLIC include)


target_link_libraries(
  bsp
  PUBLIC bsp_interface
)
