//
// Created by Damian Stewart on 28/12/16.
//

#include <fmt/format.h>
#include "LuaMidiSender.h"
#include "LuaHelpers.h"

void kll::LuaMidiSender::Setup(ofxLua *lua, MidiTriggers *triggers)
{
    mLua = lua;

    for (int channel=1; channel<=16; channel++) {
        triggers->GetNoteOnEvent(channel).add(this, &kll::LuaMidiSender::OnMidiNote, 0);
    }
}


void kll::LuaMidiSender::OnMidiNote(const void *sender, const MidiTriggers::NoteData &noteData)
{
    const auto FUNCTION_NAME = "OnMidiNote";
    CallLuaFunction(mLua, FUNCTION_NAME, noteData.channel, noteData.pitch, noteData.velocity);
}
