#include "NPBuild/NPBuild.hpp"

#include <fstream>
#include <filesystem>

constexpr auto GTemplateFormat = R"(#pragma once

#ifdef NSHARED
    // Exports
    #ifdef _MSC_VER
        #define NAPI __declspec(dllexport)
    #else
        #define NAPI __attribute__((visibility("default")))
    #endif
#else
    #define NAPI
#endif
)"; 

int main(int argc, const char* argv[])
{

    if (argc < 2)
    {
        return EXIT_FAILURE;
    }
    
    const char* filePathArg = argv[1];

    std::filesystem::path filePath{ filePathArg };
    std::filesystem::create_directories(filePath.parent_path());

    std::ofstream generatedFile(filePath);
    generatedFile << GTemplateFormat;
    generatedFile.close();

    return EXIT_SUCCESS;

}
