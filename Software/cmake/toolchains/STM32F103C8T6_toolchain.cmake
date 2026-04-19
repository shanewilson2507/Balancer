# ========================================
# Toolchain file for STM32F103C8T6 (ARM Cortex-M3)
# Usage:
#   cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/STM32F103C8T6_toolchain.cmake ..
# ========================================

# ========================================
# 1. System and processor
# ========================================
set(CMAKE_SYSTEM_NAME Generic)      # Bare-metal system
set(CMAKE_SYSTEM_PROCESSOR arm)     # ARM architecture

# ========================================
# 2. Default build type (align with STM32CubeIDE single-config Debug workflow)
# ========================================
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type: Debug, Release, MinSizeRel, RelWithDebInfo" FORCE)
endif()

# ========================================
# 3. Build defines (DEBUG is per-config; see Platform CMakeLists)
# ========================================
set(BARE_METAL_TARGET TRUE CACHE BOOL "Building for bare-metal MCU")

set(PLATFORM_DEFINES
    STM32F103xB
    USE_HAL_DRIVER
)

# ========================================
# 4. Toolchain prefix
# ========================================
set(TOOLCHAIN_PREFIX arm-none-eabi)


# ========================================
# 5. Compilers
# ========================================
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)

# ========================================
# 6. Compiler flags
# CubeIDE Debug: typically -Og; Release: -Os
# ========================================
set(PLATFORM_C_FLAGS_BASE
    -mcpu=cortex-m3
    -mthumb
    -g3
    -ffunction-sections
    -fdata-sections
    -Wall
    -fstack-usage
    -mfloat-abi=soft
)

set(PLATFORM_C_FLAGS
    ${PLATFORM_C_FLAGS_BASE}
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-Og>
    $<$<CONFIG:Release>:-Os>
    $<$<CONFIG:MinSizeRel>:-Os>
)

set(PLATFORM_CXX_FLAGS
    ${PLATFORM_C_FLAGS_BASE}
    -fno-exceptions
    -fno-rtti
    -fno-use-cxa-atexit
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-Og>
    $<$<CONFIG:Release>:-Os>
    $<$<CONFIG:MinSizeRel>:-Os>
)

set(PLATFORM_ASM_FLAGS
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
)

set(PLATFORM_COMPILE_FLAGS
    $<$<COMPILE_LANGUAGE:C>:${PLATFORM_C_FLAGS}>
    $<$<COMPILE_LANGUAGE:CXX>:${PLATFORM_CXX_FLAGS}>
    $<$<COMPILE_LANGUAGE:ASM>:${PLATFORM_ASM_FLAGS}>
)

# ========================================
# 7. Linker script
# ========================================
set(PLATFORM_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld")

# ========================================
# 8. Link flags
# Omit --specs=nosys.specs: with it, libnosys supplies strong _read/_write and overrides
# the weak CubeMX syscalls.c retargets. nano.specs alone keeps newlib small without that.
# ========================================
set(PLATFORM_LINK_FLAGS
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -T ${PLATFORM_LINKER_SCRIPT}
    -Wl,--gc-sections
    -Wl,-Map=${TARGET_NAME}.map
    -static
    --specs=nano.specs
    -u _printf_float
)

# ========================================
# 9. Prevent CMake from linking/running during try_compile
# ========================================
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ========================================
# 10. Utilities
# ========================================
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy CACHE FILEPATH "Object copy utility")
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size CACHE FILEPATH "Utility to print firmware size")
