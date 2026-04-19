# ========================================
# Host toolchain for building tests and host binaries
# Usage:
#   cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/host.cmake ..
# ========================================

# ========================================
# 1. System and processor
# ========================================
set(CMAKE_SYSTEM_NAME Generic)      # Host system
set(CMAKE_SYSTEM_PROCESSOR Generic)

# ========================================
# 2. Build defines
# ========================================
set(BARE_METAL_TARGET FALSE CACHE BOOL "Building for host (not bare-metal)")

# ========================================
# 3. Compilers
# ========================================
# Use host compilers (defaults if not explicitly set)
if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER gcc CACHE STRING "C compiler for host")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER g++ CACHE STRING "C++ compiler for host")
endif()

# ========================================
# 4. Compiler flags
# ========================================
set(PLATFORM_C_FLAGS
    -O0
    -g
    -Wall
    -Wextra
)

set(PLATFORM_CXX_FLAGS
    -O0
    -g
    -Wall
    -Wextra
)

set(PLATFORM_COMPILE_FLAGS
    $<$<COMPILE_LANGUAGE:C>:${PLATFORM_C_FLAGS}>
    $<$<COMPILE_LANGUAGE:CXX>:${PLATFORM_CXX_FLAGS}>
)

# ========================================
# 5. Linker flags
# ========================================
set(PLATFORM_LINK_FLAGS
    -static
)

# ========================================
# 6. Utilities
# ========================================
# On host, standard objcopy/size are optional; can leave unset
set(CMAKE_OBJCOPY objcopy CACHE FILEPATH "Object copy utility (host)")
set(CMAKE_SIZE size CACHE FILEPATH "Utility to print binary size (host)")

# ========================================
# 7. Prevent CMake from linking/running during try_compile
# ========================================
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
