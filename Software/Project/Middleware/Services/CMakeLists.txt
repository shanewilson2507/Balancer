# ========================================
# Services Library
# ========================================

#Setting relevant directories
set(DELAY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Delay)
set(TIMER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Timer)

#Creating static Services Library
add_library(Services STATIC)

#Adding sources to Services Library
file(GLOB DELAY_SRCS 
    ${DELAY_DIR}/src/*.c
    ${DELAY_DIR}/src/*.cpp
)

file(GLOB TIMER_SRCS
    ${TIMER_DIR}/src/*.c
    ${TIMER_DIR}/src/*.cpp
)

target_sources(Services PRIVATE
    ${DELAY_SRCS}
    ${TIMER_SRCS}
)

#Adding include directories
target_include_directories(Services PUBLIC
    ${DELAY_DIR}/inc
    ${TIMER_DIR}/inc
)

# Apply platform compile flags
target_compile_options(Services PUBLIC ${PLATFORM_COMPILE_FLAGS})

#link privately to Platform and Common
target_link_libraries(Services PUBLIC 
    PlatformInterface
    Common
)