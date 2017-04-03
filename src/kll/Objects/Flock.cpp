//
// Created by Damian Stewart on 20/02/2017.
//

#include "Flock.h"

namespace kll
{
    void Flock::Reset()
    {
        const float scale = 1;
        const vec3 min(-scale, -scale, -scale);
        const vec3 max(scale, scale, scale);
        const int count = mBoids.size();
        for (int i=0; i<count; i++) {
            mBoids[i].position = mParams.mFlockCenter + kll::RandomVector3(min, max);
            mBoids[i].velocity = glm::normalize(kll::RandomVector3(min, max));
        }
    }

    Flock::Flock(int boidCount, const FlockParams &params)
    : mBoids(boidCount), mKdTreeAdapter(mBoids), mParams(params)
    {
        Reset();
        const int MAX_LEAF_SIZE = 10;
        mKdTree = new KdTreeType(DIMENSIONS, mKdTreeAdapter, nanoflann::KDTreeSingleIndexAdaptorParams(MAX_LEAF_SIZE) );

    }

    Flock::~Flock()
    {
        delete mKdTree;
    }


    void Flock::UpdateImpl(float dt)
    {
        assert(!HasNan());
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

        auto acceleration = Clamp(v1 + v2 + v3 + v4 + v5, 0, mParams.mMaxAcceleration);

        auto damping = -boid.velocity * mParams.mDampingFactor;
        auto deltaV = dt * (acceleration + damping);
        boid.velocity = Clamp(boid.velocity + deltaV, mParams.mMinSpeed, mParams.mMaxSpeed);

        boid.position += boid.velocity * dt;
        assert(!HasNan(boid));

    }

    glm::vec3 Flock::Clamp(const glm::vec3 &v, float minMagnitude, float maxMagnitude)
    {
        auto magnitude = glm::length(v);
        auto result = v;
        if (magnitude > maxMagnitude) {
            result *= (maxMagnitude / magnitude);
        }
        if (magnitude < minMagnitude) {
            result *= (minMagnitude / magnitude);
        }
        return result;
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
        if (mDebugRender) {
            ofDrawCircle(toOfVector(mParams.mFlockCenter), 0.2f);
        }

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

    bool Flock::HasNan()
    {
        for (const auto &b:mBoids) {
            if (HasNan(b)) {
                return true;
            }
        }
        return false;
    }

    bool Flock::HasNan(const Boid& b) {
        if (isnan(b.position.x)) {
            return true;
        }
        if (isnan(b.position.y)) {
            return true;
        }
        if (isnan(b.position.z)) {
            return true;
        }
        return false;
    }

}