//
// Created by Damian Stewart on 08/01/2017.
//

#ifndef OFAPP_LIGHT_H
#define OFAPP_LIGHT_H

#include <gl/ofLight.h>

namespace kll
{

    class Light
    {
    public:
        void Enable() { mLight.enable(); UpdateColor(); }
        void Disable() { mLight.disable(); }

        float GetIntensity() { return mIntensity; }
        void SetIntensity(float i) { mIntensity = i; UpdateColor(); }

    private:
        void UpdateColor();

        float mIntensity = 1;
        ofFloatColor mColor = ofFloatColor::white;

        ofLight mLight;

    };
}


#endif //OFAPP_LIGHT_H
