# ========================================
# App Library
# ========================================

# Collect App source files
file(GLOB_RECURSE APP_SRCS
    src/*.c
    src/*.cpp
)

# Create a static library for the App layer
add_library(App STATIC ${APP_SRCS})

# Apply platform compile flags
target_compile_options(App PUBLIC ${PLATFORM_COMPILE_FLAGS})

# Public include directories (App interface headers)
target_include_directories(App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Middleware dependency
# Ensures App has access to Middleware and PlatformInterface
target_link_libraries(App PUBLIC Middleware Common)
