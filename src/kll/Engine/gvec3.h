//
// Created by Damian Stewart on 29/12/16.
//

#ifndef OFAPP_GVEC3_H
#define OFAPP_GVEC3_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
using glm::vec3;
using glm::quat;

namespace kll
{


    struct gvec3
    {
        gvec3() = default;

        gvec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
        {}

        gvec3(const vec3 &v) : x(v.x), y(v.y), z(v.z)
        {}

        gvec3 operator +(const gvec3& v) const { return gvec3(x+v.x, y+v.y, z+v.z); }
        gvec3 operator -(const gvec3& v) const { return gvec3(x-v.x, y-v.y, z-v.z); }
        gvec3 operator *(float f) const { return gvec3(x*f, y*f, z*f); }
        gvec3 operator /(float f) const { return gvec3(x/f, y/f, z/f); }

        operator vec3() const
        { return vec3(x, y, z); }

        float x = 0, y = 0, z = 0;
    };

    static float Length(const gvec3& v) { return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z); }
    static gvec3 Normalize(const gvec3& v) { return v/Length(v); }

    struct gquat
    {
        gquat() = default;

        gquat(float x, float y, float z, float w) : q(x,y,z,w)
        {}

        gquat(const gvec3& euler) : q(vec3(euler))
        {}

        gquat(const vec3 &euler) : q(euler)
        {}

        gquat(const quat &quat) : q(quat)
        {}

        operator quat() const
        { return q; }

        gquat operator*(float f) const { return gquat(q*f); }
        gquat operator*(const gquat& otherQ) const { return gquat(q * otherQ.q); }

    private:
        quat q;
    };

}

#endif //OFAPP_GVEC3_H
