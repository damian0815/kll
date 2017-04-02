//
// Created by Damian Stewart on 30/03/2017.
//

#ifndef OFAPP_MIDIRECORDINGAPP_H
#define OFAPP_MIDIRECORDINGAPP_H

#include "ofApp.h"
#include "ofxMidi.h"
#include "kll/Engine/MidiTriggers.h"
#include "3rdparty/readerwriterqueue.h"
#include "3rdparty/picojson.h"

class MidiRecordingApp : public ofApp
{
public:
    void setup  () override ;
    void update () override ;
    void exit   () override ;

private:
    void OnMidiMessageReceived(const void *sender, const ofxMidiMessage &message);
    void WritePendingMessages();

    kll::MidiTriggers mMidiTriggers;

    moodycamel::ReaderWriterQueue<ofxMidiMessage> mMessages;

    picojson::array mMessagesJson;

    picojson::object EncodeJson(ofxMidiMessage message);

    double mLastMidiMessageTime = 0;
};


#endif //OFAPP_MIDIRECORDINGAPP_H
