if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# target_link_libraries(application hardware_watchdog pico_stdlib)

# latest:
# target_link_libraries(application pico_runtime flash pico_stdlib)

include_directories(../include)
add_library(application application.c)
target_link_libraries(application pico_runtime hardware_flash pico_stdlib)
