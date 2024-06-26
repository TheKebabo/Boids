#include <stdint.h>
#include "LinAlg.h"
#include "MiscMaths.h"

#pragma once

namespace graphics
{
      enum Colors
      {
            red = 0xFF0000,
            green = 0x00FF00,
            blue = 0x0000FF,
            yellow = 0XFFFF00,
            purple = 0xFF00FF,
            cyan = 0x00FFFF,
            white = 0xFFFFFF,
            black = 0x000000,
      };

      class CanvasHandler {
      public:
            CanvasHandler() {}
            CanvasHandler(int cw, int ch): cWidth_(cw), cHeight_(ch) {}

            // Getters/setters
                  unsigned& cWidth()       { return cWidth_; }
            const unsigned cWidth() const { return cWidth_; }
                  unsigned& cHeight()       { return cHeight_; }
            const unsigned cHeight() const { return cHeight_; }

            const Coord2D centre() { return Coord2D(static_cast<int>(cWidth_/2), static_cast<int>(cHeight_/2)); }

            void setPixel(unsigned x, unsigned y, uint32_t val);
            uint32_t *pixels() { return pixels_; }
            uint32_t **pixelsPointer() { return &pixels_; }

            void setScreen(uint32_t color);
            void drawLine(Coord2D pointA, Coord2D pointB, uint32_t color);
            void drawWireframeTriangle(Coord2D const& p0, Coord2D const& p1, Coord2D const& p2, uint32_t color);
            void drawSolidTriangle(Coord2D &p0, Coord2D &p1, Coord2D &p2, uint32_t color);
            void drawShadedTriangle(Coord2D &p0, Coord2D &p1, Coord2D &p2, uint32_t color);

      private:
            uint32_t *pixels_;

            // Canvas width and height (px)
            unsigned cWidth_ = 100;  unsigned cHeight_ = 100;

            double fov_ = PI/2;
      };
}
