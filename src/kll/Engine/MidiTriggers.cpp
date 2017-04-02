//
// Created by Damian Stewart on 09/12/2016.
//

#include "MidiTriggers.h"
#include <fmt/ostream.h>

namespace kll
{

    static const char *const OFSYNC_PORT_NAME = "of sync";

    void MidiTriggers::Setup()
    {
        mSyncInput.addListener(this);
        mSyncInput.openVirtualPort(OFSYNC_PORT_NAME);

    }

    void MidiTriggers::Update()
    {
        ProcessReceivedMessages();
    }

    void MidiTriggers::newMidiMessage(ofxMidiMessage &message)
    {
        mReceivedMessagesMutex.lock();
        mReceivedMessages.push_back(message);
        RaiseMessageReceived(message);
        mReceivedMessagesMutex.unlock();
    }

    void MidiTriggers::ProcessReceivedMessages()
    {
        mReceivedMessagesMutex.lock();

        for (auto& message: mReceivedMessages) {
            if (message.portName == OFSYNC_PORT_NAME) {
                if (message.status == MIDI_NOTE_ON) {
                    if (message.channel == 1) {
                        //fmt::print("Sync: {0}\n", message.pitch);
                        if (message.pitch == 71) {
                            mTickCount = 0;
                            RaiseTimeReset();
                        } else if (message.pitch == 72) {
                            RaiseTick();
                            ++mTickCount;
                        }
                    }

                    RaiseNoteOn(message);
                } else if (message.status == MIDI_NOTE_OFF) {
                    RaiseNoteOff(message);
                } else {
                    fmt::print("Sync: {0}\n", message.toString());
                }
            }
        }
        mReceivedMessages.clear();

        mReceivedMessagesMutex.unlock();

    }

    void MidiTriggers::RaiseNoteOn(const ofxMidiMessage &message)
    {
        mNoteOnEvents[message.channel].notify(this, {message.channel, message.pitch, message.velocity});
    }

    void MidiTriggers::RaiseNoteOff(const ofxMidiMessage &message)
    {
        mNoteOffEvents[message.channel].notify(this, {message.channel, message.pitch, message.velocity});
    }

    void MidiTriggers::InjectMidiMessage(ofxMidiMessage message)
    {
        newMidiMessage(message);
    }
}