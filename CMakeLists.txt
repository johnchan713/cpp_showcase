cmake_minimum_required(VERSION 3.25)

project(cpp26_showcase VERSION 1.0 LANGUAGES CXX)

# Set C++ standard to C++23 (targeting C++26 when available)
# Note: C++26 is not yet finalized, using C++23 features that will be in C++26
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Using C++ Standard: C++${CMAKE_CXX_STANDARD}")

# Enable threading support
find_package(Threads REQUIRED)

# Define the executable
add_executable(cpp26_showcase
    main.cpp
)

# Include directories (current directory for headers)
target_include_directories(cpp26_showcase PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link threading library
target_link_libraries(cpp26_showcase PRIVATE Threads::Threads)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cpp26_showcase PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
        -Wno-unused-variable
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(cpp26_showcase PRIVATE
        /W4
        /permissive-
    )
endif()

# Optional: Enable optimization for Release builds
if(CMAKE_BUILD_TYPE MATCHES Release)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(cpp26_showcase PRIVATE -O3)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(cpp26_showcase PRIVATE /O2)
    endif()
endif()

# Print build information
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# Installation rules (optional)
install(TARGETS cpp26_showcase
    RUNTIME DESTINATION bin
)

# Display header files (for IDE support)
file(GLOB HEADER_FILES "*.hpp")
target_sources(cpp26_showcase PRIVATE ${HEADER_FILES})
