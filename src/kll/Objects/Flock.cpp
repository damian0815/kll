//
// Created by Damian Stewart on 20/02/2017.
//

#include "Flock.h"
#include "../../3rdparty/nanoflann.hpp"

namespace kll
{


    void Flock::Update(float dt)
    {

        for (auto &b: mBoids) {
            UpdateBoid(b);
        }

    }

    void Flock::UpdateBoid(kll::Boid &boid)
    {
        // http://www.vergenet.net/~conrad/boids/pseudocode.html

        auto v1 = Rule1(boid, neighbours);
        auto v2 = Rule2(boid, neighbours);
        auto v3 = Rule3(boid, neighbours);


    }

}