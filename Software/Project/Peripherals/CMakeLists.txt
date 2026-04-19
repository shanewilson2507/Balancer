# ========================================
# Peripherals Library
# ========================================

# Collect Peripherals source files
file(GLOB_RECURSE PERIPHERALS_SRCS CMAKE_CONFIGURE_DEPENDS
    */src/*.c
    */src/*.cpp
)

# Create a static library for Peripherals
add_library(Peripherals STATIC ${PERIPHERALS_SRCS})

# Apply platform compile flags
target_compile_options(Peripherals PUBLIC ${PLATFORM_COMPILE_FLAGS})

# Collect include directories
file(GLOB PERIPHERALS_INC_DIRS CMAKE_CONFIGURE_DEPENDS
    */inc
)

# Public include directories
target_include_directories(Peripherals PUBLIC ${PERIPHERALS_INC_DIRS})

# Peripherals depends on the platform library
target_link_libraries(Peripherals PUBLIC PlatformInterface Common)
