//
// Created by Damian Stewart on 20/02/2017.
//

#ifndef OFAPP_FLOCK_H
#define OFAPP_FLOCK_H


#include <vector>
#include "../Engine/gvec3.h"
#include "../../3rdparty/nanoflann.hpp"
#include "Object.h"
using glm::vec3;

using std::vector;

namespace kll {

    struct FlockAdapter {

        FlockAdapter(const vector<Boid>& boids) : mBoids(boids) {}
        const vector<Boid>& mBoids;

        inline size_t kdtree_get_point_count() const { return mBoids.size(); }

        // Returns the distance between the vector "p1[0:size-1]" and the data point with index "idx_p2" stored in the class:
        inline float kdtree_distance(const float *p1, const size_t idx_p2,size_t /*size*/) const
        {
            const auto& boid = GetBoid(idx_p2);
            const auto& position = boid.position;
            const float d0 = p1[0] - position.x;
            const float d1 = p1[1] - position.y;
            const float d2 = p1[2] - position.z;
            return d0*d0+d1*d1+d2*d2;
        }

        inline const :: ::kll::Boid& GetBoid(const size_t idx_p2) const
        {
            return mBoids[idx_p2];
        }

        // Returns the dim'th component of the idx'th point in the class:
        // Since this is inlined and the "dim" argument is typically an immediate value, the
        //  "if/else's" are actually solved at compile time.
        inline float kdtree_get_pt(const size_t idx, int dim) const
        {
            const auto& boid = GetBoid(idx);
            const auto& position = boid.position;
            if (dim == 0) { return position.x; }
            else if (dim==1) { return position.y; }
            else { return position.z; }
        }

        // Optional bounding-box computation: return false to default to a standard bbox computation loop.
        //   Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again.
        //   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
        template <class BBOX>
        bool kdtree_get_bbox(BBOX& /* bb */) const { return false; }

    };

    struct Boid
    {
        vec3 position;
        vec3 velocity;
    };

    class Flock : public kll::Object
    {
    public:

        Flock(int boidCount);

        ~Flock();

        void Update(float dt) override;


    private:

        void UpdateBoid(kll::Boid &boid, const struct Neighbours &neighbours, const float dt);

        struct Neighbours {
            vector<size_t> indices;
            vector<float> distances;
            Neighbours(size_t count) : indices(count), distances(count) {}
        };


        static const int DIMENSIONS = 3;
        typedef nanoflann::KDTreeSingleIndexAdaptor<
                nanoflann::L2_Simple_Adaptor<float, FlockAdapter>,
                FlockAdapter,
                DIMENSIONS
        > KdTreeType;
        KdTreeType *mKdTree;

        FlockAdapter mKdTreeAdapter;

        vector<Boid> mBoids;

        <unknown> Rule1(const Boid &boid, const Neighbours &neighbours);

        <unknown> Rule2(const Boid &boid, const Neighbours &neighbours);

        vec3 Rule3(const Boid &boid, const Neighbours &neighbours);
    };




}

#endif //OFAPP_FLOCK_H