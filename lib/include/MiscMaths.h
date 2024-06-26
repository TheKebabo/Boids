#include <vector>

#pragma once

# define PI     3.14159265358979323846
# define TAU    6.28318530717958647692

namespace graphics
{
    int absol(int x);
    double absol(double x);
    double norm(double val, double min, double max); // Assuming val is between min and max
    double lerp(double v0, double v1, double t);
    std::vector<double> lerp(int x0, int y0, int x1, int y1);
    std::vector<double> lerp(double x0, double y0, double x1, double y1);
    std::vector<int> bresenLerp(int x0, int y0, int x1, int y1);
    std::vector<int> bresenLow(int x0, int y0, int x1, int y1);
    std::vector<int> bresenHigh(int x0, int y0, int x1, int y1);
    double clamp(double val, double min, double max);
    uint32_t scaleColor(uint32_t color, double k);
}