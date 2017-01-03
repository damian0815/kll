//
// Created by Damian Stewart on 11/12/2016.
//

#include "FallBehaviour.h"
#include "../Objects/Object.h"

kll::FallBehaviour::FallBehaviour(Object *target, vec3 gravity)
        : mGravity(gravity)
{
    mTarget = target;

}

void kll::FallBehaviour::Update(float dt)
{
    mTarget->SetVelocity(vec3(mTarget->GetVelocity()) + dt * mGravity);
}
