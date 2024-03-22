
// ##################################################################################
//                                 Platform Globals
// ##################################################################################
static bool running = true;

// ##################################################################################
//                                 Platform Functions
// ##################################################################################
bool PlatformCreateWindow(int width, int height, char* title);

// ##################################################################################
//                                 Windows Platform
// ##################################################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <iostream>

// ##################################################################################
//                                 Windows Globals
// ##################################################################################
static HWND window;

// ##################################################################################
//                             Platform Implementations
// ##################################################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (msg)
    {
    case WM_CLOSE:
        running = false;
        break;
    
    default:
        // Let windows handle the default input for now
        result = DefWindowProcA(window, msg, wParam, lParam); 
        break;
    }

    return result;
}

bool PlatformCreateWindow(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0);

    char* windowClassID = "CppSourcePlatformer";

    WNDCLASSA windowsClass = {};
    windowsClass.hInstance = instance;
    windowsClass.hIcon = LoadIcon(instance, IDI_APPLICATION);               // Set the icon of the application
    windowsClass.hCursor = LoadCursor(instance, IDC_ARROW);                 // Set the Cursor of the application
    windowsClass.lpszClassName = windowClassID;                             // This is NOT the actual title, just a unique identifier (ID) for the window
    windowsClass.lpfnWndProc = windows_window_callback;                     // Callback for Input into the Window

    if (!RegisterClassA(&windowsClass))
    {
        return false;
    }
    
    // Set the style of the window
    int dwStyle = WS_OVERLAPPEDWINDOW;

    window = CreateWindowExA(0,
                                  windowClassID,                            // This is the ID
                                  title,                                    // Actual title
                                  dwStyle,
                                  100,
                                  100,
                                  width,
                                  height,
                                  NULL,                                     // parent
                                  NULL,                                     // menu
                                  instance,
                                  NULL);                                    // lpParam

    if (window == NULL)
    {
        return false;   
    }

    ShowWindow(window, SW_SHOW);

    return true;                        
}

void PlatformUpdateWindow()
{
    MSG msg;

    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);                                              // Calls hte callback specified when creating the window
    }
}

#endif


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