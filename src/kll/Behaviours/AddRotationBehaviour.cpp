//
// Created by Damian Stewart on 11/12/2016.
//

#include <glm/gtc/quaternion.hpp>
#include "AddRotationBehaviour.h"
#include "../Objects/Object.h"

kll::AddRotationBehaviour::AddRotationBehaviour(Object *target, vec3 angularVelocity)
        : mAngularVelocity(angularVelocity)
{
    mTarget = target;

}

void kll::AddRotationBehaviour::Update(float dt)
{
    auto deltaRotation = glm::quat(mAngularVelocity * dt);

    auto newRotation = mTarget->GetOrientation() * deltaRotation;
    mTarget->SetOrientation(newRotation);
}
