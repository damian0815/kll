//
// Created by Damian Stewart on 10/12/2016.
//

#include <ofMain.h>
#include "Object.h"
#include <OpenGL/gl.h>
#include "../kll.h"

void ofRotate(const quat &q);

void kll::Object::Draw()
{
    ofPushMatrix();
    ofSetColor(ofFloatColor(1,1,1,mAlpha));
    ofTranslate(mPosition.x, mPosition.y, mPosition.z);
    ofRotate(mOrientation);
    ofScale(mScale.x, mScale.y, mScale.z);
    DrawImpl();
    ofPopMatrix();
}

void ofRotate(const quat &q)
{
    auto angle = glm::degrees(glm::angle(q));
    auto axis = glm::axis(q);
    ofRotate(angle, axis.x, axis.y, axis.z);
}

void kll::Object::Update(float dt)
{
    mPosition += mVelocity * dt;
    UpdateImpl(dt);
}


