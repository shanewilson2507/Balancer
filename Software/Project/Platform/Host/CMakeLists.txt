# ========================================
# Host Platform (no implementation)
# ========================================

# Create an INTERFACE library for host builds
add_library(Platform INTERFACE)

# No platform-specific source files for host
set(PLATFORM_SRCS "" PARENT_SCOPE)
