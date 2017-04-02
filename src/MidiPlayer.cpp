//
// Created by Damian Stewart on 30/03/2017.
//

#include "MidiPlayer.h"

void MidiPlayer::Setup(kll::MidiTriggers *midiTriggers, const std::string &path)
{
    mMidiTriggers = midiTriggers;

    ifstream inFile;
    inFile.open(ofToDataPath(path));
    picojson::value v;
    inFile >> v;
    inFile.close();

    mMessages = v.get<picojson::array>();
    ResetTime();
}

void MidiPlayer::Update(double dt)
{
    mCurrentTime += dt;
    while (mCurrentArrayIndex < mMessages.size()) {
        auto nextMessage = DecodeJson(mMessages[mCurrentArrayIndex]);

        auto thisDt = nextMessage.deltatime / 1000.0;
        if ((mCurrentArrayTime + thisDt) > mCurrentTime) {
            break;
        }

        ++mCurrentArrayIndex;
        mCurrentArrayTime += thisDt;
        mMidiTriggers->InjectMidiMessage(nextMessage);

    }
}

void MidiPlayer::ResetTime()
{
    mCurrentTime = 0;
    mCurrentArrayIndex = 0;

}

ofxMidiMessage MidiPlayer::DecodeJson(picojson::value &value)
{
    /*
    o["deltatime"] = picojson::value(message.deltatime);
    o["portNum"] = picojson::value(double(message.portNum));
    o["portName"] = picojson::value(message.portName);

    picojson::array a;
    for (const auto b: message.bytes) {
        a.push_back(picojson::value(double(b)));
    }
    o["message"] = picojson::value(a);*/

    auto o = value.get<picojson::object>();

    auto bytes = DecodeMessageBytes(o["message"]);
    ofxMidiMessage m = ofxBaseMidiIn::buildMidiMessageFromBytes(&bytes);

    m.deltatime = o["deltatime"].get<double>();
    m.portNum = int(o["portNum"].get<double>());
    m.portName = o["portName"].get<string>();

    return m;
}

vector<unsigned char> MidiPlayer::DecodeMessageBytes(const picojson::value &value)
{
    vector<unsigned char> bytes;
    auto arrayj = value.get<picojson::array>();
    for (auto bj: arrayj) {
        auto byte = bj.get<double>();
        bytes.push_back(byte);
    }
    return bytes;
}

void MidiPlayer::JumpToTime(const float t)
{
    mCurrentTime = t;
}
