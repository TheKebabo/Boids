#include <string>
#include "CanvasHandler.h"
#include "MiscMaths.h"
#include "UtilityFunctions.h"

namespace graphics
{
    void CanvasHandler::setPixel(unsigned x, unsigned y, uint32_t val) {
        if (x < cWidth_ && y < cHeight_) {
                pixels_[y*cWidth_ + x] = val;
        }
    }

    void CanvasHandler::drawLine(Coord2D pointA, Coord2D pointB, uint32_t color) {
        int dx = absol(pointB.x - pointA.x);
        int sx = pointA.x < pointB.x ? 1 : -1;

        int dy = -absol(pointB.y - pointA.y);
        int sy = pointA.y < pointB.y ? 1 : -1;
        int error = dx + dy;
        
        int x = pointA.x;   int y = pointA.y;
        while (true) {
            this->setPixel(x, y, color);

            if (x == pointB.x && y == pointB.y) { return; }

            int e2 = 2 * error;
            if (e2 >= dy) {
                if (x == pointB.x) { return; }
                error += dy;
                x += sx;
            }
            if (e2 <= dx) {
                if (y == pointB.y) { return; }
                error += dx;
                y += sy;
            }
        }
    }

    void CanvasHandler::drawWireframeTriangle(Coord2D const& p0, Coord2D const& p1, Coord2D const& p2, uint32_t color) {        
        CanvasHandler::drawLine(p0, p1, color);
        CanvasHandler::drawLine(p1, p2, color);
        CanvasHandler::drawLine(p2, p0, color);
    }

    void CanvasHandler::drawSolidTriangle(Coord2D &p0, Coord2D &p1, Coord2D &p2, uint32_t color) {
        // Sort the points so that y0 <= y1 <= y2
        if (p1.y < p0.y) { Coord2D::swap(p1, p0); }
        if (p2.y < p0.y) {  Coord2D::swap(p2, p0); }
        if (p2.y < p1.y) { Coord2D::swap(p2, p1); }
        
        // Compute the x coordinates of the triangle edges 
        std::vector<int> x01 = bresenLerp(p0.y, p0.x, p1.y, p1.x);
        std::vector<int> x12 = bresenLerp(p1.y, p1.x, p2.y, p2.x);
        std::vector<int> x02 = bresenLerp(p0.y, p0.x, p2.y, p2.x);   

        // Concatenate the short sides
        std::vector<int> x012 = x01;
        x012.pop_back();
        x012.insert(x012.end(), x12.begin(), x12.end());

        // Determine which is left and which is right
        std::vector<int> xLeft, xRight;

        int m = static_cast<int>(x02.size() / 2);
        if (x02[m] < x012[m]) {
            xLeft = x02;
            xRight = x012;
        } else {
            xLeft = x012;
            xRight = x02;
        }

        // Draw the horizontal segments
        for (int y = p0.y; y <= p2.y; y++) {
            for (int x = xLeft[y - p0.y]; x <= xRight[y - p0.y]; x++) {
                setPixel(x, y, color);
            }
        }
    }

    void CanvasHandler::drawShadedTriangle(Coord2D &p0, Coord2D &p1, Coord2D &p2, uint32_t color) {
        // Sort the points so that y0 <= y1 <= y2
        if (p1.y < p0.y) { Coord2D::swap(p1, p0); }
        if (p2.y < p0.y) {  Coord2D::swap(p2, p0); }
        if (p2.y < p1.y) { Coord2D::swap(p2, p1); }
        
        // Compute the x coordinates of the triangle edges 
        std::vector<int> x01 = bresenLerp(p0.y, p0.x, p1.y, p1.x);
        std::vector<double> h01 = lerp(static_cast<double>(p0.y), p0.h, static_cast<double>(p1.y), p1.h);

        std::vector<int> x12 = bresenLerp(p1.y, p1.x, p2.y, p2.x);
        std::vector<double> h12 = lerp(static_cast<double>(p1.y), p1.h, static_cast<double>(p2.y), p2.h);

        std::vector<int> x02 = bresenLerp(p0.y, p0.x, p2.y, p2.x);
        std::vector<double> h02 = lerp(static_cast<double>(p0.y), p0.h, static_cast<double>(p2.y), p2.h); 

        // Concatenate the short sides and their h-values
        std::vector<int> x012 = x01;
        x012.pop_back();
        x012.insert(x012.end(), x12.begin(), x12.end());

        std::vector<double> h012 = h01;
        h012.pop_back();
        h012.insert(h012.end(), h12.begin(), h12.end()); 

        // Determine which is left and which is right
        std::vector<int> xLeft, xRight;
        std::vector<double> hLeft, hRight;

        int m = static_cast<int>(x02.size() / 2);
        if (x02[m] < x012[m]) {
            xLeft = x02;
            hLeft = h02;

            xRight = x012;
            hRight = h012;
        } else {
            xLeft = x012;
            hLeft = h012;

            xRight = x02;
            hRight = h02;
        }

        // Draw the horizontal segments
        int i = 0;
        for (int y = p0.y; y <= p2.y; y++) {
            int curXLeft = xLeft[i];
            int curXRight = xRight[i];

            std::vector<double> hSegment = lerp(static_cast<double>(curXLeft), hLeft[i], static_cast<double>(curXRight), hRight[i]);
            for (int x = curXLeft; x <= curXRight; x++) {
                uint32_t shadedColor = scaleColor(color, hSegment[x-curXLeft]);
                setPixel(x, y, shadedColor);
            }
            i++;
        }
    }

    void CanvasHandler::setScreen(uint32_t color) {
        size_t numPixels = cWidth_ * cHeight_;
        for (int i = 0; i < numPixels; i++ ) {
            pixels_[i] = color;
        }
    }
}