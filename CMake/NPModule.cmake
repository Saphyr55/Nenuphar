
function(generate module_name)

    #set(GENERATED_FILENAME ${module_name}.Generated.hpp)
    # set(GENERATE_FILE ${CMAKE_BINARY_DIR}/Generated/${module_name}/${GENERATED_FILENAME})
    
    #add_custom_target(${module_name}.Generated
    #    DEPENDS NPBuild
    #    COMMAND NPBuild ${GENERATE_FILE}
    #    COMMENT "NPBuild processing."
    #    VERBATIM
    #)

endfunction()

function(add_module module_name module_location)
    
    cmake_path(APPEND PUBLIC_FOLDER ${module_location} Public)
    cmake_path(APPEND PRIVATE_FOLDER ${module_location} Private)

    set(GENERATED_FOLDER ${CMAKE_BINARY_DIR}/Generated/${module_name})
    set(GENERATED_FILENAME ${module_name}.Generated.hpp)
    set(GENERATE_FILE ${GENERATED_FOLDER}/${GENERATED_FILENAME})

    file(GLOB_RECURSE MODULE_SOURCES
            ${PUBLIC_FOLDER}/**.hpp
            ${PUBLIC_FOLDER}/**.cpp
            ${PUBLIC_FOLDER}/**.inl
            ${PRIVATE_FOLDER}/**.hpp
            ${PRIVATE_FOLDER}/**.cpp
            ${PRIVATE_FOLDER}/**.inl
    )

    target_include_directories(${module_name} 
            PUBLIC
                ${GENERATED_FOLDER}
                ${PUBLIC_FOLDER}
            PRIVATE
                ${PRIVATE_FOLDER}
    )

    target_sources(${module_name} PRIVATE ${MODULE_SOURCES})

endfunction()


function(add_library_module module_name kind module_location)

    # generate(${module_name})

    add_library(${module_name} ${kind})
    add_module(${module_name} ${module_location})

    if (${kind} STREQUAL SHARED)
        target_compile_definitions(${module_name} PRIVATE NSHARED)
    elseif(${kind} STREQUAL STATIC)
        target_compile_definitions(${module_name} PRIVATE NLIB)
    endif()

    # add_dependencies(${module_name} ${module_name}.Generated)

endfunction()


function(add_executable_module module_name module_location)

    # generate(${module_name})

    add_executable(${module_name})
    add_module(${module_name} ${module_location})

    # add_dependencies(${module_name} ${module_name}.Generated)

endfunction()


function(add_test_module module_name module_location)

    project(Test)
    cmake_path(APPEND MODULE_TEST_FOLDER ${module_location} Test)

    set(MODULE_TEST_NAME ${module_name}.Test)
    file(GLOB_RECURSE TEST_FILES
            ${MODULE_TEST_FOLDER}/**.cpp
            ${MODULE_TEST_FOLDER}/**.hpp
    )

    add_executable(${MODULE_TEST_NAME} ${TEST_FILES})
    target_link_directories(${MODULE_TEST_NAME} PRIVATE ${MODULE_TEST_FOLDER})
    target_link_libraries(${MODULE_TEST_NAME} PRIVATE Catch2::Catch2WithMain ${module_name})


endfunction()
