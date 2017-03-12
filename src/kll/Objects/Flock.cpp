//
// Created by Damian Stewart on 20/02/2017.
//

#include "Flock.h"

namespace kll
{
    static vector<Boid> MakeBoids(int count, float scale)
    {
        vector<Boid> boids(count);
        const vec3 min(-scale, -scale, -scale);
        const vec3 max(scale, scale, scale);
        for (int i=0; i<count; i++) {
            boids[i].position = kll::RandomVector3(min, max);
        }
        return boids;
    }

    Flock::Flock(int boidCount, const FlockParams &params)
    : mBoids(MakeBoids(boidCount, 1.0f)), mKdTreeAdapter(mBoids), mParams(params)
    {
        const int MAX_LEAF_SIZE = 10;
        mKdTree = new KdTreeType(DIMENSIONS, mKdTreeAdapter, nanoflann::KDTreeSingleIndexAdaptorParams(MAX_LEAF_SIZE) );

    }

    Flock::~Flock()
    {
        delete mKdTree;
    }


    void Flock::UpdateImpl(float dt)
    {
        mKdTree->buildIndex();

        mCurrentFlockCenter = vec3();
        for (const auto& b: mBoids) {
            mCurrentFlockCenter += b.position;
        }
        mCurrentFlockCenter /= mBoids.size();

        const float RANDOM_RANGE = 2.9;
        int maxNeighbours = mParams.mNeighboursToConsider + int(RANDOM_RANGE*2);
        Neighbours neighbours(maxNeighbours);
        vector<float> queryPos;
        for (int bIdx = 0; bIdx < mBoids.size(); bIdx++) {
            auto& b = mBoids[bIdx];
            int numNeighbours = mParams.mNeighboursToConsider + int(kll::RandomNormal(RANDOM_RANGE, -RANDOM_RANGE));
            nanoflann::KNNResultSet<float> neighbourResultSet(numNeighbours);

            queryPos = { b.position.x, b.position.y, b.position.z };
            neighbourResultSet.init(&neighbours.indices[0], &neighbours.distances[0]);
            mKdTree->findNeighbors(neighbourResultSet, &queryPos[0], nanoflann::SearchParams(10));
            UpdateBoid(bIdx, neighbours, dt);
        }

    }

    void Flock::UpdateBoid(int boidIdx, const Flock::Neighbours &neighbours, const float dt)
    {
        // http://www.vergenet.net/~conrad/boids/pseudocode.html
        auto& boid = mBoids[boidIdx];
        auto v1 = mParams.mLocalCohesion * GetFlyTowardsCoMOfNeighboursVector(boidIdx, neighbours);
        auto v2 = mParams.mSeparation * GetKeepDistanceFromNeighboursVector(boidIdx, neighbours);
        auto v3 = mParams.mMatchVelocity * GetMatchVelocityWithNeighboursVector(boidIdx, neighbours);
        auto v4 = mParams.mStayInOnePlace * GetFlyTowardDesiredCenterVector(boid);
        auto v5 = mParams.mGlobalCohesion * GetFlyTowardActualFlockCenterVector(boid);

        auto acceleration = (v1 + v2 + v3 + v4 + v5);
        auto damping = -boid.velocity * mParams.mDampingFactor;
        boid.velocity += dt * (acceleration + damping);

        auto speed = glm::length(boid.velocity);
        if (speed > mParams.mMaxSpeed) {
            boid.velocity *= (mParams.mMaxSpeed/speed);
        }
        if (speed < mParams.mMinSpeed) {
            boid.velocity *= (mParams.mMinSpeed/speed);
        }

        boid.position += boid.velocity * dt;

    }

    vec3 Flock::GetFlyTowardsCoMOfNeighboursVector(const int boidIdx, const Flock::Neighbours &neighbours)
    {
        // Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
        vec3 c;
        for (const auto idx: neighbours.indices) {
            if (idx != boidIdx) {
                c += mBoids[idx].position;
            }
        }
        c /= neighbours.size() - 1;
        const auto& boid = mBoids[boidIdx];
        return c - boid.position;
    }

    vec3 Flock::GetKeepDistanceFromNeighboursVector(const int boidIdx, const Flock::Neighbours &neighbours)
    {
        // Rule 2: Boids try to keep a small distance away from other objects (including other boids).
        vec3 c;
        const auto& boid = mBoids[boidIdx];
        for (int i=0; i<neighbours.size(); i++) {
            int idx = neighbours.indices[i];
            if (idx != boidIdx) {
                auto delta = boid.position - mBoids[idx].position;
                float length = neighbours.distances[i];
                if (length > 0 && length < mParams.mSeparationThreshold) {
                    c += (delta/length) * 1.0f/length;
                }
            }
        }
        return c;
    }

    vec3 Flock::GetMatchVelocityWithNeighboursVector(const int boidIdx, const Flock::Neighbours &neighbours)
    {
        vec3 v;
        for (const auto& idx: neighbours.indices) {
            if (idx != boidIdx) {
                v += mBoids[idx].velocity;
            }
        }
        v /= neighbours.size() - 1;
        const auto& boid = mBoids[boidIdx];
        return (v - boid.velocity) / 8.0f;
    }

    void Flock::DrawImpl()
    {
        for (const auto& b: mBoids) {
            ofDrawCircle(toOfVector(b.position), 0.01f);
        }

        /*
        ofMesh mesh;

        for (const auto& b: mBoids) {
            mesh.addVertex(toOfVector(b.position));
        }
        mesh.setMode(OF_PRIMITIVE_POINTS);
        mesh.draw();*/

    }

    vec3 Flock::GetFlyTowardDesiredCenterVector(Boid &boid)
    {
        return mParams.mFlockCenter - boid.position;
    }

    vec3 Flock::GetFlyTowardActualFlockCenterVector(Boid &boid)
    {
        return mCurrentFlockCenter - boid.position;
    }

}