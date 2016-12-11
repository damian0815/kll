//
// Created by Damian Stewart on 09/12/2016.
//

#ifndef OFAPP_PERCUSSIONVISUALS_H
#define OFAPP_PERCUSSIONVISUALS_H


#include "../MidiTriggers.h"
#include "Environment.h"


namespace kll
{
    class PercussionVisuals
    {
    public:
        PercussionVisuals(Environment *environment): mEnvironment(environment) {}

        void OnDrumNote(const void *sender, const MidiTriggers::NoteData &noteData);

        void Draw();


    private:
        Environment *mEnvironment;

        bool mDrawSnare = false;
        bool mDrawKick = false;
        bool mDrawHat = false;

    };

}

#endif //OFAPP_PERCUSSIONVISUALS_H
