#include "MiscMaths.h"

namespace graphics
{
    int absol(int x) { return (x >= 0 ? x : -x); }
    double absol(double x) { return (x >= 0 ? x : -x); }

    double norm(double val, double min, double max) {
        return (val - min) / (max - min);
    }

    double lerp(double v0, double v1, double t) {
        return (1 - t) * v0 + t * v1;
    }

    std::vector<double> lerp(int x0, int y0, int x1, int y1) {
        return lerp(static_cast<double>(x0), static_cast<double>(y0), static_cast<double>(x1), static_cast<double>(y1));
    }

    std::vector<double> lerp(double x0, double y0, double x1, double y1) {
        double dx = x1 - x0;
        if (dx == 0) {
            std::vector<double> vals = {y0};
            return vals;
        }

        std::vector<double> vals(static_cast<int>(dx+1));    

        double a = static_cast<double>((y1 - y0) / dx);
        
        for (int i = 0; i <= dx; i++) {
            vals[i] = y0;
            y0 += a;
        }
        return vals;
    }

    std::vector<int> bresenLerp(int x0, int y0, int x1, int y1) {
        if (absol(y1 - y0) < absol(x1 - x0)) {
            return bresenLow(x0, y0, x1, y1);
        }
        return bresenHigh(x0, y0, x1, y1);
    }

    std::vector<int> bresenLow(int x0, int y0, int x1, int y1) {
        int dx = x1 - x0; int dy = y1 - y0;
        
        std::vector<int> yVals(absol(dx) + 1);

        int yIncr = 1;
        if (dy < 0) {   // y must decrease instead of increasing
            yIncr = -1;
            dy *= -1;
        }
            
        int y = y0;

        if (dx > 0) {
            int D = 2*dy - dx;

            for (int i = 0; i <= dx; i++) {
                yVals[i] = y;
                if (D > 0) {
                    y += yIncr;
                    D += 2*(dy - dx);
                } else {
                    D += 2*dy;
                }
            }
        } else {
            dx *= -1;
            int D = 2*dy - dx;

            for (int i = dx; i >= 0; i--) {
                yVals[i] = y;
                if (D > 0) {
                    y += yIncr;
                    D += 2*(dy - dx);
                } else {
                    D += 2*dy;
                }
            }  
        }

        return yVals;
    }

    std::vector<int> bresenHigh(int x0, int y0, int x1, int y1) {
        int dx = x1 - x0; int dy = y1 - y0;

        if (dx == 0) {
            std::vector<int> yVals{y1};
            return yVals;
        }

        std::vector<int> yVals(absol(dx) + 1);
        int xIncr = 1;

        if (dx < 0) {   // x must decrease instead of increasing
            xIncr = -1;
            dx *= -1;
        }
            
        int x = x0;
        
        if (dy > 0) {
            yVals[0] = y0;
            int D = 2*dx - dy;

            for (int y = y0; y < y1; y++) {
                if (D > 0) {
                    x += xIncr;
                    yVals[x - x0] = y;
                    D += 2*(dx - dy);
                } else {
                    D += 2*dx;
                }
            }
        } else {
            dy *= -1;
            int D = 2*dx - dy;

            for (int y = y0; y > y1; y--) {
                if (D > 0) {
                    yVals[x - x0] = y;
                    x += xIncr;
                    D += 2*(dx - dy);
                } else {
                    D += 2*dx;
                }
            }
            yVals[dx] = y1;
        }

        return yVals;
    }

     double clamp(double val, double min, double max) {
        if (val < min) { return min; }
        if (val > max) { return max; }
        return val;
    }
    
     uint32_t scaleColor(uint32_t color, double k) {
        k = clamp(k, 0, 1);
        uint8_t r = (color >> 16) & 0xFF;
        uint8_t g = (color >> 8) & 0xFF;
        uint8_t b = color & 0xFF;
        return static_cast<uint8_t>(r*k) << 16 | static_cast<uint8_t>(g*k) << 8 | static_cast<uint8_t>(b*k);
    }
}