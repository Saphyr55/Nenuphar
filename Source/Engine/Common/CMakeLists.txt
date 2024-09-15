# ========================================================
# Setup Engine Common Lib.
# ========================================================
project(Engine.Common)

set(LOCATION        .)
set(TARGET          Engine.Common)
set(GROUP           Engine)
set(DEPS            fmt::fmt)

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS} INTERFACE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


# ========================================================
# Setup Engine Common Test.
# ========================================================
if(NENUPHAR_TEST_ENABLE)
    
    project(${TARGET}.Test)

    set(TARGET_TEST     ${TARGET}.Test)
    set(SRCS 
                        Test/FunctionalTest.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})

    add_test(NAME ${TARGET}.Test COMMAND $<TARGET_FILE:${TARGET}.Test>)
endif()

