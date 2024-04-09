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
#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#endif

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
void _log(char* prefix, char* msg, TextColor textColor, Args... args)
{
    static char* textColorTable[TEXT_COLOR_COUNT] = 
    {
        "\x1b[30m", // TEXT_COLOR_BLACK
        "\x1b[31m", // TEXT_COLOR_RED
        "\x1b[32m", // TEXT_COLOR_GREEN
        "\x1b[33m", // TEXT_COLOR_YELLOW
        "\x1b[34m", // TEXT_COLOR_BLUE
        "\x1b[35m", // TEXT_COLOR_MAGENTA
        "\x1b[36m", // TEXT_COLOR_CYAN
        "\x1b[37m", // TEXT_COLOR_WHITE
        "\x1b[90m", // TEXT_COLOR_BTIGHT_BLACK
        "\x1b[91m", // TEXT_COLOR_BIRGHT_RED
        "\x1b[92m", // TEXT_COLOR_BIRGHT_GREEN
        "\x1b[93m", // TEXT_COLOR_BRIGHT_YELLOW
        "\x1b[94m", // TEXT_COLOR_BRIGHT_BLUE
        "\x1b[95m", // TEXT_COLOR_BRIGHT_MAGENTA
        "\x1b[96m", // TEXT_COLOR_BRIGHT_CYAN
        "\x1b[97m", // TEXT_COLOR_BRIGHT_WHITE
    };

    char formatBuffer[8192] = {};
    sprintf(formatBuffer, "%s %s %s \033[0m", textColorTable[textColor], prefix, msg);

    char textBuffer[8192] = {};
    sprintf(textBuffer, formatBuffer, args...);

    puts(textBuffer);
}

#define SM_TRACE(msg, ...) _log("TRACE: ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__);
#define SM_WARNING(msg, ...) _log("WARNING: ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define SM_ERROR(msg, ...) _log("ERROR: ", msg, TEXT_COLOR_RED, ##__VA_ARGS__);

#define SM_ASSERTION(condition, msg, ...)       \
{                                               \
    if (!condition)                             \
    {                                           \
        SM_ERROR(msg, ##__VA_ARGS__);           \
        DEBUG_BREAK();                          \
    }                                           \
}

#pragma endregion