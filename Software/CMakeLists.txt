# ========================================
# Top-level CMakeLists.txt for Balancer
# ========================================

cmake_minimum_required(VERSION 3.15)
project(Balancer C CXX ASM)

# Export compile commands for IDEs and tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========================================
# Required configuration variables
# ========================================
# TARGET_PLATFORM, TARGET_NAME, and ENABLE_TESTING must be defined when invoking CMake

if(NOT DEFINED TARGET_PLATFORM)
    message(FATAL_ERROR
        "TARGET_PLATFORM is not defined.\n"
        "Invoke CMake with: -DTARGET_PLATFORM=<PlatformName>"
    )
endif()

if(NOT DEFINED TARGET_NAME)
    message(FATAL_ERROR
        "TARGET_NAME is not defined.\n"
        "Invoke CMake with: -DTARGET_NAME=<Name>"
    )
endif()

# Provide a safe default for ENABLE_TESTING
if(NOT DEFINED ENABLE_TESTING)
    set(ENABLE_TESTING OFF)
endif()

# ========================================
# Project directories
# ========================================
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/Project)

# ========================================
# Add subdirectories (libraries)
# ========================================
# Each subdirectory defines its own library and exports sources
add_subdirectory(${PROJECT_DIR}/Common)
add_subdirectory(${PROJECT_DIR}/Platform)    # Exports PLATFORM_SRCS (core + startup)
add_subdirectory(${PROJECT_DIR}/Peripherals)
add_subdirectory(${PROJECT_DIR}/Middleware)
add_subdirectory(${PROJECT_DIR}/App)

# ========================================
# Firmware executable (embedded target)
# ========================================
if(NOT ENABLE_TESTING)

    add_executable(${TARGET_NAME}.elf
        ${PLATFORM_SRCS}   # Core sources + startup
    )

    # Apply compile & linker flags
    target_compile_options(${TARGET_NAME}.elf PUBLIC ${PLATFORM_COMPILE_FLAGS})
    target_link_options(${TARGET_NAME}.elf PRIVATE ${PLATFORM_LINK_FLAGS})

    # Wrap static libs so the linker rescans archives (closer to CubeIDE/GCC makefile behavior)
    target_link_libraries(${TARGET_NAME}.elf PRIVATE
        -Wl,--start-group
        Common
        App
        Peripherals
        Middleware
        Platform
        -Wl,--end-group
    )

    # Post-build: generate binaries and show size
    if(BARE_METAL_TARGET)
        add_custom_command(TARGET ${TARGET_NAME}.elf POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET_NAME}.elf> ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.bin
            COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${TARGET_NAME}.elf> ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.hex
            COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET_NAME}.elf>
            COMMENT "Generating platform binaries and showing size"
        )
    endif()

endif()

# ========================================
# Testing
# ========================================
if(ENABLE_TESTING)
    set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

    enable_testing()
    add_subdirectory(${TEST_DIR})
endif()
