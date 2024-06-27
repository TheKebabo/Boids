#include <windows.h>
#include "MessageHandling.h"

namespace messages
{
    void handlePaint(HWND windowHandle, HDC frameDeviceContext) {
        static PAINTSTRUCT paint;
        static HDC device_context;
        device_context = BeginPaint(windowHandle, &paint);
        BitBlt(device_context,
            paint.rcPaint.left, paint.rcPaint.top,
            paint.rcPaint.right - paint.rcPaint.left, paint.rcPaint.bottom - paint.rcPaint.top,
            frameDeviceContext,
            paint.rcPaint.left, paint.rcPaint.top,
            SRCCOPY);
        EndPaint(windowHandle, &paint);
    }

    void handleSize(HBITMAP frameBitmap, BITMAPINFO* frameBitmapInfo, HDC frameDeviceContext, int width, int height, graphics::CanvasHandler* canvas) {
            frameBitmapInfo->bmiHeader.biWidth  = width;
            frameBitmapInfo->bmiHeader.biHeight = height;

            if (frameBitmap) DeleteObject(frameBitmap);  

            frameBitmap = CreateDIBSection(frameDeviceContext, frameBitmapInfo, DIB_RGB_COLORS, (void**)canvas->pixelsPointer(), 0, 0); // NEED A PIXELS ARRAY LOCATION
            SelectObject(frameDeviceContext, frameBitmap);
            
            canvas->cWidth() = width;
            canvas->cHeight() = height;
    }

    bool handleQuit() {   
        return true;
    }

    void handleMouse(boids::BoidsHandler* bh, bool mouseIsDown) {
        bh->mouseIsDown = mouseIsDown;
    }
}