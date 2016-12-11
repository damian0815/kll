//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_BEHAVIOUR_H
#define OFAPP_BEHAVIOUR_H

#include <memory>

using std::shared_ptr;

namespace kll {

    class Object;

    class Behaviour
    {
    public:
        Behaviour(Object* target) : mTarget(target) {}

        virtual void Update(float dt) = 0;
        virtual bool ShouldObjectBeDestroyed() { return false; }

    protected:

        Object* mTarget;

    };

}

#endif //OFAPP_BEHAVIOUR_H
