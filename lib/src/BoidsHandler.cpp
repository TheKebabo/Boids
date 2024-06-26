#include "BoidsHandler.h"
#include "UtilityFunctions.h"
#include <vector>

namespace boids
{
    void BoidsHandler::initBoids(int numBoids) {
        std::mt19937 gen(rd_());
        std::uniform_int_distribution<> distrX(0, canvas_->cWidth()-1);
        std::uniform_int_distribution<> distrY(0, canvas_->cHeight()-1);
        std::uniform_real_distribution<> distrDir(0, 2*PI);

        for (int i = 0; i < numBoids; ++i) {
            Boid b(Coord2D(distrX(gen), distrY(gen)), distrDir(gen), white);
            boids_.push_back(b);
        }
    }

    std::vector<HomogCoord3D> BoidsHandler::drawBoids() {
        HomogCoord3D sumOfPos(0, 0, 0, 1);
        HomogCoord3D sumOfVels(0, 0, 0, 0);
        for (Boid b : boids_) {
            b.drawSelf(canvas_);
            sumOfPos = sumOfPos + b.pos();
            sumOfVels = sumOfVels + b.velocity();
        }
        std::vector<HomogCoord3D> returnVals = std::vector<HomogCoord3D> { sumOfPos, sumOfVels };
        return returnVals;
    }

    void BoidsHandler::updateBoids(HomogCoord3D* sumOfPos, HomogCoord3D* sumOfVels) {
        for (int i = 0; i < boids_.size(); ++i) {
            Boid* b = &boids_[i];
            HomogCoord3D v1 = rule1_(b, sumOfPos);
            HomogCoord3D v2 = rule2_(b);
            HomogCoord3D v3 = rule3_(b, sumOfVels);
            b->updateVelocityFromRules(&v1, &v2, &HomogCoord3D(0, 0, 0, 0));
            b->updatePos();
        }
    }

    // RULE 1: Boids try to fly towards the centre of mass of neighbouring boids
    HomogCoord3D BoidsHandler::rule1_(Boid* b, HomogCoord3D* sumOfPos) {
        // 'Percieved' CofM for all boids but one is found by summing all other boid positions and dividing by N - 1
        // - can be achieved by summing all, and then subtracting each boid's position sequentially
        HomogCoord3D sumWithoutCurrent = *sumOfPos - b->pos();
        HomogCoord3D cOfM = sumWithoutCurrent / ((double)boids_.size()-1);
        return (cOfM - b->pos()) / 100;
    }

    // RULE 2: Boids try to keep a small distance away from other objects (including only boids for now).
    HomogCoord3D BoidsHandler::rule2_(Boid* b) {
        HomogCoord3D c;
        for (Boid bOther : boids_) {
            if (&bOther != b) {
                HomogCoord3D bPos = b->pos();
                HomogCoord3D bOtherPos = bOther.pos();
                HomogCoord3D dPos = bOtherPos - bPos;
                if (dPos.norm() < 100)
                    c = c - dPos;
            }
        }
        return c;
    }

    // RULE 3: Boids try to match velocity with near boids.
    HomogCoord3D BoidsHandler::rule3_(Boid* b, HomogCoord3D* sumOfVels) {
        // 'Percieved' average velocity for all boids but one is found by summing all other boid positions and dividing by N - 1
        // - can be achieved by summing all, and then subtracting each boid's position sequentially
        HomogCoord3D sumWithoutCurrent = *sumOfVels - b->velocity();
        HomogCoord3D avg = sumWithoutCurrent  / ((double)boids_.size()-1);
        return (avg - b->velocity()) / 8;
    }

    // DEBUG METHODS

    void BoidsHandler::drawAveragePosAndVels(HomogCoord3D* sumOfPos, HomogCoord3D* sumOfVels) {
        HomogCoord3D avgPos = *sumOfPos / (double)boids_.size();
        HomogCoord3D avgVels = *sumOfVels / (double)boids_.size();
        Boid* b = &Boid(avgPos, pink);
        b->setVelocity(avgVels);
        b->drawSelf(canvas_);
    }
}