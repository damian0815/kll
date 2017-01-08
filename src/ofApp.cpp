#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(60);

    ofEnableAlphaBlending();
    mKllEngine.Setup();
}

void ofApp::update()
{
    mKllEngine.Update(ofGetLastFrameTime());
}

void ofApp::draw()
{
    ofBackground(0);
    ofSetColor(255);
    mKllEngine.Draw();
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

