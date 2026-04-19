#!/usr/bin/env bash
set -e

TARGET_PLATFORM=STM32F103C8T6
TARGET_NAME=Balancer
BUILD_DIR=build
TOOLCHAIN_DIR="cmake/toolchains"
ENABLE_TESTING="OFF"

# -----------------------
# Argument validation
# -----------------------
if [ -n "$1" ] && [ "$1" != "clean" ] && [ "$1" != "flash" ] && [ "$1" != "test" ]; then
    echo "Error: Unknown argument '$1'. Valid options are 'clean', 'flash', 'test' or no argument."
    exit 1
fi

# -----------------------
# Configure for testing
# -----------------------
if [ "$1" == "test" ]; then
    TARGET_PLATFORM=Host
    ENABLE_TESTING="ON"
    TARGET_NAME="${TARGET_NAME}_tests"
fi

# -----------------------
# Set platform-specific build directory
# -----------------------
PLATFORM_BUILD_DIR="${BUILD_DIR}/build_${TARGET_NAME}_${TARGET_PLATFORM}"

# -----------------------
# Clean build directory
# -----------------------
if [ "$1" == "clean" ]; then
    rm -rf "${BUILD_DIR}"
    echo "Cleaned build directory."
    exit 0
fi

# -----------------------
# Flash existing binary
# -----------------------
if [ "$1" == "flash" ]; then
	BINARY_FILE=${PLATFORM_BUILD_DIR}/${TARGET_NAME}.bin
    if [ ! -f "${BINARY_FILE}" ]; then
        echo "No built binary found at ${BINARY_FILE}. Build first."
        exit 1
    fi

    if ! command -v openocd &>/dev/null; then
        echo "Error: openocd not found in PATH"
        exit 1
    fi

    openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
        -c "program ${BINARY_FILE} 0x08000000 reset exit"

    exit 0
fi


echo "Building '${TARGET_NAME}' for platform '${TARGET_PLATFORM}' (ENABLE_TESTING=${ENABLE_TESTING}) in '${PLATFORM_BUILD_DIR}'" 

# -----------------------
# Default: configure & build
# -----------------------
cmake -B "${PLATFORM_BUILD_DIR}" -S . \
    -DTARGET_NAME="${TARGET_NAME}" \
    -DTARGET_PLATFORM="${TARGET_PLATFORM}" \
    -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_DIR}/${TARGET_PLATFORM}_toolchain.cmake" \
    -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Debug}" \
    -DENABLE_TESTING="${ENABLE_TESTING}"

cmake --build "${PLATFORM_BUILD_DIR}"

# -----------------------
# Run tests if requested
# -----------------------
if [ "$1" == "test" ]; then
    ctest --test-dir "${PLATFORM_BUILD_DIR}" --output-on-failure
fi
