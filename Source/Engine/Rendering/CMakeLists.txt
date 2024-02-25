# ========================================================
# Setup Engine Common Lib.
# ========================================================
project(Engine.Rendering)

set(LOCATION        .)
set(TARGET          Engine.Rendering)
set(GROUP           Engine)
set(DEPS            fmt::fmt 
                    glad 
                    Engine.Common 
                    Engine.Core 
                    Engine.ApplicationCore
                    )

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS} INTERFACE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


# ========================================================
# Setup Engine Common Test.
# ========================================================
if(NENUPHAR_TEST_ENABLE)

    project(Engine.Rendering.Test)

    set(TARGET_TEST     Engine.Rendering.Test)
    set(SRCS 
                        Test/Rendering.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})
endif()
