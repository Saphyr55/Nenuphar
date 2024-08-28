# ========================================================
# Setup Engine Application Core Module for the engine.
# ========================================================
project(Engine.ApplicationCore)

set(LOCATION    .)
set(TARGET      Engine.ApplicationCore)
set(GROUP       Engine)
set(DEPS        Engine.Core 
                Engine.Common
                Engine.EventSystem
                Engine.InputSystem
)

add_library_module(${TARGET} STATIC ${LOCATION})

target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


