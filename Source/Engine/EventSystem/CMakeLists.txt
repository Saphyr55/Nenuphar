# ========================================================
# Setup Core Lib for the engine.
# ========================================================
project(Engine.EventSystem)

set(LOCATION        .)
set(TARGET          Engine.EventSystem)
set(GROUP           Engine)
set(DEPS            Engine.Common
                    Engine.Core
                    Engine.ApplicationCore
    )

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


