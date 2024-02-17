project(Noname)

set(LOCATION    .)
set(TARGET      Noname)
set(GROUP       Sample)
set(DEPS        
                Engine.Core 
                Engine.Common
                Engine.Math
                Engine.ApplicationCore
                Engine.EventSystem
                Engine.InputSystem
                glad
    )


add_executable_module(${TARGET} ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


