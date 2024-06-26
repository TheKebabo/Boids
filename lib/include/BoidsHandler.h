#include <random>
#include "Boid.h"

namespace boids
{
    class BoidsHandler {
    public:
        // Empty constructor
        BoidsHandler() {};

        // Initialise all boid positions, directions etc.
        void initBoids(int numBoids);

        void setCanvasHandler(CanvasHandler* canvas) { canvas_ = canvas; }

        // Updates boids' velocities and positions based on the 'rules', and draws them
        void updateAndDrawBoids();

        // DEBUG to show average positions and velocities
        void drawAveragePosAndVels();

    private:
        std::vector<Boid> boids_;
        double boundaryEffect_ = 50;
        double radiusOfVisibility_ = 100;
        CanvasHandler* canvas_;
        std::random_device rd_;

        HomogCoord3D alignPosition_(Boid* b);
        HomogCoord3D seperateIfNearby_(Boid* b);
        HomogCoord3D alignVelocities_(Boid* b);
        HomogCoord3D boundPosition_(Boid* b);
    };
}