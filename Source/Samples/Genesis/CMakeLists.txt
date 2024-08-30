# ========================================================
# Setup Genesis Module.
# ========================================================
project(Genesis)

set(LOCATION    .)
set(TARGET      Genesis)
set(GROUP       Sample)
set(DEPS        glad)
set(MODULES     Engine.Core
                Engine.Common
                Engine.Math
                Engine.Entity
                Engine.ApplicationCore
                Engine.EventSystem
                Engine.InputSystem
                Engine.Rendering
                Engine.Model
                Engine.Asset)

add_executable(${TARGET})
add_module(${TARGET} ${LOCATION})

target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR})
target_link_libraries(${TARGET} PRIVATE ${DEPS} ${MODULES})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


