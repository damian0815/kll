//
// Created by Damian Stewart on 10/12/2016.
//

#include <cmath>
#include "ImplodeBehaviour.h"
#include "Object.h"

kll::ImplodeBehaviour::ImplodeBehaviour(Object *target, vec3 scaleAffect)
        : Behaviour(target), mScaleAffect(scaleAffect)
{


}

void kll::ImplodeBehaviour::Update(float dt)
{
    float implodeRate = 0.2f;

    mScale *= std::pow(implodeRate, dt);

    vec3 equalScale(mScale, mScale, mScale);
    vec3 scaleDelta = equalScale - mTarget->GetScale();

    mTarget->SetScale(mTarget->GetScale() + scaleDelta * mScaleAffect);
}

bool kll::ImplodeBehaviour::ShouldObjectBeDestroyed()
{
    static const float MIN_SCALE = 0.001;
    return mScale <= MIN_SCALE;
}

