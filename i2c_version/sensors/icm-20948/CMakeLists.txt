add_library(icm-20948 src/icm-20948.cpp)

target_include_directories(icm-20948 PUBLIC include)

include(FetchContent)

FetchContent_Declare(
  icm20948_driver
  GIT_REPOSITORY https://github.com/stephendpmurphy/icm20948.git
  GIT_TAG v1.0.0)

FetchContent_MakeAvailable(icm20948_driver)

target_include_directories(_icm20948 PUBLIC ${icm20948_driver_SOURCE_DIR}/inc)



target_link_libraries(icm-20948
PUBLIC sensor_interface
PRIVATE _icm20948
PRIVATE bsp)