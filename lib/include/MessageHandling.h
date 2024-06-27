#include <windows.h>
#include "CanvasHandler.h"
#include "BoidsHandler.h"

#pragma once

namespace messages
{
    void handlePaint(HWND windowHandle, HDC frameDeviceContext);
    void handleSize(HBITMAP frameBitmap, BITMAPINFO* frameBitmapInfo, HDC frameDeviceContext, int width, int height, graphics::CanvasHandler* canvas);
    bool handleQuit();
    void handleMouse(boids::BoidsHandler* bh, bool mouseIsDown);
}