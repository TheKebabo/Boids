#include "BoidsHandler.h"
#include "UtilityFunctions.h"
#include <vector>

namespace boids
{
    void BoidsHandler::initBoids(int numBoids) {
        std::mt19937 gen(rd_());
        // INIT ALL BOIDS OFF SCREEN
        std::uniform_int_distribution<> distrEdges(0, 3); // different cases for each edge of screen 
        std::uniform_int_distribution<> distrX(0, canvas_->cWidth()-1); // random width of screen
        std::uniform_int_distribution<> distrY(0, canvas_->cHeight()-1); // random height of screen
        std::uniform_int_distribution<> distrDist(0, 50); // random distance from chosen edge of screen
        std::uniform_real_distribution<> distrDir(0, 2*PI);

        for (int i = 0; i < numBoids; ++i) {
            Boid* b;
            switch (distrEdges(gen)) {
                case 0: // LEFT EDGE
                    b = &Boid(Coord2D(-distrDist(gen), distrY(gen)), distrDir(gen), white);
                    break;
                case 1: // RIGHT EDGE
                    b = &Boid(Coord2D(canvas_->cWidth()-1 + distrDist(gen), distrY(gen)), distrDir(gen), white);
                    break;
                case 2: // BOTTOM EDGE
                    b = &Boid(Coord2D(distrX(gen), -distrDist(gen)), distrDir(gen), white);
                    break;
                case 3:
                    b = &Boid(Coord2D(distrX(gen), canvas_->cHeight()-1 + distrDist(gen)), distrDir(gen), white);
                    break;
            }
            boids_.push_back(*b);
        }
    }

    void BoidsHandler::updateAndDrawBoids() {
        for (int i = 0; i < boids_.size(); ++i) {
            Boid* b = &boids_[i];
            HomogCoord3D v1 = alignPosition_(b);
            HomogCoord3D v2 = seperateIfNearby_(b);
            HomogCoord3D v3 = alignVelocities_(b);
            HomogCoord3D v4 = boundPosition_(b);
            b->updateVelocity(v1 + v2 + v3 + v4);
            limitSpeed_(b);
            b->updatePos();
    
            b->drawSelf(canvas_);
        }
    }

    // MAIN RULE 1: Boids try to fly towards the centre of mass of neighbouring boids
    HomogCoord3D BoidsHandler::alignPosition_(Boid* b) {
        // 'Percieved' CofM for all boids but one is found by summing all other boid positions IN SOME RADIUS and dividing by N
        HomogCoord3D avgPos;
        unsigned n = 0;
        for (Boid bOther : boids_) {
            if (&bOther != b) {
                if ((b->pos() - bOther.pos()).norm() < radiusOfVisibility_) {
                    avgPos = avgPos + b->pos();
                    n++;
                }
            }
        }

        if (n > 0) {
            avgPos = avgPos / (double)n;
            return (avgPos - b->pos()) / 100;
        }
        return HomogCoord3D(0, 0, 0, 0);
    }

    // MAIN RULE 2: Boids try to keep a small distance away from other objects (only boids).
    HomogCoord3D BoidsHandler::seperateIfNearby_(Boid* b) {
        HomogCoord3D c;
        for (Boid bOther : boids_) {
            if (&bOther != b) {
                HomogCoord3D dPos = b->pos() - bOther.pos();
                if (dPos.norm() < seperation_)
                    c = c - dPos;   // Essentially doubles seperation
            }
        }
        return c;
    }

    // MAIN RULE 3: Boids try to match velocity with near boids
    HomogCoord3D BoidsHandler::alignVelocities_(Boid* b) {
        // 'Percieved' average velocity for all boids but one is found by summing all other boid velocities IN SOME RADIUS and dividing by N
        HomogCoord3D avgVel;
        unsigned n = 0;
        for (Boid bOther : boids_) {
            if (&bOther != b) {
                if ((b->pos() - bOther.pos()).norm() < radiusOfVisibility_) {
                    avgVel = avgVel + b->pos();
                    n++;
                }
            }
        }

        if (n > 0) {
            avgVel = avgVel / (double)n;
            return (avgVel - b->pos()) / 8;
        }
        return HomogCoord3D(0, 0, 0, 0);
    }

    // Keep boid inside rough screen boundaries
    HomogCoord3D BoidsHandler::boundPosition_(Boid* b) {
        HomogCoord3D v;
        double xPos = b->pos().x, yPos = b->pos().y;

        if (xPos < 0)
            // v.x = boundaryEffect_ * sqrt(-xPos);
            v.x = boundaryEffect_;
        else if (xPos >= canvas_->cWidth()) 
            // v.x = -boundaryEffect_ * sqrt(xPos - canvas_->cWidth() + 1);
            v.x = -boundaryEffect_;
        
        if (yPos < 0)
            // v.y = boundaryEffect_ * sqrt(-yPos);
            v.y = boundaryEffect_;
        else if (yPos >= canvas_->cHeight()) 
            // v.y = -boundaryEffect_ * sqrt(yPos - canvas_->cHeight() + 1);
            v.y = -boundaryEffect_;
        
        utilities::outputVal(v.norm());
        return v;
    }

    // Ensure magnitude of velocities don't become unrealistically high
    void BoidsHandler::limitSpeed_(Boid* b) {
        if (b->velocity().norm() > limitingSpeed_)
            b->setVelocity(b->velocity().normalised() * limitingSpeed_);
    }

    // DEBUG METHODS

    void BoidsHandler::drawAveragePosAndVels() {
        HomogCoord3D avgPos, avgVel;
        for (Boid b : boids_) {
            avgPos = avgPos + b.pos();
            avgVel = avgVel + b.velocity();
        }
        avgPos = avgPos / (double)boids_.size();
        avgVel = avgVel / (double)boids_.size();
        Boid b = Boid(avgPos, avgVel, pink);
        b.drawSelf(canvas_);
    }
}