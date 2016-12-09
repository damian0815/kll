//
// Created by Damian Stewart on 09/12/2016.
//

#ifndef OFAPP_PERCUSSIONVISUALS_H
#define OFAPP_PERCUSSIONVISUALS_H


#include "MidiTriggers.h"

class PercussionVisuals
{
public:
    void OnDrumNote(const void* sender, const MidiTriggers::NoteData& noteData);

    void Draw();

private:
    bool mDrawSnare = false;
    bool mDrawKick = false;
    bool mDrawHat = false;
};


#endif //OFAPP_PERCUSSIONVISUALS_H
