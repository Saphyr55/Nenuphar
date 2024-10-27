# ========================================================
# Setup Editor Executable.
# ========================================================
project(Editor)

set(LOCATION    .)
set(TARGET      Editor)
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
                Engine.RenderLight
                Engine.Model
                Engine.Asset
                Editor.Core
                Editor.Application)

add_executable(${TARGET})
add_module(${TARGET} ${LOCATION})

target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR})
target_link_libraries(${TARGET} PRIVATE ${DEPS} ${MODULES})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


