#include <random>
#include "Boid.h"

#pragma once

namespace boids
{
    class BoidsHandler {
    public:
        bool mouseIsDown = false;

        // Empty constructor
        BoidsHandler() {};

        // Initialise all boid positions, directions etc.
        void initBoids(int numBoids);

        void setCanvasHandler(CanvasHandler* canvas) { canvas_ = canvas; }

        // Updates boids' velocities and positions based on the 'rules', and draws them
        void updateAndDrawBoids(HomogCoord3D mousePos);

        // DEBUG to show average positions and velocities
        void drawAveragePosAndVels();

    private:
        std::vector<Boid> boids_;
        double boundaryEffect_ = 40;
        double limitingSpeed_ = 1000;
        double radiusOfVisibility_ = 200;

        double alignPositionEffect_ = 0.01; // Larger = higher effect
        double seperationEffect_ = 0.1;
        double alignVelocityEffect_ = 0.125;
        double tendToPosEffect_ = 0.5;
        CanvasHandler* canvas_;
        std::random_device rd_;

        HomogCoord3D alignPosition_(Boid* b);
        HomogCoord3D seperateIfNearby_(Boid* b);
        HomogCoord3D alignVelocities_(Boid* b);
        HomogCoord3D boundPosition_(Boid* b);
        HomogCoord3D tendToPos_(Boid* b, HomogCoord3D pos);
        void limitSpeed_(Boid* b);
    };
}