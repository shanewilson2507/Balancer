# ========================================
# STM32F103C8T6 Platform Library
# Builds HAL + CMSIS + custom wrapper code
# Exports core files, startup, linker info, and sets compiler/linker flags
# ========================================

# Core and driver directories
set(CORE_DIR    ${CMAKE_SOURCE_DIR}/Core)
set(DRIVERS_DIR ${CMAKE_SOURCE_DIR}/Drivers)
set(MIDDLEWARES_DIR ${CMAKE_SOURCE_DIR}/Middlewares)
set(USB_DEVICE_DIR ${CMAKE_SOURCE_DIR}/USB_DEVICE)

# Platform interface directory
set(PLATFORM_DIR ${CMAKE_SOURCE_DIR}/Project/Platform)

# ========================================
# CubeMX / HAL sources
# ========================================
file(GLOB_RECURSE CMSIS_SRCS
    "${DRIVERS_DIR}/CMSIS/Device/ST/STM32F1xx/Source/*.c"
)

file(GLOB_RECURSE HAL_SRCS
    "${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Src/*.c"
)

file(GLOB_RECURSE MIDDLEWARES_SRCS
	"${MIDDLEWARES_DIR}/ST/STM32_USB_Device_Library/Class/CDC/Src/*.c"
	"${MIDDLEWARES_DIR}/ST/STM32_USB_Device_Library/Core/Src/*.c"
)

file(GLOB_RECURSE USB_DEVICE_SRCS
	"${USB_DEVICE_DIR}/App/*.c"
	"${USB_DEVICE_DIR}/Target/*.c"
)

# ========================================
# Core sources (including main.c)
# ========================================
file(GLOB_RECURSE CORE_SRCS 
    "${CORE_DIR}/Src/*.c"
)

# ========================================
# Custom platform sources
# ========================================
file(GLOB_RECURSE CUSTOM_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# ========================================
# Create Platform library
# ========================================
add_library(Platform STATIC
    ${CMSIS_SRCS}
    ${HAL_SRCS}
    ${CUSTOM_SRCS}
    ${MIDDLEWARES_SRCS}
    ${USB_DEVICE_SRCS}
)

# Compile definitions (DEBUG only for Debug / RelWithDebInfo, like STM32CubeIDE)
target_compile_definitions(Platform PUBLIC
    ${PLATFORM_DEFINES}
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:DEBUG>
)

# Platform-specific compiler flags
target_compile_options(Platform PUBLIC ${PLATFORM_COMPILE_FLAGS})

# ========================================
# Include directories
# ========================================
target_include_directories(Platform PUBLIC
    # STM32-specific wrapper headers
    ${CMAKE_CURRENT_SOURCE_DIR}/inc

    # CubeMX HAL + CMSIS
    ${DRIVERS_DIR}/CMSIS/Include
    ${DRIVERS_DIR}/CMSIS/Device/ST/STM32F1xx/Include
    ${DRIVERS_DIR}/STM32F1xx_HAL_Driver/Inc
    ${MIDDLEWARES_DIR}/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ${MIDDLEWARES_DIR}/ST/STM32_USB_Device_Library/Core/Inc
    ${USB_DEVICE_DIR}/App
    ${USB_DEVICE_DIR}/Target
    
    # Platform interface headers
    ${PLATFORM_DIR}/inc

    # Core headers
    ${CORE_DIR}/Inc
)

target_link_libraries(Platform PUBLIC Common)

# ========================================
# Export core sources and startup file
# ========================================
set(STARTUP_FILE "${CORE_DIR}/Startup/startup_stm32f103c8tx.s")

# Propagate PLATFORM_SRCS up to parent scope
set(PLATFORM_SRCS
    ${STARTUP_FILE}
    ${CORE_SRCS}
    PARENT_SCOPE
)