#include "NPBuild/NPBuild.hpp"

#include <Nenuphar/Core/Core.hpp>

#include <fstream>
#include <filesystem>

using namespace Nenuphar;

int main(int argc, char const *argv[])
{

    for (int i = 0; i < argc; i++)
    {
        NP_INFO(NPBuild::Main, "'{}'", argv[i]);
    }
    
    if (argc < 2)
    {
        NP_ERROR(NPBuild::Main, "Missing filepath generated file as argument.");
        return EXIT_FAILURE;
    }

    const char* FilePathArg = argv[1];

    std::filesystem::path FilePath{ FilePathArg };
    std::filesystem::create_directories(FilePath.parent_path());

    std::ofstream GeneratedFile(FilePath);
    GeneratedFile << "#pragma once\n";
    
    GeneratedFile.close();

    NP_INFO(NPBuild::Main, "Finish to generate files.");

    return EXIT_SUCCESS;

}
