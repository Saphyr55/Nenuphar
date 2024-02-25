project(glad)

set(TARGET      glad)
set(GROUP       ThirdParty)

add_library(${TARGET} STATIC)

target_include_directories(${TARGET} PUBLIC glad/include)
target_sources(${TARGET} PRIVATE glad/src/glad.c glad/src/glad_wgl.c)

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})
