//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_IMPLODEBEHAVIOUR_H
#define OFAPP_IMPLODEBEHAVIOUR_H

#include "Behaviour.h"
#include "../Engine/gvec3.h"
#include <glm/glm.hpp>
using glm::vec3;

namespace kll {

    class ImplodeBehaviour: public Behaviour
    {
    public:
        void Setup(Object *target, kll::gvec3 scaleAffect);

        void Update(float dt) override;

        bool ShouldObjectBeDestroyed() override;

        void Reset() override ;

    private:

        float mScale = 1;
        vec3 mScaleAffect;

    };

}

#endif //OFAPP_IMPLODEBEHAVIOUR_H
