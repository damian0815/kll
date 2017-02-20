//
// Created by Damian Stewart on 20/02/2017.
//

#include "Flock.h"

namespace kll
{

    Flock::Flock(int boidCount)
    : mKdTreeAdapter(mBoids)
    {
        const int MAX_LEAF_SIZE = 10;
        mKdTree = new KdTreeType(DIMENSIONS, mKdTreeAdapter, nanoflann::KDTreeSingleIndexAdaptorParams(MAX_LEAF_SIZE) );

    }

    Flock::~Flock()
    {
        delete mKdTree;
    }


    void Flock::Update(float dt)
    {
        const int NUM_NEIGHBOURS = 7;
        nanoflann::KNNResultSet<float> neighbourResultSet(NUM_NEIGHBOURS);
        Neighbours neighbours(NUM_NEIGHBOURS);
        neighbourResultSet.init(&neighbours.indices[0], &neighbours.distances[0]);

        mKdTree->buildIndex();

        vector<float> queryPos;
        for (auto &b: mBoids) {
            queryPos = { b.position.x, b.position.y, b.position.z };
            mKdTree->findNeighbors(neighbourResultSet, &queryPos[0], nanoflann::SearchParams(10));
            UpdateBoid(b, neighbours, 0);
        }

    }

    void Flock::UpdateBoid(kll::Boid &boid, const struct Neighbours &neighbours, const float dt)
    {
        // http://www.vergenet.net/~conrad/boids/pseudocode.html

        auto v1 = Rule1(boid, neighbours);
        auto v2 = Rule2(boid, neighbours);
        auto v3 = Rule3(boid, neighbours);

        boid.velocity += v1 + v2 + v3;
        boid.position += boid.velocity * dt;

    }

    vec3 Flock::Rule1(const Boid &boid, const Flock::Neighbours &neighbours)
    {
        // Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
        vec3 c;
        for (const auto idx: neighbours.indices) {
            c += mBoids[idx].position;
        }
        c /= neighbours.indices.size();
        return c;
    }

    vec3 Flock::Rule2(const Boid &boid, const Flock::Neighbours &neighbours)
    {
        // Rule 2: Boids try to keep a small distance away from other objects (including other boids).

    }

    vec3 Flock::Rule3(const Boid &boid, const Flock::Neighbours &neighbours)
    {
        return glm::vec3();
    }

}