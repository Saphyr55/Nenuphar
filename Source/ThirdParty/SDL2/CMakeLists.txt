
set(GROUP       ThirdParty)

add_subdirectory(SDL)
set_target_properties(SDL2 SDL2-static PROPERTIES FOLDER ${GROUP})
