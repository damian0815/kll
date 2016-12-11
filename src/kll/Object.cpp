//
// Created by Damian Stewart on 10/12/2016.
//

#include "Object.h"
#include <OpenGL/gl.h>
#include "kll.h"

void glRotatef(const quat &q);

void kll::Object::Draw()
{
    glPushMatrix();
    glTranslatef(mPosition.x, mPosition.y, mPosition.z);

    glRotatef(mOrientation);

    glScalef(mScale.x, mScale.y, mScale.z);
    DrawImpl();
    glPopMatrix();
}

void glRotatef(const quat &q)
{
    auto angle = glm::degrees(glm::angle(q));
    auto axis = glm::axis(q);
    glRotatef(angle, axis.x, axis.y, axis.z);
}

void kll::Object::Update(float dt)
{
    mPosition += mVelocity * dt;
    UpdateImpl(dt);
}


