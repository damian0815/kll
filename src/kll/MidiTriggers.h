//
// Created by Damian Stewart on 09/12/2016.
//

#ifndef OFAPP_MIDITRIGGERS_H
#define OFAPP_MIDITRIGGERS_H

#include "ofMain.h"
#include "ofxMidiIn.h"
#include "ofxMidiMessage.h"

namespace kll
{

    class MidiTriggers : public ofxMidiListener
    {
    public:
        void Setup();

        ofEvent<void> &GetTimeResetEvent()
        { return mTimeResetEvent; }

        ofEvent<const int> &GetTickEvent()
        { return mTickEvent; }

        struct NoteData
        {
            int channel;
            int pitch;
            int velocity;
        };

        ofEvent<const NoteData &> &GetNoteOnEvent(int channel)
        { return mNoteOnEvents[channel]; }

    private:
        void newMidiMessage(ofxMidiMessage &message) override;

        void RaiseTimeReset()
        { mTimeResetEvent.notify(this); }

        void RaiseTick()
        { mTickEvent.notify(this, mTickCount); }

        void RaiseNoteOn(const ofxMidiMessage &message);

        int mTickCount = 0;

        ofEvent<void> mTimeResetEvent;
        ofEvent<const int> mTickEvent;

        ofxMidiIn mSyncInput;

        ofEvent<const NoteData &> mNoteOnEvents[17];
    };

}

#endif //OFAPP_MIDITRIGGERS_H
