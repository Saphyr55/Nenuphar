# ========================================================
# Setup Engine Model Module.
# ========================================================
project(Engine.Model)

set(LOCATION        .)
set(TARGET          Engine.Model)
set(GROUP           Engine)
set(DEPS            fmt::fmt
                    tinyobj
                    Engine.Common
                    Engine.Math
                    Engine.Core 
                    Engine.Rendering    
                    Engine.Graphics                                    
                    Engine.Asset
                    )

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS} INTERFACE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


# ========================================================
# Setup Engine Mesh Loader Test.
# ========================================================
if(NENUPHAR_TEST_ENABLE)

    project(${TARGET}.Test)

    set(TARGET_TEST     ${TARGET}.Test)
    set(SRCS 
                        Test/WavefrontObjLexerTest.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})

    add_test(NAME ${TARGET}.Test COMMAND $<TARGET_FILE:${TARGET}.Test>)
endif()

