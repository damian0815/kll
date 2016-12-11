#pragma once

#include "ofMain.h"
#include "MidiTriggers.h"
#include "FeedbackTunnel.h"
#include "kll/PercussionVisuals.h"
#include "kll/Environment.h"

class ofApp : public ofBaseApp
{
  public:
    ofApp();

    void setup  ();
    void update ();
    void draw   ();
    void exit   ();

    void keyPressed      (ofKeyEventArgs&);
    void keyReleased     (ofKeyEventArgs&);

    void mouseMoved      (ofMouseEventArgs&);
    void mouseDragged    (ofMouseEventArgs&);
    void mousePressed    (ofMouseEventArgs&);
    void mouseReleased   (ofMouseEventArgs&);
    void mouseScrolled   (ofMouseEventArgs&);
    void mouseEntered    (ofMouseEventArgs&);
    void mouseExited     (ofMouseEventArgs&);

    void touchDown       (ofTouchEventArgs&);
    void touchMoved      (ofTouchEventArgs&);
    void touchUp         (ofTouchEventArgs&);
    void touchDoubleTap  (ofTouchEventArgs&);
    void touchCancelled  (ofTouchEventArgs&);

    void windowResized   (ofResizeEventArgs&);
    void dragged         (ofDragInfo&);
    void messageReceived (ofMessage&);

    void OnTick(const void *sender, const int &tickCount);


    MidiTriggers mTriggers;
    FeedbackTunnel mFeedbackTunnel;

    kll::Environment mEnvironment;
    kll::PercussionVisuals mPercussionVisuals;

    bool mShouldDrawTick = false;


};
