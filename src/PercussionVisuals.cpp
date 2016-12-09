//
// Created by Damian Stewart on 09/12/2016.
//

#include <fmt/format.h>
#include "PercussionVisuals.h"

void PercussionVisuals::Draw()
{
    ofSetRectMode(OF_RECTMODE_CENTER);
    if (mDrawSnare) {
        ofSetColor(ofColor::yellow);
        ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, 300, 300);
        mDrawSnare = false;
    }
    if (mDrawKick) {
        ofSetColor(ofColor::blue);
        ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() - 200, 400, 10);
        mDrawKick = false;
    }
    if (mDrawHat) {
        ofSetColor(ofColor::white);
        ofDrawRectangle(ofGetWidth() / 2, 200, 20, 20);
        mDrawHat = false;
    }

}

void PercussionVisuals::OnDrumNote(const void *sender, const MidiTriggers::NoteData &noteData)
{
    if (noteData.pitch == 64) {
        mDrawSnare = true;
    } else if (noteData.pitch == 60) {
        mDrawKick = true;
    } else if (noteData.pitch == 71) {
        mDrawHat = true;
    } else {
        fmt::print("got unhandled drum note {0} {1}\n", noteData.pitch, noteData.velocity);

    }
}
