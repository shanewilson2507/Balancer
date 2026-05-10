# ========================================
# Devices Library
# ========================================

#Setting relevant directories
set(IMU_DIR ${CMAKE_CURRENT_SOURCE_DIR}/IMU)
set(LED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/LED)
set(MOTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Motor)

#Creating static Devices Library
add_library(Devices STATIC)

#Adding sources to Devices Library
file(GLOB IMU_SRCS 
    ${IMU_DIR}/src/*.c
    ${IMU_DIR}/src/*.cpp
)

file(GLOB LED_SRCS
    ${LED_DIR}/src/*.c
    ${LED_DIR}/src/*.cpp
)

file(GLOB MOTOR_SRCS
    ${MOTOR_DIR}/src/*.c
    ${MOTOR_DIR}/src/*.cpp
)

target_sources(Devices PRIVATE
    ${IMU_SRCS}
    ${LED_SRCS}
    ${MOTOR_SRCS}
)

#Adding include directories
target_include_directories(Devices PUBLIC
    ${IMU_DIR}/inc
    ${LED_DIR}/inc
    ${MOTOR_DIR}/inc
)

# Apply platform compile flags
target_compile_options(Devices PUBLIC ${PLATFORM_COMPILE_FLAGS})

#link relevant libraries
target_link_libraries(Devices PUBLIC
    PlatformInterface
    Peripherals
)

target_link_libraries(Devices PRIVATE 
    Services #Motor.cpp uses Delay.hpp
)