# ========================================
# Communication Library
# ========================================

#Setting relevant directories
set(TRANSMITTER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Transmitter)
set(TRANSMITTER_SRC_DIR ${TRANSMITTER_DIR}/src)
set(TRANSMITTER_INC_DIR ${TRANSMITTER_DIR}/inc)

#Creating static Communication Library
add_library(Communication STATIC)

#Adding sources to Communication Library
file(GLOB COMMUNICATION_SRCS 
    ${TRANSMITTER_SRC_DIR}/*.c
    ${TRANSMITTER_SRC_DIR}/*.cpp
)

target_sources(Communication PRIVATE
    ${COMMUNICATION_SRCS}
)

#Adding include directories
target_include_directories(Communication PUBLIC
    ${TRANSMITTER_INC_DIR}
)

# Apply platform compile flags
target_compile_options(Communication PUBLIC ${PLATFORM_COMPILE_FLAGS})

#link privately to Platform
target_link_libraries(Communication PUBLIC
    PlatformInterface
)