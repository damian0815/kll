
//
// Created by Damian Stewart on 08/01/2017.
//

#include "Light.h"


void kll::Light::UpdateColor()
{
    if (!mLight.getIsEnabled()) {
        return;
    }

    mLight.setDiffuseColor(mColor * mIntensity);
    mLight.setDiffuseColor(mColor * mIntensity);
}
