project(Assets C)

set(TARGET      Assets)
set(RESOURCE_FILES
    Resources.h
    Shaders/MainFragment.glsl
    Shaders/MainVertex.glsl)
    

add_library(${TARGET} STATIC ${RESOURCE_FILES})
