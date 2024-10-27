# ========================================================
# Setup Editor Application Module.
# ========================================================
project(Editor.Application)

set(LOCATION    .)
set(TARGET      Editor.Application)
set(GROUP       Engine)
set(DEPS        Engine.Core 
                Engine.Common
                Engine.EventSystem
                Engine.InputSystem
                Editor.Core)

add_library_module(${TARGET} SHARED ${LOCATION})

target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


