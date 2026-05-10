# ========================================
# Middleware Interface Library
# ========================================

# Create a interface library for Middleware
add_library(Middleware INTERFACE)

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Communication)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Control)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Services)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Devices)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Observers)

# Apply platform compile flags
target_compile_options(Middleware INTERFACE ${PLATFORM_COMPILE_FLAGS})

#link libraries
target_link_libraries(Middleware INTERFACE Communication Control Devices Math Observers Services)
