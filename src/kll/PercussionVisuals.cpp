//
// Created by Damian Stewart on 09/12/2016.
//

#include <fmt/format.h>
#include "PercussionVisuals.h"
#include "ImplodeBehaviour.h"
#include "FallBehaviour.h"
#include "Environment.h"

using glm::vec3;

namespace kll
{

    void PercussionVisuals::Draw()
    {
        ofSetRectMode(OF_RECTMODE_CENTER);
        if (mDrawSnare) {
            ofSetColor(ofColor::lightGrey);
            ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, 1500, 150);
            mDrawSnare = false;
        }
        if (mDrawKick) {
            ofSetColor(ofColor::white, 255);
            ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() - 200, 400, 100);
            mDrawKick = false;
        }
        if (mDrawHat) {
            ofSetColor(ofColor::lightSlateGray);
            ofDrawRectangle(ofGetWidth() / 2, 200, 100, 5);
            mDrawHat = false;
        }

    }

    void PercussionVisuals::OnDrumNote(const void *sender, const MidiTriggers::NoteData &noteData)
    {
        if (noteData.pitch == 64) {
            mDrawSnare = true;
        } else if (noteData.pitch == 60) {
            auto block = mEnvironment->AddBlock(vec3(0, 0.4f, 0), vec3(1, 0.02, 0.02));
            mEnvironment->AttachBehaviour(block, std::make_shared<ImplodeBehaviour>(block, vec3(1,0,0)));
            mEnvironment->AttachBehaviour(block, std::make_shared<FallBehaviour>(block));
            mDrawKick = true;
        } else if (noteData.pitch == 71) {
            mDrawHat = true;
        } else {
            fmt::print("got unhandled drum note {0} {1}\n", noteData.pitch, noteData.velocity);

        }
    }
}
