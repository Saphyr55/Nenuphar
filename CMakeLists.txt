cmake_minimum_required(VERSION 3.26)

# ===================================================================================================
# Top-level project.
# ===================================================================================================
project(Nenuphar)

# Use folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Append cmake modules in CMAKE_MODULE_PATH from CMake folder.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# Include cmake module for Nénuphar Module.
include(NpAddModule)

# Configure C++ standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Nénuphar test.
option(NENUPHAR_TEST_ENABLE "Enable Nénuphar Test." OFF)

# Enable export compile command.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Bin)

# Configure properties.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
    add_compile_definitions(NP_PLATFORM_WINDOWS)
endif()

# ===================================================================================================
# BuildTool.
# ===================================================================================================
add_subdirectory(Source/BuildTool/NPBuild)
add_subdirectory(Source/BuildTool/Generator)
add_subdirectory(Source/BuildTool/Analysis)

add_subdirectory(Assets)

# ===================================================================================================
# Engine Modules.
# ===================================================================================================
add_subdirectory(Source/Engine/Common)
add_subdirectory(Source/Engine/Core)
add_subdirectory(Source/Engine/Math)
add_subdirectory(Source/Engine/ApplicationCore)
add_subdirectory(Source/Engine/EventSystem)
add_subdirectory(Source/Engine/InputSystem)
add_subdirectory(Source/Engine/Rendering)


# ===================================================================================================
# Samples.
# ===================================================================================================
add_subdirectory(Source/Sample/Genesis)


# ===================================================================================================
# Third Party.
# ===================================================================================================
add_subdirectory(Source/ThirdParty/fmt)
add_subdirectory(Source/ThirdParty/glad)

if(NENUPHAR_TEST_ENABLE)
    add_subdirectory(Source/ThirdParty/Catch2)
endif()