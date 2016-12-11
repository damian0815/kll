//
// Created by Damian Stewart on 09/12/2016.
//

#include "FeedbackTunnel.h"

void FeedbackTunnel::setup(int width, int height)
{
    mFboA.allocate(width, height, GL_RGBA16F_ARB);
    mFboB.allocate(width, height, GL_RGBA16F_ARB);
    mCurrentFbo = &mFboA;

    mFboA.begin();
    ofBackground(0,255);
    mFboA.end();
    mFboB.begin();
    ofBackground(0,255);
    mFboB.end();
}

void FeedbackTunnel::begin()
{
    GetCurrentFbo()->begin();
    ofBackground(0, 255);

    mRotation += (mTargetRotation - mRotation)*0.02f;

    //float scale = 1.01f;
    float scale = 1;
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(250, 255);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //ofRotate(mRotation);
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    GetOtherFbo()->draw(GetCurrentFbo()->getWidth()/2, GetCurrentFbo()->getHeight()/2,
                        GetOtherFbo()->getWidth()*scale, GetOtherFbo()->getHeight()*scale);
    ofPopMatrix();

}

void FeedbackTunnel::end()
{
    mCurrentFbo->end();

    ofSetRectMode(OF_RECTMODE_CORNER);
    mCurrentFbo->draw(0,0);

    mCurrentFbo = GetOtherFbo();

}

ofFbo *FeedbackTunnel::GetOtherFbo()
{
    if (mCurrentFbo == &mFboA) {
        return &mFboB;
    } else {
        return &mFboA;
    }
}
