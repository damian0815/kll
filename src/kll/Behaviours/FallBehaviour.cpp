//
// Created by Damian Stewart on 11/12/2016.
//

#include "FallBehaviour.h"
#include "../Object.h"

kll::FallBehaviour::FallBehaviour(Object *target, vec3 gravity)
        : Behaviour(target), mGravity(gravity)
{

}

void kll::FallBehaviour::Update(float dt)
{
    mTarget->SetVelocity(mTarget->GetVelocity() + dt * mGravity);

}
