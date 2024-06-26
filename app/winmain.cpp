#include <windows.h>
#include "MessageHandling.h"
#include "BoidsHandler.h"

using namespace boids;

static graphics::CanvasHandler canvas;
static BoidsHandler boidsHandler;

static MSG msg;
bool quit;
static graphics::Colors cols;

LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);
#if RAND_MAX == 32767
#define Rand32() ((rand() << 16) + (rand() << 1) + (rand() & 1))
#else
#define Rand32() rand()
#endif

// GRAPHICY STUFF
static BITMAPINFO frameBitmapInfo;
static HBITMAP frameBitmap;
static HDC frameDeviceContext;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE NULLInstance, PSTR pCmdLine, int nCmdShow) {
    // Register window class for main window
    const wchar_t windowClassName[] = L"My Window Class";
    static WNDCLASS windowClass;
    windowClass.lpfnWndProc = WindowProcessMessage;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = (PCSTR)windowClassName;
    
    if (!RegisterClass(&windowClass))
        return false;

    // Define frame bitmap attributes
    frameBitmapInfo.bmiHeader.biSize = sizeof(frameBitmapInfo.bmiHeader);
    frameBitmapInfo.bmiHeader.biPlanes = 1;
    frameBitmapInfo.bmiHeader.biBitCount = 32;
    frameBitmapInfo.bmiHeader.biCompression = BI_RGB;
    frameDeviceContext = CreateCompatibleDC(0);

    boidsHandler.setCanvasHandler(&canvas);
    
    // Create the main window
    static HWND windowHandle;
    windowHandle = CreateWindow((PCSTR)windowClassName, "Boids", WS_MAXIMIZE | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    // If the main window isn't created, terminate
    if(!windowHandle)
        return false;
    
    // Hide cursor
    while(ShowCursor(false)>=0);

    // Show and paint window
    ShowWindow(windowHandle, nCmdShow);
    UpdateWindow(windowHandle);

    boidsHandler.initBoids(75);

    // Message loop
    while(!quit) {
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            DispatchMessage(&msg);

        // BOID-SPECIFIC UPDATE LOOP
        canvas.setScreen(black);
        boidsHandler.updateAndDrawBoids();

        // boidsHandler.drawAveragePosAndVels(&sumOfPosAndVel[0], &sumOfPosAndVel[1]);

        InvalidateRect(windowHandle, NULL, FALSE);
        UpdateWindow(windowHandle);
    }

    return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_QUIT:
        case WM_DESTROY: {
            quit = handleQuit();
        } break;

        case WM_PAINT: {
            handlePaint(windowHandle, frameDeviceContext);
        } break;

        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            handleSize(frameBitmap, &frameBitmapInfo, frameDeviceContext, width, height, &canvas);
        } break; 

        default: {
            return DefWindowProc(windowHandle, message, wParam, lParam);
        }
    }
    return 0;
}