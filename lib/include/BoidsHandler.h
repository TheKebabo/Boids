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

        // Draws current state of each boid, also summing their positions and velocities for rules 1 and 3 respectively 
        std::vector<HomogCoord3D> drawBoids();

        // Updates boids' velocities and positions based on the 'rules'
        void updateBoids(HomogCoord3D* sumOfPos, HomogCoord3D* sumOfVels);

        // DEBUG to show average positions and velocities
        void drawAveragePosAndVels(HomogCoord3D* sumOfPos, HomogCoord3D* sumOfVels);

    private:
        std::vector<Boid> boids_;
        CanvasHandler* canvas_;
        std::random_device rd_;

        HomogCoord3D rule1_(Boid* b, HomogCoord3D* sumOfPos);
        HomogCoord3D rule2_(Boid* b);
        HomogCoord3D rule3_(Boid* b, HomogCoord3D* sumOfVels);
    };
}