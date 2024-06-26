#include <windows.h>
#include <vector>

#pragma once

namespace graphics
{
  struct Coord2D {
    static int dot(Coord2D const& a, Coord2D const& b);
    static void swap(Coord2D &a, Coord2D &b);

    int x = 0, y = 0;
    double h = 1;
    Coord2D() {}
    Coord2D(int _x, int _y) : x(_x), y(_y) {}
    Coord2D(double _x, double _y) : x(int(_x)), y(int(_y)) {}
    Coord2D(int _x, int _y, double _h) : x(_x), y(_y), h(_h) {}
    Coord2D(double _x, double _y, double _h) : x(int(_x)), y(int(_y)), h(_h) {}
    Coord2D(POINT p) : x(p.x), y(p.y) {}

    int operator[](int i); 
    Coord2D operator+(Coord2D const& v);
    Coord2D operator-(Coord2D const& v);
    Coord2D operator*(int k);    // Scalar
    Coord2D operator/(int k);
    
    double norm();

    bool operator==(Coord2D const& c) { return x == c.x && y == c.y && h == c.h; }
  };

  struct HomogCoord3D {
    static double dot(HomogCoord3D const& a, HomogCoord3D const& b);
    static void swap(HomogCoord3D &a, HomogCoord3D &b);

    double x = 0, y = 0, z = 0, w = 1;
    HomogCoord3D() {}
    HomogCoord3D(double _x, double _y) : x(_x), y(_y) {}
    HomogCoord3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    HomogCoord3D(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}
    HomogCoord3D(std::vector<double> v);

    double operator[](unsigned i); 
    HomogCoord3D operator+(HomogCoord3D const& v);
    HomogCoord3D operator-(HomogCoord3D const& v);
    HomogCoord3D operator*(double k);               // Scalar
    HomogCoord3D operator/(double k);        
    HomogCoord3D operator*(HomogCoord3D const& v);  // Cross

    double norm();
    HomogCoord3D normalised();
    HomogCoord3D canonical();

    std::vector<double> asVector();
    
    bool operator==(HomogCoord3D const& v) { return x = v.x && y == v.y && w == v.w; }
  };
}