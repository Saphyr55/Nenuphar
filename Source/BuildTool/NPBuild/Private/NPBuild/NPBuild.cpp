#include "NPBuild/NPBuild.hpp"

#include <Nenuphar/Core/Core.hpp>

#include <fstream>
#include <filesystem>

using namespace Nenuphar;

constexpr auto GTemplateFormat = R"(#pragma once

#ifdef NSHARED
    // Exports
    #ifdef _MSC_VER
        #define NAPI __declspec(dllexport)
    #else
        #define NAPI __attribute__((visibility("default")))
    #endif
#else

    // Imports
    #ifdef _MSC_VER
        #define NAPI __declspec(dllimport)
    #else
        #define NAPI
    #endif
#endif
)"; 

int main(int argc, const char* argv[])
{

    if (argc < 2)
    {
        NP_ERROR(NPBuild::main, "Missing filepath generated file as argument.");
        return EXIT_FAILURE;
    }
    
    const char* filePathArg = argv[1];

    std::filesystem::path filePath{ filePathArg };
    std::filesystem::create_directories(filePath.parent_path());

    std::ofstream generatedFile(filePath);
    generatedFile << GTemplateFormat;
    generatedFile.close();

    NP_INFO(NPBuild::main, "Finish to generate files.");

    return EXIT_SUCCESS;

}
