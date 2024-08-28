# ========================================================
# Setup Engine Rendering Module.
# ========================================================
project(Engine.Rendering)

set(LOCATION        .)
set(TARGET          Engine.Rendering)
set(GROUP           Engine)
set(DEPS            fmt::fmt
                    stb
                    glad
                    Engine.Common
                    Engine.Math
                    Engine.Core
                    Engine.Model
                    Engine.ApplicationCore
                    Engine.EventSystem
                    Engine.InputSystem
                    Engine.Asset
                    )

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS} INTERFACE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


# ========================================================
# Setup Engine Rendering Test.
# ========================================================
if(NENUPHAR_TEST_ENABLE)

    project(${TARGET}.Test)

    set(TARGET_TEST     ${TARGET}.Test)
    set(SRCS 
                        Test/Rendering.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})

    add_test(NAME ${TARGET}.Test COMMAND $<TARGET_FILE:${TARGET}.Test>)
endif()

