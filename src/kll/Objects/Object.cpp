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
    ofPushMatrix();
    ofLoadMatrix(mModelViewMatrix);

    ofSetColor(ofFloatColor(1, 1, 1, mAlpha));
    if (mAlpha >= 1) {
        ofEnableDepthTest();
    } else {
        ofDisableDepthTest();
    }

    bool shouldUseMaterial = GetLightingEnabled() && GetShouldUseMaterial();
    if (shouldUseMaterial) {
        mMaterial.begin();
    }
    DrawImpl();
    if (shouldUseMaterial) {
        mMaterial.end();
    }

    ofPopMatrix();
}

ofMatrix4x4 kll::Object::GetTransformMatrix() const
{
    ofMatrix4x4 m;

    m.scale(mScale.x, mScale.y, mScale.z);

    auto angle = glm::degrees(glm::angle(mOrientation));
    auto axis = glm::axis(mOrientation);
    m.rotate(angle, axis.x, axis.y, axis.z);

    m.translate(mPosition.x, mPosition.y, mPosition.z);

    return m;
}

void ofRotate(const quat &q)
{
    auto angle = glm::degrees(glm::angle(q));
    auto axis = glm::axis(q);
    ofRotate(angle, axis.x, axis.y, axis.z);
}

void kll::Object::Update(float dt)
{
    mPreviousModelViewMatrix = mModelViewMatrix;

    mPosition += mVelocity * dt;
    UpdateImpl(dt);

    mModelViewMatrix = GetTransformMatrix() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);

    mRemainingLifetime -= dt;
}



