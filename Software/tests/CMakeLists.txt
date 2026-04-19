# ========================================
# tests/CMakeLists.txt
# GoogleTest integration for host unit tests
# ========================================

# ----------------------------------------
# Fetch GoogleTest
# ----------------------------------------
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)

# Make GTest targets available
FetchContent_MakeAvailable(googletest)

# ----------------------------------------
# Collect test sources
# ----------------------------------------
file(GLOB_RECURSE TEST_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# ----------------------------------------
# Create test executable
# ----------------------------------------
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE ${TEST_SOURCES})

# Include directories for production libraries
target_include_directories(${TARGET_NAME} PRIVATE
    ${PROJECT_DIR}/App/inc
    ${PROJECT_DIR}/Middleware/inc
)

# Apply host compile flags to test code
target_compile_options(${TARGET_NAME} PRIVATE ${PLATFORM_COMPILE_FLAGS})

# ----------------------------------------
# Link test executable
# ----------------------------------------
target_link_libraries(${TARGET_NAME}
    PRIVATE
        GTest::gtest_main
        App
        Middleware
)

# ----------------------------------------
# Integrate with CTest
# ----------------------------------------
include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
