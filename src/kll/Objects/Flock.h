//
// Created by Damian Stewart on 20/02/2017.
//

#ifndef OFAPP_FLOCK_H
#define OFAPP_FLOCK_H


#include <vector>
#include "../Engine/gvec3.h"

using std::vector;

namespace kll {

    struct Boid
    {
        gvec3 position;
        gvec3 velocity;
    };

    class Flock
    {
    public:

        void Update(float dt);

    private:

        vector<Boid> mBoids;

        void UpdateBoid(Boid &boid);
    };

    struct PointCloud
    {
        PointCloud(vector<Boid>* boids) : mBoids(boids) {}
        vector<Boid>* mBoids;

        inline size_t kdtree_get_point_count() const { return mBoids->size(); }

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
            return mBoids->operator[](idx_p2);
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


}

#endif //OFAPP_FLOCK_H
