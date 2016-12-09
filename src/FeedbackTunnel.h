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

private:
    ofFbo mFboA, mFboB;
    ofFbo* mCurrentFbo;

    ofFbo *GetCurrentFbo() { return mCurrentFbo; }
    ofFbo *GetOtherFbo();
};


#endif //OFAPP_FEEDBACKTUNNEL_H
