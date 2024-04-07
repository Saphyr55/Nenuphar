# ========================================================
# Setup Math Lib for the engine.
# ========================================================
project(Engine.Math)

set(LOCATION    .)
set(TARGET      Engine.Math)
set(GROUP       Engine)
set(DEPS        Engine.Common)

add_library_module(${TARGET} STATIC ${LOCATION})

target_link_libraries(${TARGET} PRIVATE ${DEPS})
set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})


# ========================================================
# Setup Engine Math Test.
# ========================================================
if (NENUPHAR_TEST_ENABLE)

    project(${TARGET}.Test)

    set(TARGET_TEST     Engine.Math.Test)
    set(SRCS
            Test/Matrix3Test.cpp
            Test/Matrix4Test.cpp
            Test/Vector2Test.cpp
            Test/Vector3Test.cpp
            Test/Vector4Test.cpp
    )
    set(DEPS         Catch2::Catch2WithMain
                     Engine.Common)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} ${DEPS})
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})
endif()


