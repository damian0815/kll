//
// Created by Damian Stewart on 28/12/16.
//

#include <fmt/format.h>
#include "LuaMidiSender.h"

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
    if (!mLua->isFunction(FUNCTION_NAME)) {
        fmt::print("Missing OnMidiNote(channel,pitch,velocity) function\n");
        return;
    }

    lua_getglobal(*mLua, FUNCTION_NAME);
    lua_pushinteger(*mLua, noteData.channel);
    lua_pushinteger(*mLua, noteData.pitch);
    lua_pushinteger(*mLua, noteData.velocity);

    auto result = lua_pcall(*mLua, 3, 0, 0);
    if (result != 0) {
        fmt::print_colored(fmt::Color::RED, "Error calling {0}: {1}\n", FUNCTION_NAME, (string)lua_tostring(*mLua, -1));
    }

}
