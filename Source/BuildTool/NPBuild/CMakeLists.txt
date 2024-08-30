project(NPBuild)

set(LOCATION    .)
set(TARGET      NPBuild)
set(GROUP       BuildTool)
set(DEPS        fmt::fmt
                Engine.Core
                Engine.Common
    )

add_executable_module(${TARGET} ${LOCATION})


target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})
