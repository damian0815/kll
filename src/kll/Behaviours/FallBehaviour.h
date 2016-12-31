//
// Created by Damian Stewart on 11/12/2016.
//

#ifndef OFAPP_FALLBEHAVIOUR_H
#define OFAPP_FALLBEHAVIOUR_H

#include "../kll.h"
#include "Behaviour.h"

namespace kll {
    class FallBehaviour: public Behaviour
    {
    public:
        FallBehaviour(Object *target, vec3 gravity);

    public:
        void Update(float dt) override;

        void Reset() override {};

    private:

        vec3 mGravity;
    };
}


#endif //OFAPP_FALLBEHAVIOUR_H
