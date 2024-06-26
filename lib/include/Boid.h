#include "CanvasHandler.h"
#include "LinAlg.h"
#include "MiscMaths.h"

using namespace graphics;
namespace boids
{
    class Boid {
    public:
        Boid(Colors col) : col_(col) {}
        Boid(Coord2D &pos, Colors col) : pos_(HomogCoord3D(pos.x, pos.y, 0, 1)), col_(col) {}
        Boid(Coord2D &pos, double dir, Colors col) : pos_(HomogCoord3D(pos.x, pos.y, 0, 1)), col_(col) { setDir(dir); }
        Boid(HomogCoord3D &pos, Colors col) : col_(col) {
            setPos(pos);
        }
        Boid(HomogCoord3D &pos, double dir, Colors col) : pos_(pos), col_(col) {
            setPos(pos);
            setDir(dir);
        }

        void setPos(HomogCoord3D &pos) {
            pos_ = pos;
            pos_.w = 1;
        }
        void updatePos();   // Updates position from its velocity
        HomogCoord3D& pos() { return pos_; }

        void setDir(double dir) {
            HomogCoord3D newVUnscaled = (HomogCoord3D(cos(dir), sin(dir), 0, 0)).normalised();
            velocity_ = newVUnscaled * velocity_.norm();
        }
        const double dir() { return atan2(velocity_.y, velocity_.x); }
        
        void updateVelocityFromRules(HomogCoord3D* v1, HomogCoord3D* v2, HomogCoord3D* v3);
        HomogCoord3D& velocity() { return velocity_; }

        void setCol(Colors col) { col_ = col; }
        const uint32_t col() { return col_; }

        void drawSelf(CanvasHandler* canvas);
    private:
        HomogCoord3D pos_; // (w != 0)
        HomogCoord3D velocity_ = HomogCoord3D(1, 0, 0, 0); // (w = 0)
        uint32_t col_;
    };
}