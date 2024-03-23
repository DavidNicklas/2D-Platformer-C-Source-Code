#pragma once

#include <stdio.h>

// ##################################################################################
//                                 Platform Globals
// ##################################################################################
static bool running = true;


#pragma region Window Generation

// ##################################################################################
//                                 Platform Functions
// ##################################################################################
bool PlatformCreateWindow(int width, int height, char* title);
void PlatformUpdateWindow();

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
        windowsClass.hIcon = LoadIcon(instance, IDI_ASTERISK);               // Set the icon of the application
        windowsClass.hCursor = LoadCursor(instance, IDC_CROSS);                 // Set the Cursor of the application
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
                                    CW_USEDEFAULT,
                                    CW_USEDEFAULT,
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

#pragma endregion

#pragma region Logging

// ##################################################################################
//                                    Defines
// ##################################################################################


// ##################################################################################
//                                    Logging
// ##################################################################################
enum TextColor
{
    TEXT_COLOR_BLACK,
    TEXT_COLOR_RED,
    TEXT_COLOR_GREEN,
    TEXT_COLOR_YELLOW,
    TEXT_COLOR_BLUE,
    TEXT_COLOR_MAGENTA,
    TEXT_COLOR_CYAN,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_BRIGHT_BLACK,
    TEXT_COLOR_BRIGHT_RED,
    TEXT_COLOR_BRIGHT_GREEN,
    TEXT_COLOR_BRIGHT_YELLOW,
    TEXT_COLOR_BRIGHT_BLUE,
    TEXT_COLOR_BRIGHT_MAGENTA,
    TEXT_COLOR_BRIGHT_CYAN,
    TEXT_COLOR_BRIGHT_WHITE,
    TEXT_COLOR_COUNT,
};


template<typename ...Args>
void _log(char* prefix, char* msg, TextColor textColor, Args... args);


#pragma endregion