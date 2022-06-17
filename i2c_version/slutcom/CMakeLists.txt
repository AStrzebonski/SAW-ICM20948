add_library(slutcom src/slutcom_packet.cpp)

target_include_directories(slutcom PUBLIC include)


target_link_libraries(slutcom PRIVATE bsp)