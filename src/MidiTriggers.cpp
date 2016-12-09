//
// Created by Damian Stewart on 09/12/2016.
//

#include "MidiTriggers.h"
#include <fmt/ostream.h>

static const char *const OFSYNC_PORT_NAME = "of sync";

void MidiTriggers::Setup()
{
    mSyncInput.addListener(this);
    mSyncInput.openVirtualPort(OFSYNC_PORT_NAME);

}

void MidiTriggers::newMidiMessage(ofxMidiMessage &message)
{
    if (message.portName == OFSYNC_PORT_NAME) {
        if (message.status == MIDI_NOTE_ON) {
            if (message.channel == 1) {
                fmt::print("Sync: {0}\n", message.pitch);
                if (message.pitch == 71) {
                    mTickCount = 0;
                    RaiseTimeReset();
                } else if (message.pitch == 72) {
                    RaiseTick();
                    ++mTickCount;
                }
            } else {
                RaiseNoteOn(message);
            }
        } else if (message.status == MIDI_NOTE_OFF) {
            // do nothing
        } else {
            fmt::print("Sync: {0}\n", message.toString());
        }
    }

}

void MidiTriggers::RaiseNoteOn(const ofxMidiMessage &message)
{
    mNoteOnEvents[message.channel].notify(this, {message.pitch, message.velocity});
}

