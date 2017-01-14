
//
// Created by Damian Stewart on 13/01/2017.
//

#include "KllCamera.h"

ofMatrix4x4 kll::KllCamera::GetTransform()
{
    ofMatrix4x4 m;
    m.makeTranslationMatrix(mPosition);
    return m * mOrientation;
}
