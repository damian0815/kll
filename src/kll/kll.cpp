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

float kll::RandomNormal()
{
    float value = 0;
    for (int i=0; i<12; i++) {
        value += Random();
    }
    return (value - 6.0f)/6.0f;
}


float kll::RandomNormal(float min, float max)
{
    auto range = max - min;
    auto center = min + range/2;
    auto r = RandomNormal();
    return r*range + center;
}

vec3 kll::RandomVector3(const vec3 &min, const vec3 &max)
{
    return glm::vec3(Random(min.x, max.x), Random(min.y, max.y), Random(min.z, max.z));
}
