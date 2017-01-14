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
        triggers->GetNoteOnEvent(channel).add(this, &kll::LuaMidiSender::OnMidiNoteOn, 0);
        triggers->GetNoteOffEvent(channel).add(this, &kll::LuaMidiSender::OnMidiNoteOff, 0);
    }
}


void kll::LuaMidiSender::OnMidiNoteOn(const void *sender, const MidiTriggers::NoteData &noteData)
{
    const auto FUNCTION_NAME = "OnMidiNoteOn";
    CallLuaFunction(mLua, FUNCTION_NAME, noteData.channel, noteData.pitch, noteData.velocity);
}

void kll::LuaMidiSender::OnMidiNoteOff(const void *sender, const MidiTriggers::NoteData &noteData)
{
    const auto FUNCTION_NAME = "OnMidiNoteOff";
    CallLuaFunction(mLua, FUNCTION_NAME, noteData.channel, noteData.pitch, noteData.velocity);
}