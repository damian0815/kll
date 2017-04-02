#include "ofApp.h"

const bool DO_EXPORT = true;
const float EXPORT_FPS = 60;
const float EXPORT_FRAMESTEP = (1.0f/EXPORT_FPS);
const float EXPORT_TIME_START = 0;
const float EXPORT_TIME_END = 60*3;
const string MIDI_JSON_PATH = "midirecording.json";

void ofApp::setup()
{
    ofSetFrameRate(60);

    ofEnableAlphaBlending();
    mKllEngine.Setup();

    const int NUM_SAMPLES = 16;
    mFbo.allocate(2560, 1440, GL_RGBA, NUM_SAMPLES);
    if (DO_EXPORT) {
        mMidiPlayer.Setup(mKllEngine.GetMidiTriggers(), MIDI_JSON_PATH);
        mMidiPlayer.JumpToTime(EXPORT_TIME_START);
    }

}

void ofApp::update()
{
    auto dt = (DO_EXPORT ? EXPORT_FRAMESTEP : ofGetLastFrameTime());

    if (DO_EXPORT) {
        mMidiPlayer.Update(dt);
        if (mMidiPlayer.GetCurrentTime() > EXPORT_TIME_END) {
            ofExit();
        }
    }

    mKllEngine.Update(dt);


}

void ofApp::draw()
{
    mFbo.begin();
    ofBackground(0);
    ofSetColor(255);
    mKllEngine.Draw(mFbo.getWidth(), mFbo.getHeight());
    mFbo.end();

    mFbo.draw(0,0, ofGetWidth(), ofGetHeight());
    if (DO_EXPORT) {
        mFbo.readToPixels(mFboPixels);
        mFboPixels.resize(mFbo.getWidth()/2, mFbo.getHeight()/2, OF_INTERPOLATE_BICUBIC);
        char filename[2048];
        sprintf(filename, "export/%08li.png", long(ofGetFrameNum()));
        ofSaveImage(mFboPixels, filename);
    }

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
    fmt::print("window at ({0},{1})\n", ofGetWindowPositionX(), ofGetWindowPositionY());
}

void ofApp::dragged(ofDragInfo& dragged)
{
}

void ofApp::messageReceived(ofMessage& message)
{
}

bool ofApp::GetIsRetina()
{
    auto glfwWindow = dynamic_cast<ofAppGLFWWindow*>(ofGetWindowPtr());
    int glfwWidth=0, glfwHeight=0;
    if (glfwWindow != nullptr) {
        glfwGetFramebufferSize(glfwWindow->getGLFWWindow(), &glfwWidth, &glfwHeight);
    }
    fmt::print("retina check: of {0}x{1}, vp {2}x{3}, fb = {4}x{5}\n", ofGetWidth(), ofGetHeight(), ofGetViewportWidth(), ofGetViewportHeight(), glfwWidth, glfwHeight);
    return (glfwHeight == ofGetHeight());
}

