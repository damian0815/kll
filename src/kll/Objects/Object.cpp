//
// Created by Damian Stewart on 10/12/2016.
//

#include <ofMain.h>
#include "Object.h"
#include <OpenGL/gl.h>
#include "../kll.h"

void ofRotate(const quat &q);

kll::Object::Object()
: mScale(1,1,1)
{
    ofMaterial::Data materialData;

    materialData.diffuse = ofFloatColor::white;
    materialData.ambient = ofFloatColor(0.01, 0.01, 0.01, 1);
    materialData.specular = ofFloatColor::white;
    materialData.emissive = ofFloatColor::black;
    materialData.shininess = 10;

    mMaterial.setData(materialData);

}

void kll::Object::Draw()
{
    bool shouldUseMaterial = GetShouldUseMaterial();

    ofPushMatrix();


    ofTranslate(mPosition.x, mPosition.y, mPosition.z);
    ofRotate(mOrientation);
    ofScale(mScale.x, mScale.y, mScale.z);

    ofSetColor(ofFloatColor(1,1,1,mAlpha));
    if (shouldUseMaterial) {
        mMaterial.begin();
    }
    DrawImpl();
    if (shouldUseMaterial) {
        mMaterial.end();
    }

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



