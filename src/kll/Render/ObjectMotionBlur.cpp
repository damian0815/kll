//
// Created by Damian Stewart on 12/01/2017.
//

#include "ObjectMotionBlur.h"
#include "../Engine/Environment.h"

void kll::ObjectMotionBlur::Setup()
{
    mVelocityShader.load("velocity");

}

void kll::ObjectMotionBlur::DrawVelocityBuffer(float dt)
{
    //uniform mat4 uModelViewProjectionMat;
    //uniform mat4 uPrevModelViewProjectionMat;

    auto environment = kll::Environment::GetInstance();

    mVelocityShader.begin();
    for (auto o: environment->GetAllObjects()) {
        o->GetVelocity();
    }


}
