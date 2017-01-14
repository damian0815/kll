//
// Created by Damian Stewart on 28/12/16.
//

#ifndef OFAPP_LUAMIDISENDER_H
#define OFAPP_LUAMIDISENDER_H

#include "ofxLua.h"
#include "MidiTriggers.h"

namespace kll {

    class LuaMidiSender
    {
    public:
        void Setup(ofxLua *lua, MidiTriggers *triggers);

    private:

        void OnMidiNoteOn(const void *sender, const MidiTriggers::NoteData &noteData);
        void OnMidiNoteOff(const void *sender, const MidiTriggers::NoteData &noteData);

        ofxLua* mLua;
    };

}

#endif //OFAPP_LUAMIDISENDER_H
