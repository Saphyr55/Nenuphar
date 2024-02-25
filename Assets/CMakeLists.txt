project(Assets C)

set(TARGET      Assets)
set(RESOURCE_FILES
        Resources.h
        Shaders/MainFragment.glsl
        Shaders/MainVertex.glsl)
    
add_custom_target(AssetsGen ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets
        COMMENT "Copying assets...")
