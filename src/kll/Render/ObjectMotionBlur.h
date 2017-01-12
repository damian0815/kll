//
// Created by Damian Stewart on 12/01/2017.
//

#ifndef OFAPP_OBJECTMOTIONBLUR_H
#define OFAPP_OBJECTMOTIONBLUR_H

#include <gl/ofShader.h>
#include <gl/ofFbo.h>

namespace kll {

	// http://john-chapman-graphics.blogspot.co.at/2013/01/per-object-motion-blur.html

class ObjectMotionBlur
{
public:
    void Setup();

    void DrawVelocityBuffer(float dt);

private:

    ofShader mVelocityShader;
    ofFbo mVelocityBuffer;

};

}

#endif //OFAPP_OBJECTMOTIONBLUR_H
