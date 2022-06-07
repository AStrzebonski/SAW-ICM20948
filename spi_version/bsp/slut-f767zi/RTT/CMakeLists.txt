# Tworzymy bibliotekę segger_rtt_obj - składa się ona z 3 plików źródłowych, znajdujących się w katalogu src (patrząc od naszego głównego katalogu jest to bsp/slut-f767zi/RTT/src)
add_library(segger_rtt_obj OBJECT src/SEGGER_RTT_printf.c src/SEGGER_RTT.c
                                  src/SEGGER_RTT_Syscalls_GCC.c)

# Dodajemy do biblioteki segger_rtt_obj publiczny folder nagłówków - include (patrząc od naszego głównego katalogu jest to bsp/slut-f767zi/RTT/include)
target_include_directories(segger_rtt_obj PUBLIC include)
# W folderze include powinny się znaleźć pliki SEGGER_RTT_Conf.h i SEGGER_RTT.h

# Tworzymy bibliotekę segger_rtt. Podobnie jak w przypadku CubeMX, ta biblioteka dodaje zaleźność do publicznych nagłówków biblioteki segger_rtt_obj, a także obiektów, z których ta biblioteka się składa
add_library(segger_rtt INTERFACE)
target_link_libraries(segger_rtt INTERFACE segger_rtt_obj
                                           $<TARGET_OBJECTS:segger_rtt_obj>)

