#pragma once

#include "ofMain.h"
#include "kll/Engine/Engine.h"

class ofApp : public ofBaseApp
{
  public:

    void setup  () override ;
    void update () override ;
    void draw   () override ;
    void exit   () override ;

    void keyPressed      (ofKeyEventArgs&) override ;
    void keyReleased     (ofKeyEventArgs&) override ;

    void mouseMoved      (ofMouseEventArgs&) override ;
    void mouseDragged    (ofMouseEventArgs&) override ;
    void mousePressed    (ofMouseEventArgs&) override ;
    void mouseReleased   (ofMouseEventArgs&) override ;
    void mouseScrolled   (ofMouseEventArgs&) override ;
    void mouseEntered    (ofMouseEventArgs&) override ;
    void mouseExited     (ofMouseEventArgs&) override ;

    void touchDown       (ofTouchEventArgs&) override ;
    void touchMoved      (ofTouchEventArgs&) override ;
    void touchUp         (ofTouchEventArgs&) override ;
    void touchDoubleTap  (ofTouchEventArgs&) override ;
    void touchCancelled  (ofTouchEventArgs&) override ;

    void windowResized   (ofResizeEventArgs&) override ;
    void dragged         (ofDragInfo&) override ;
    void messageReceived (ofMessage&) override ;


    kll::Engine mKllEngine;


    bool mInitialIsRetina;
    float mInitialWidth, mInitialHeight;
    bool GetIsRetina();

    bool mWasRetina;
};
