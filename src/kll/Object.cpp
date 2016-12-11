//
// Created by Damian Stewart on 10/12/2016.
//

#include "Object.h"
#include <OpenGL/gl.h>
#include "kll.h"

void kll::Object::Draw()
{
    glPushMatrix();
    glTranslatef(mPosition.x, mPosition.y, mPosition.z);
    glScalef(mScale.x, mScale.y, mScale.z);
    DrawImpl();
    glPopMatrix();
}

void kll::Object::Update(float dt)
{
    mPosition += mVelocity * dt;
    UpdateImpl(dt);
}

