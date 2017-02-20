//
// Created by Damian Stewart on 20/02/2017.
//

#include "Flock.h"

namespace kll
{

    Flock::Flock(int boidCount)
    {
        const int MAX_LEAF_SIZE = 10;
        mKdTree = new KdTreeType(DIMENSIONS, this, nanoflann::KDTreeSingleIndexAdaptorParams(MAX_LEAF_SIZE) );

    }

    Flock::~Flock()
    {
        delete mKdTree;
    }

    struct Neighbours {
        vector<size_t> indices;
        vector<float> distances;
        Neighbours(int count) : indices(count), distances(count) {}
    };

    void Flock::Update(float dt)
    {
        const int NUM_NEIGHBOURS = 7;
        nanoflann::KNNResultSet<float> neighbourResultSet(NUM_NEIGHBOURS);
        Neighbours neighbours(NUM_NEIGHBOURS);
        neighbourResultSet.init(&neighbours.indices[0], &neighbours.distances[0]);

        mKdTree->buildIndex();

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