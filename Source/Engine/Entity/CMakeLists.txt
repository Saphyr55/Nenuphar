# ========================================================
# Setup Engine Rendering Module.
# ========================================================
project(Engine.Entity)

set(LOCATION        .)
set(TARGET          Engine.Entity)
set(GROUP           Engine)
set(DEPS            fmt::fmt
                    stb
                    Engine.Common
                    Engine.Core
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
            Test/EntityTest.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})
endif()

