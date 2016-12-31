//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_BEHAVIOUR_H
#define OFAPP_BEHAVIOUR_H

#include <memory>

namespace kll {

    class Object;

    class Behaviour
    {
    public:
        virtual ~Behaviour() {}

        virtual void Update(float dt) = 0;
        virtual bool ShouldObjectBeDestroyed() { return false; }
        Object* GetTarget() { return mTarget; }

    protected:

        Object* mTarget = nullptr;

    };

}

#endif //OFAPP_BEHAVIOUR_H
