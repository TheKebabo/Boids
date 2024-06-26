#include "Boid.h"
#include "LinAlg.h"

namespace boids
{
    void Boid::drawSelf(CanvasHandler* canvas) {
        double dX = 4, dY = 4;
        double dir = this->dir();

        // Find relative rotated equilateral triangle points
        double s = sin(dir), c = cos(dir);

        Coord2D relA((-dX) * c - (dY) * s, (-dX) * s + (dY) * c);   // Top-left (-1, 1) if dir = 0
        Coord2D relB((-dX) * c - (-dY) * s, (-dX) * s + (-dY) * c);   // Bottom-left (-1, -1) if dir = 0
        Coord2D relC((dX) * c - (0) * s, (dX) * s + (0) * c);             // Middle-right (1, 0) if dir = 0
        
        Coord2D pos2D = Coord2D(pos_.x, pos_.y); // WHEN 3D, actual pos is projected into integer Coord2D
        canvas->drawSolidTriangle(relA + pos2D, relB + pos2D, relC + pos2D, col_);
    }

    void Boid::updatePos() {
        pos_ = (pos_ + velocity_ * speed_);
    }
}