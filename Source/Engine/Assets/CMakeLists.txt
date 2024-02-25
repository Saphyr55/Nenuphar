# ========================================================
# Setup Engine Assets Module.
# ========================================================
project(Engine.Assets)

set(LOCATION        .)
set(TARGET          Engine.Assets)
set(GROUP           Engine)
set(DEPS            fmt::fmt 
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

    project(Engine.${TARGET}.Test)

    set(TARGET_TEST     Engine.${TARGET}.Test)
    set(SRCS 
                        Test/Assets.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})
endif()

