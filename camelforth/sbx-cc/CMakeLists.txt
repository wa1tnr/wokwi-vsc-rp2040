# add_compile_options(-DNOT_WOKWI -v -Werror -Wall -Wextra -Wnull-dereference -fmax-errors=8)
# sbx-cc.c
# add_compile_options(-DNOT_WOKWI -v -Wall -Wextra -Wnull-dereference -fmax-errors=8)
add_compile_options(-DNOT_WOKWI    -Wall -Wextra -Wnull-dereference -fmax-errors=8)
add_executable(sbx-cc
        sbx-cc.c
        )

# Sat Feb 27 23:45:07 UTC 2021

target_compile_definitions(sbx-cc PRIVATE
    # enable this flag only for no_flash compile:
    # NO_FLASH_CMAKE=-1
    # NO_FLASH_CMAKE=-1
)

target_link_libraries(sbx-cc PRIVATE application pico-LED asmword ws2812 hardware_flash pico_stdlib)

# pico_set_binary_type(sbx-cc copy_to_ram)
# pico_set_binary_type(sbx-cc no_flash)
pico_set_binary_type(sbx-cc copy_to_ram)
# pico_set_binary_type(sbx-cc no_flash)

pico_enable_stdio_usb(sbx-cc 1)
pico_enable_stdio_uart(sbx-cc 1) # was zero

pico_add_extra_outputs(sbx-cc)

example_auto_set_url(sbx-cc)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(application)
add_subdirectory(pico-hw)
add_subdirectory(pio)
add_subdirectory(asm)
