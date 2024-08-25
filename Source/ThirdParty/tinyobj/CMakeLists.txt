project(tinyobj)

set(TARGET      tinyobj)
set(GROUP       ThirdParty)

add_library(${TARGET} STATIC)

target_include_directories(${TARGET} PUBLIC tinyobj)
target_sources(${TARGET} PRIVATE tinyobj/tiny_obj_loader.cc)

set_target_properties(${TARGET} PROPERTIES FOLDER ${GROUP})
