//
// Created by Damian Stewart on 08/01/2017.
//

#ifndef OFAPP_LIGHT_H
#define OFAPP_LIGHT_H

#include <gl/ofLight.h>
#include "gvec3.h"

namespace kll
{

    class Lighty
    {
    public:
        void Enable() { mLight.enable(); UpdateColor(); }
        void Disable() { mLight.disable(); }

        float GetIntensity() { return mIntensity; }
        void SetIntensity(float i);

        kll::gvec3 GetPosition() { return mLight.getPosition(); }
        void SetPosition(kll::gvec3 p) { mLight.setPosition(p); }

    private:
        void UpdateColor();

        float mIntensity = 1;
        ofFloatColor mColor = ofFloatColor::white;

        ofLight mLight;

    };
}


#endif //OFAPP_LIGHT_H
