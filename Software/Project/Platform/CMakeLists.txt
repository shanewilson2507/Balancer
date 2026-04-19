# ========================================
# Platform Interface (Platform-agnostic APIs)
# ========================================

# Path to platform-agnostic include directory
set(PLATFORM_INTERFACE_INC_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

# Interface library exposing common cross-platform headers
add_library(PlatformInterface INTERFACE)

target_include_directories(PlatformInterface INTERFACE
    ${PLATFORM_INTERFACE_INC_DIR}
)

# ========================================
# Platform Selection + Validation
# ========================================

# TARGET_PLATFORM must be specified by the top-level build
if(NOT DEFINED TARGET_PLATFORM)
    message(FATAL_ERROR
        "TARGET_PLATFORM is not defined. "
        "You must specify -DTARGET_PLATFORM=<name> when running CMake."
    )
endif()

# Construct path to selected platform directory
set(PLATFORM_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PLATFORM}"
)

# Ensure the platform folder exists and contains its own CMakeLists.txt
if(NOT EXISTS "${PLATFORM_DIR}/CMakeLists.txt")
    message(FATAL_ERROR
        "Platform '${TARGET_PLATFORM}' does not exist under: "
        "${CMAKE_CURRENT_SOURCE_DIR}\n"
        "Missing folder or CMakeLists.txt!"
    )
endif()

# ========================================
# Add the selected platform backend
# (Exports PLATFORM_SRCS)
# ========================================

add_subdirectory(${PLATFORM_DIR})

# Propagate platform source list upward to parent
set(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
