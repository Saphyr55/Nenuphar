# ========================================================
# Setup Core Lib for the engine.
# ========================================================
project(Engine.Core)

set(LOCATION        .)
set(TARGET          Engine.Core)
set(GROUP           Engine)
set(DEPS            fmt::fmt Engine.Common Engine.ApplicationCore)

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


