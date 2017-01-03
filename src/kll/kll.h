//
// Created by Damian Stewart on 11/12/2016.
//

#ifndef OFAPP_KLL_H_H
#define OFAPP_KLL_H_H

#include <vector>
#include <glm/glm.hpp>
#include <fmt/ostream.h>

using std::vector;
using std::shared_ptr;
using glm::vec3;

namespace glm
{
    std::ostream &operator<<(std::ostream &o, const vec3 &v);
}

namespace kll
{
    float Random(float low=0, float high=1);
    float RandomNormal();
    float RandomNormal(float min, float max);
}

#endif //OFAPP_KLL_H_H
