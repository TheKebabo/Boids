#include <windows.h>
#include "CanvasHandler.h"

#pragma once

namespace boids
{
    void handlePaint(HWND windowHandle, HDC frameDeviceContext);
    void handleSize(HBITMAP frameBitmap, BITMAPINFO* frameBitmapInfo, HDC frameDeviceContext, int width, int height, graphics::CanvasHandler* canvas);
    bool handleQuit();
}