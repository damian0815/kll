//
// Created by Damian Stewart on 11/12/2016.
//

#include "PercussionVisuals.h"
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

float kll::RandomNormal()
{
    float value = 0;
    for (int i=0; i<12; i++) {
        value += Random();
    }
    return (value - 6.0f)/6.0f;
}