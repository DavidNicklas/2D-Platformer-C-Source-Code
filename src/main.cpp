
#include "NoobEngine_lib.h"

int main()
{
    PlatformCreateWindow(1200, 720, "MyFirstSourcePlatformer");

    while (running)
    {
        // Update
        PlatformUpdateWindow();
    }
    
    return 0;
}