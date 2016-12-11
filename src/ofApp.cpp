#include "ofApp.h"

ofApp::ofApp()
: ofBaseApp(), mPercussionVisuals(&mEnvironment)
{
}

void ofApp::setup()
{
    ofSetFrameRate(60);
    mFeedbackTunnel.setup(ofGetWidth(), ofGetHeight());

    mTriggers.Setup();
    mTriggers.GetTickEvent().add(this, &ofApp::OnTick, 0);

    mTriggers.GetNoteOnEvent(2).add(&mPercussionVisuals, &kll::PercussionVisuals::OnDrumNote, 0);
}

void ofApp::update()
{
    float dt = ofGetLastFrameTime();
    mEnvironment.Update(dt);
}

void ofApp::draw()
{
    ofBackground(0);
    /*
    ofSetupScreen();
    mFeedbackTunnel.begin();

    if (mShouldDrawTick) {
        ofDrawCircle(20, 20, 10);
        mShouldDrawTick = false;
    }

    mPercussionVisuals.Draw();

    mFeedbackTunnel.end();*/

    static float SCREEN_WIDTH = 2;
    float aspectRatio = (float(ofGetHeight())/ofGetWidth());
    float screenHeight = SCREEN_WIDTH * aspectRatio;
    ofSetupScreenPerspective(SCREEN_WIDTH, SCREEN_WIDTH * screenHeight);
    ofTranslate(SCREEN_WIDTH/2, screenHeight/2);
    mEnvironment.Draw();

}

void ofApp::exit()
{
}

void ofApp::keyPressed(ofKeyEventArgs& key)
{
}

void ofApp::keyReleased(ofKeyEventArgs& key)
{
}

void ofApp::mouseMoved(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseDragged(ofMouseEventArgs& mouse)
{
}

void ofApp::mousePressed(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseReleased(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseScrolled(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseEntered(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseExited(ofMouseEventArgs& mouse)
{
}

void ofApp::touchDown(ofTouchEventArgs& touch)
{
}

void ofApp::touchMoved(ofTouchEventArgs& touch)
{
}

void ofApp::touchUp(ofTouchEventArgs& touch)
{
}

void ofApp::touchDoubleTap(ofTouchEventArgs& touch)
{
}

void ofApp::touchCancelled(ofTouchEventArgs& touch)
{
}

void ofApp::windowResized(ofResizeEventArgs& window)
{
}

void ofApp::dragged(ofDragInfo& dragged)
{
}

void ofApp::messageReceived(ofMessage& message)
{
}

void ofApp::OnTick(const void *sender, const int &tickCount)
{
    mShouldDrawTick = true;
    if ((tickCount % 8) == 0) {
        mFeedbackTunnel.switchRotationDirection();
    }
}

