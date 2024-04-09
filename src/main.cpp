
#include "PainGine_lib.h"

int main()
{
    PlatformCreateWindow(1200, 720, "MyFirstSourcePlatformer");

    while (running)
    {
        // Update
        PlatformUpdateWindow();
        SM_TRACE("Test: ");
        SM_WARNING("Test: ");
        SM_ERROR("Tets: ");
        SM_ASSERTION(false, "Assertion not hit");
    }
    
    return 0;
}