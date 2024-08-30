# ========================================================
# Setup Engine Asset Module.
# ========================================================
project(Engine.Asset)

set(LOCATION        .)
set(TARGET          Engine.Asset)
set(GROUP           Engine)
set(DEPS            Engine.Common
                    Engine.Core
                    )


add_library_module(${TARGET} STATIC ${LOCATION})
add_dependencies(${TARGET} ${TARGET}.Generated)

target_link_libraries(${TARGET} PRIVATE ${DEPS} INTERFACE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


# ========================================================
# Setup Engine Asset Test.
# ========================================================
if(NENUPHAR_TEST_ENABLE)

    project(${TARGET}.Test)

    set(TARGET_TEST     ${TARGET}.Test)
    set(SRCS 
                        Test/AssetRegistryTest.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})

    add_test(NAME ${TARGET}.Test COMMAND $<TARGET_FILE:${TARGET}.Test>)
endif()

