#include <stdexcept>
#include "LinAlg.h"

namespace graphics
{
    // COORD
    int Coord2D::operator[](int i) {
        if (i < 0 || i > 1) {
            throw std::out_of_range("Index must be between 0 or 1");
        }
        return i == 0 ? x : y;
    }

    Coord2D Coord2D::operator+(Coord2D const& v) {     
        return Coord2D(x + v.x, y + v.y);
    }
    
    Coord2D Coord2D::operator-(Coord2D const& v) {     
        return Coord2D(x - v.x, y - v.y);
    }

    Coord2D Coord2D::operator*(int k) {
        return Coord2D(x*k, y*k);
    }

    Coord2D Coord2D::operator/(int k) {
        return Coord2D(x/k, y/k);
    }

    int Coord2D::dot(Coord2D const& a, Coord2D const& b) {
        return a.x*b.x + a.y*b.y;
    }

    double Coord2D::norm() {
        return sqrt(x*x + y*y);
    }

    void Coord2D::swap(Coord2D& a, Coord2D& b) {
        Coord2D temp = a;
        a = b;
        b = temp;
    }

    // HOMOGCOORD3D
    HomogCoord3D::HomogCoord3D(std::vector<double> v) {
        if (v.size() != 3 && v.size() != 4) {
            throw std::invalid_argument("Vector must be of length 3 or 4");
        }
        x = v[0];
        y = v[1];
        z = v[2];

        if (v.size() > 3) {
            w = v[3];
        }
    }

    double HomogCoord3D::operator[](unsigned i) {
        if (i < 0 || i > 3) {
            throw std::out_of_range("Index must be 0, 1, 2 or 3");
        }
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: throw;
        }
    }

    HomogCoord3D HomogCoord3D::operator+(HomogCoord3D const& v) {     
        return HomogCoord3D(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    
    HomogCoord3D HomogCoord3D::operator-(HomogCoord3D const& v) {     
        return HomogCoord3D(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    HomogCoord3D HomogCoord3D::operator*(double k) {
        return HomogCoord3D(x*k, y*k, z*k, w*k);
    }

    HomogCoord3D HomogCoord3D::operator/(double k) {
        return HomogCoord3D(x/k, y/k, z/k, w/k);
    }

    HomogCoord3D HomogCoord3D::operator*(HomogCoord3D const& v) {
        if (w != v.w) {
            throw std::invalid_argument("Both w must be equal");
        }

        double _x = y*v.z - z*v.y;
        double _y = z*v.x - x*v.z;
        double _z = x*v.y - y*v.x;
        return HomogCoord3D(_x, _y, _z, w);
    }

    double HomogCoord3D::dot(HomogCoord3D const& a, HomogCoord3D const& b) {
        if (a.w != b.w) {
            throw std::invalid_argument("Both w must be equal");
        }
        
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }
    
    void HomogCoord3D::swap(HomogCoord3D& a, HomogCoord3D& b) {
        HomogCoord3D temp = a;
        a = b;
        b = temp;
    }

    double HomogCoord3D::norm() {
        return sqrt(x*x + y*y + z*z);
    }

    HomogCoord3D HomogCoord3D::normalised() {
        return *this / norm();
    }

    HomogCoord3D HomogCoord3D::canonical() {
        if (w == 0) {
            throw("Canonical representaiton of translations is undefined");
        }
        return HomogCoord3D(x / w, y / w, z / w, 1);
    }

    std::vector<double> HomogCoord3D::asVector() {
        return std::vector<double> {x, y, z, w};
    }
}