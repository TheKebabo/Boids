#include <string>
#include <windows.h>
#include "UtilityFunctions.h"
#include "CanvasHandler.h"

using namespace std;
using namespace graphics;

namespace utilities
{
    void moveMouseToClientCentre(CanvasHandler canvHandler, MouseState* mouseState) { 
        Coord2D centreCanv = canvHandler.centre();
        SetCursorPos(centreCanv.x, centreCanv.y);
        if (*mouseState == outClientArea)
            *mouseState = justEnteredClientArea;
    }

    // Tracks mouse to determine whether in client area or not
    void trackMouse(HWND hwnd) {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_HOVER | TME_LEAVE; // Type of events to track
        tme.dwHoverTime = 1; // Default is 400 ms
        tme.hwndTrack = hwnd;
        TrackMouseEvent(&tme);
    }
}