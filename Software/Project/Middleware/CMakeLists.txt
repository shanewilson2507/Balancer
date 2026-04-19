# ========================================
# Middleware Library
# ========================================

# Collect Middleware source files
file(GLOB_RECURSE MIDDLEWARE_SRCS
    src/*.c
    src/*.cpp
)

# Create a static library for Middleware
add_library(Middleware STATIC ${MIDDLEWARE_SRCS})

# Apply platform compile flags
target_compile_options(Middleware PUBLIC ${PLATFORM_COMPILE_FLAGS})

# Public include directories (Middleware interface headers)
target_include_directories(Middleware PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Dependencies
#target_link_libraries(Middleware PUBLIC PlatformInterface)

# Middleware depends on the platform library
target_link_libraries(Middleware PUBLIC Platform Common Peripherals)
