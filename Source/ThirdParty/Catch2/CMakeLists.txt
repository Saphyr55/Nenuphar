
set(GROUP       ThirdParty)

add_subdirectory(Catch2)
set_target_properties(Catch2 Catch2WithMain PROPERTIES FOLDER ${GROUP})
