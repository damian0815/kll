//
// Created by Damian Stewart on 09/12/2016.
//

#ifndef OFAPP_FEEDBACKTUNNEL_H
#define OFAPP_FEEDBACKTUNNEL_H

#include "ofMain.h"

class FeedbackTunnel
{
public:
    void setup(int width, int height);

    void begin();
    void end();
    void switchRotationDirection() { mTargetRotation = -mTargetRotation; }

private:
    ofFbo mFboA, mFboB;
    ofFbo* mCurrentFbo = nullptr;
    float mRotation = 0;
    float mTargetRotation = 1;

    ofFbo *GetCurrentFbo() { return mCurrentFbo; }
    ofFbo *GetOtherFbo();
};


#endif //OFAPP_FEEDBACKTUNNEL_H
