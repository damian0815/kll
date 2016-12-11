//
// Created by Damian Stewart on 11/12/2016.
//

#include "kll.h"

std::ostream& glm::operator<<(std::ostream& o, const vec3& v)
{
    return o << "(" << v.x << "," << v.y << "," << v.z << ")";
}

float kll::Random(float low, float high)
{
    auto random = arc4random();

    return low + (float(random)/float(0xffffffff)) * (high-low);
}

