# ========================================================
# Setup Graphics Module.
# ========================================================
project(Engine.Graphics)

set(LOCATION        .)
set(TARGET          Engine.Graphics)
set(GROUP           Engine)
set(DEPS            Engine.Rendering
                    Engine.Common                    
                    Engine.Core
                    Engine.Math
                    )

add_library_module(${TARGET} STATIC ${LOCATION})

target_link_libraries(${TARGET} PRIVATE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})

