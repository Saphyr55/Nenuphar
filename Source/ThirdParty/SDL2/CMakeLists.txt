
set(GROUP       ThirdParty)

add_subdirectory(SDL)
set_target_properties(
        SDL2
        SDL2_test
        SDL2main
        PROPERTIES FOLDER ${GROUP})
