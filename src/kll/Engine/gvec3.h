//
// Created by Damian Stewart on 29/12/16.
//

#ifndef OFAPP_GVEC3_H
#define OFAPP_GVEC3_H

#include <glm/glm.hpp>
using glm::vec3;

namespace kll
{

    struct gvec3
    {
        gvec3() = default;

        gvec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
        {}

        gvec3(const vec3 &v) : x(v.x), y(v.y), z(v.z)
        {}

        operator vec3() const
        { return vec3(x, y, z); }

        float x = 0, y = 0, z = 0;
    };

}

#endif //OFAPP_GVEC3_H
