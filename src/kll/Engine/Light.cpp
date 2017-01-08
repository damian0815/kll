
//
// Created by Damian Stewart on 08/01/2017.
//

#include "Light.h"


void kll::Lighty::UpdateColor()
{
    if (!mLight.getIsEnabled()) {
        return;
    }

    mLight.setDiffuseColor(mColor * mIntensity);
    mLight.setSpecularColor(mColor * mIntensity);
}

void kll::Lighty::SetIntensity(float i)
{
    mIntensity = i;
    UpdateColor();
}
