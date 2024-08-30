cmake_minimum_required(VERSION 3.26)

# ===================================================================================================
# Top-level project.
# ===================================================================================================
project(Nenuphar)

# Enable Nénuphar test.
set(NENUPHAR_TEST_ENABLE ON)

# Use folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Append cmake modules in CMAKE_MODULE_PATH from CMake folder.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# Include cmake module for Nénuphar Module.
include(NPModule)
include(NPBuild)

if(NENUPHAR_TEST_ENABLE)
    include(CTest)
    enable_testing()
endif()

# Configure C++ standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable export compile command.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Bin)

# Project source.
add_compile_definitions(NP_PROJECT_DIR="${CMAKE_SOURCE_DIR}")

# Configure properties.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# ===================================================================================================
# BuildTool.
# ===================================================================================================
add_subdirectory(Source/BuildTool/NPBuild)
add_subdirectory(Source/BuildTool/Generator)
add_subdirectory(Source/BuildTool/Analysis)


# ===================================================================================================
# Engine Modules.
# ===================================================================================================
add_subdirectory(Source/Engine/Common)
add_subdirectory(Source/Engine/Core)
add_subdirectory(Source/Engine/Math)
add_subdirectory(Source/Engine/ApplicationCore)
add_subdirectory(Source/Engine/EventSystem)
add_subdirectory(Source/Engine/InputSystem)
add_subdirectory(Source/Engine/Model)
add_subdirectory(Source/Engine/Rendering)
add_subdirectory(Source/Engine/RenderLight)
add_subdirectory(Source/Engine/Entity)
add_subdirectory(Source/Engine/Asset)


# ===================================================================================================
# Samples.
# ===================================================================================================
add_subdirectory(Source/Samples/Genesis)


# ===================================================================================================
# Third Party.
# ===================================================================================================
add_subdirectory(Source/ThirdParty/fmt)
add_subdirectory(Source/ThirdParty/glad)
add_subdirectory(Source/ThirdParty/stb)
add_subdirectory(Source/ThirdParty/tinyobj)
add_subdirectory(Source/ThirdParty/SDL2)


# If the variable NENUPHAR_TEST_ENABLE is ON, add Catch2.
if(NENUPHAR_TEST_ENABLE)
    add_subdirectory(Source/ThirdParty/Catch2)
endif()
