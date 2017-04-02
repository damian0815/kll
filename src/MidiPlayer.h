//
// Created by Damian Stewart on 30/03/2017.
//

#ifndef OFAPP_MIDIPLAYER_H
#define OFAPP_MIDIPLAYER_H

#include <string>
#include "3rdparty/picojson.h"
#include "kll/Engine/MidiTriggers.h"

class MidiPlayer
{
public:
    void Setup(kll::MidiTriggers *midiTriggers, const std::string &path);

    void Update(double dt);
    void ResetTime();

    double GetCurrentTime() { return mCurrentTime; }

    void JumpToTime(const float t);

private:

    picojson::array mMessages;
    double mCurrentArrayTime;
    double mCurrentArrayIndex;
    double mCurrentTime;

    kll::MidiTriggers* mMidiTriggers;

    ofxMidiMessage DecodeJson(picojson::value &value);

    vector<unsigned char> DecodeMessageBytes(const picojson::value &value);
};


#endif //OFAPP_MIDIPLAYER_H
