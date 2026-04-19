# ========================================
# Common Library
# ========================================


# Create a INTERFACE library for Common for reuse by any Layer
add_library(Common INTERFACE)

# Public include directories (Common interface headers)
target_include_directories(Common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)