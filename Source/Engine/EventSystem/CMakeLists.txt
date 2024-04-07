# ========================================================
# Setup Event System Module.
# ========================================================
project(Engine.EventSystem)

set(LOCATION        .)
set(TARGET          Engine.EventSystem)
set(GROUP           Engine)
set(DEPS            Engine.Common
                    Engine.Core
                    Engine.ApplicationCore
                    Engine.InputSystem
    )

add_library_module(${TARGET} STATIC ${LOCATION})
target_link_libraries(${TARGET} PRIVATE ${DEPS})

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})

# ========================================================
# Setup Engine Event-System Test.
# ========================================================
if(NENUPHAR_TEST_ENABLE)

    project(${TARGET}.Test)

    set(TARGET_TEST     ${TARGET}.Test)
    set(SRCS
            Test/EventTest.cpp)

    add_executable(${TARGET_TEST} ${SRCS})

    target_include_directories(${TARGET_TEST} PRIVATE Private)
    target_link_libraries(${TARGET_TEST} ${TARGET} 
            Engine.Common 
            Engine.Core 
            Catch2::Catch2WithMain)
    set_target_properties(${TARGET_TEST} PROPERTIES FOLDER ${GROUP})
endif()

