# This is the main binary. List your C files here.
add_executable(timing
    task_delay.c
    )

pico_set_program_name(timing "test")
pico_set_program_version(timing "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(timing 1)
pico_enable_stdio_usb(timing 0)

# Add the libraries to the build
target_link_libraries(timing PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(timing PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(timing)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash ${PICOTOOL} load -f $<TARGET_FILE:timing> DEPENDS timing)
add_custom_target(openocd_flash ${OPENOCD} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c 'program "$<TARGET_FILE:timing>" verify reset exit' DEPENDS timing)
