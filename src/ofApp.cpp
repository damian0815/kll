#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(60);
    mFeedbackTunnel.setup(ofGetWidth(), ofGetHeight());

    mTriggers.Setup();
    mTriggers.GetTickEvent().add(this, &ofApp::OnTick, 0);

    mTriggers.GetNoteOnEvent(2).add(&mPercussionVisuals, &PercussionVisuals::OnDrumNote, 0);
}

void ofApp::update()
{
}

void ofApp::draw()
{
    mFeedbackTunnel.begin();

    if (mShouldDrawTick) {
        ofDrawCircle(20, 20, 10);
        mShouldDrawTick = false;
    }

    mPercussionVisuals.Draw();

    mFeedbackTunnel.end();
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
}

