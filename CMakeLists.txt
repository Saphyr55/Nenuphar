cmake_minimum_required(VERSION 3.26)

# ========================================================
# Top-level project.
# ========================================================
project(Nenuphar)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
include(Scripts)

# Configure C++ standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Nénuphar test.
set(NENUPHAR_TEST_ENABLE OFF)

# Configure properties.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
    add_compile_definitions(NP_PLATFORM_WINDOWS)
endif()


# ========================================================
# Engine Modules.
# ========================================================
add_subdirectory(Source/Engine/Common)
add_subdirectory(Source/Engine/Core)
add_subdirectory(Source/Engine/Math)
add_subdirectory(Source/Engine/ApplicationCore)
add_subdirectory(Source/Engine/EventSystem)
add_subdirectory(Source/Engine/InputSystem)


# ========================================================
# Samples.
# ========================================================
add_subdirectory(Source/Sample/Genesis)


# ========================================================
# Third Party.
# ========================================================
add_subdirectory(Source/ThirdParty/fmt)
add_subdirectory(Source/ThirdParty/glad)

if(NENUPHAR_TEST_ENABLE)
    add_subdirectory(Source/ThirdParty/Catch2)
endif()