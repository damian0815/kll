//
// Created by Damian Stewart on 11/12/2016.
//

#include "FallBehaviour.h"
#include "Object.h"

kll::FallBehaviour::FallBehaviour(kll::Object *target) : Behaviour(target)
{

}

void kll::FallBehaviour::Update(float dt)
{
    const vec3 GRAVITY(0, 1, 0);
    mTarget->SetVelocity(mTarget->GetVelocity() + dt * GRAVITY);

}
