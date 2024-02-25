project(NPBuild.Generator)

set(LOCATION    .)
set(TARGET      NPBuild.Generator)
set(GROUP       BuildTool)
set(DEPS        fmt::fmt
                Engine.Core
                Engine.Common
    )

add_library_module(${TARGET} STATIC ${LOCATION})

target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


