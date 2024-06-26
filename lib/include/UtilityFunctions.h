#include <windows.h>
#include <sstream>
#include "LinAlg.h"
#include "CanvasHandler.h"

#pragma once

using namespace graphics;

namespace utilities
{
    enum MouseState { inClientArea, outClientArea, justEnteredClientArea };

    // Debug functions
    template<typename T> void outputVal(T arg) {
        std::stringstream ss;
        ss << arg << std::endl;
        OutputDebugStringA(ss.str().c_str());
    }
    template<typename T> void outputVal(std::vector<T> arg) {
        std::stringstream ss;
        for (int i = 0; i < arg.size(); i++) {
            ss << arg[i];
            if (i < arg.size()-1) {
                ss << ", ";
            }
        }
        ss << std::endl;
        OutputDebugStringA(ss.str().c_str());
    }

    // Moves mouse to centre of client screen
    void moveMouseToClientCentre(CanvasHandler canvHandler, MouseState* mouseState);

    // Tracks mouse to determine whether in client area or not
    void trackMouse(HWND hwnd);
};