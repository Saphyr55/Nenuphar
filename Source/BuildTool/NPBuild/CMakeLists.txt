project(NPBuild)

set(LOCATION    .)
set(TARGET      NPBuild)
set(GROUP       BuildTool)
set(DEPS        fmt::fmt
                Engine.Core
                Engine.Common
    )

add_executable_module(${TARGET} ${LOCATION})

add_custom_target(NPBuildGen
    DEPENDS NPBuild
    COMMAND NPBuild ${CMAKE_BINARY_DIR}/Generated/Generated.hpp
    COMMENT "NPBuild processing..."
    VERBATIM
    )

target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})
