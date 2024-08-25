# ========================================================
# Setup Genesis Module.
# ========================================================
project(Genesis)

set(LOCATION    .)
set(TARGET      Genesis)
set(GROUP       Sample)
set(DEPS        
                Engine.Core 
                Engine.Common
                Engine.Math
                Engine.Entity
                Engine.ApplicationCore
                Engine.EventSystem
                Engine.InputSystem
                Engine.Rendering
                Engine.Model
                glad
    )

add_executable(${TARGET})
add_module(${TARGET} ${LOCATION})

add_dependencies(${TARGET} NPBuildGen)

target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR})
target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


