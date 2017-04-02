//
// Created by Damian Stewart on 30/03/2017.
//

#include "MidiRecordingApp.h"

void MidiRecordingApp::setup()
{
    mMidiTriggers.Setup();
    mMidiTriggers.GetRawMessageReceivedEvent().add(this, &MidiRecordingApp::OnMidiMessageReceived, 0);


}

void MidiRecordingApp::exit()
{
    WritePendingMessages();

    std::ofstream outFile;
    char path[2048] = "/tmp/midirecording.XXXXXX";
    mktemp(path);
    cout << "writing to " << path << endl;
    outFile.open(path);
    outFile << picojson::value(mMessagesJson);
    outFile.close();

}

void MidiRecordingApp::OnMidiMessageReceived(const void *sender, const ofxMidiMessage &message)
{
    auto messageCopy = message;
    auto now = ofGetElapsedTimef();
    messageCopy.deltatime = 1000 * (now - mLastMidiMessageTime);
    mLastMidiMessageTime = now;
    mMessages.enqueue(messageCopy);
}

void MidiRecordingApp::update()
{
    WritePendingMessages();
}

void MidiRecordingApp::WritePendingMessages()
{
    ofxMidiMessage m;
    while (mMessages.try_dequeue(m)) {
        auto o = EncodeJson(m);
        mMessagesJson.push_back(picojson::value(o));
    }
}

picojson::object MidiRecordingApp::EncodeJson(ofxMidiMessage message)
{
    picojson::object o;
    o["deltatime"] = picojson::value(message.deltatime);
    o["portNum"] = picojson::value(double(message.portNum));
    o["portName"] = picojson::value(message.portName);

    picojson::array a;
    for (const auto b: message.bytes) {
        a.push_back(picojson::value(double(b)));
    }
    o["message"] = picojson::value(a);

    return o;
}
