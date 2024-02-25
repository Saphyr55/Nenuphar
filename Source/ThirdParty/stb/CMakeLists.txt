project(stb)

set(TARGET      stb)
set(GROUP       ThirdParty)

add_library(${TARGET} STATIC)

target_include_directories(${TARGET} PUBLIC stb)
target_sources(${TARGET} PRIVATE stb/stb_image.c)

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})
