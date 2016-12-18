//
// Created by Damian Stewart on 09/12/2016.
//

#include <fmt/format.h>
#include "PercussionVisuals.h"
#include "Behaviours/ImplodeBehaviour.h"
#include "Behaviours/FallBehaviour.h"
#include "Behaviours/AddRotationBehaviour.h"
#include "Environment.h"
#include "Clock.h"

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

    }

    void PercussionVisuals::OnDrumNote(const void *sender, const MidiTriggers::NoteData &noteData)
    {
        if (noteData.pitch == 64) {
            mDrawSnare = true;
        } else if (noteData.pitch == 60) {
            // kick
            auto block = mEnvironment->AddBlock(vec3(0, 0.5f, 0), vec3(1.0, 0.03, 0.03));
            mEnvironment->AttachBehaviour(block, new ImplodeBehaviour(block, vec3(1,0,0)));
            mEnvironment->AttachBehaviour(block, new FallBehaviour(block, vec3(0, 3, 0)));
            mEnvironment->AttachBehaviour(block, new AddRotationBehaviour(block, vec3(0, 3, 0)));

        } else if (noteData.pitch == 71) {
            // hihat
            auto phase = Clock::Get()->GetPhase(8);
            vec3 center(0.5f*cosf(float(phase*M_PI*2)), -0.3, 0.0);
            auto block = mEnvironment->AddBlock(center, vec3(0.1, 0.01, 0.01));

            const vec3 screenCenter(0,0,0);
            auto towardsCenter = glm::normalize(screenCenter - center);
            mEnvironment->AttachBehaviour(block, new FallBehaviour(block, -towardsCenter*4.0f));
        } else {
            fmt::print("got unhandled drum note {0} {1}\n", noteData.pitch, noteData.velocity);

        }
    }

}
