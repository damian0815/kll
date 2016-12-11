//
// Created by Damian Stewart on 11/12/2016.
//

#ifndef OFAPP_FALLBEHAVIOUR_H
#define OFAPP_FALLBEHAVIOUR_H

#include "Behaviour.h"

namespace kll {
    class FallBehaviour: public Behaviour
    {
    public:
        FallBehaviour(Object *target);

    public:
        void Update(float dt) override;

    private:

    };
}


#endif //OFAPP_FALLBEHAVIOUR_H
