//
// Created by Damian Stewart on 13/01/2017.
//

#ifndef OFAPP_CAMERA_H
#define OFAPP_CAMERA_H

#include <math/ofMatrix4x4.h>
#include "gvec3.h"

namespace kll {

    class KllCamera
    {
    public:
        void SetOrientation(const kll::gquat& q) { mOrientation = q; }
        void SetPosition(const kll::gvec3& p) { mPosition = p; }

        ofMatrix4x4 GetTransform();


    private:
        ofVec3f mPosition;
        ofQuaternion mOrientation;

    };

}

#endif //OFAPP_CAMERA_H
