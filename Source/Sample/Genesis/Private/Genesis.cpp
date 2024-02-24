#include "Genesis/GenesisApplication.hpp"


int main(int argc, char* argv[])
{
    try
    {

        auto genesisApplication =
            MakeSharedRef<GenesisApplication>();

        genesisApplication->Setup();

        Float start = 0.0f;
        Float end = start;

        while (genesisApplication->IsRunning())
        {
            start = start + 0.1f;
            const Float deltaTime = start / 60.0f;

            genesisApplication->Update(deltaTime);

            end = start - end;
        }

        NP_DEBUG(W, "");

        genesisApplication->Destroy();
        
    }
    catch (const std::exception& exception)
    {
        NP_CRITICAL(Engine, "Exception occured.");
        NP_CRITICAL(Engine, "{}", exception.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
