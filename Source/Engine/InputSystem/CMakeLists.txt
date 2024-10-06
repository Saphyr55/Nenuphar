# ========================================================
# Setup Input System Module.
# ========================================================
project(Engine.InputSystem)

set(LOCATION        .)
set(TARGET          Engine.InputSystem)
set(GROUP           Engine)
set(DEPS            Engine.Common
                    Engine.Core
                    Engine.EventSystem
    )

add_library_module(${TARGET} STATIC ${LOCATION})

target_link_libraries(${TARGET} PRIVATE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


