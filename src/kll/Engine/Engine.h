//
// Created by Damian Stewart on 28/12/16.
//

#ifndef OFAPP_ENGINE_H
#define OFAPP_ENGINE_H


#include "ofxLua.h"
#include "Environment.h"
#include "MidiTriggers.h"
#include "LuaMidiSender.h"
#include "FolderWatcher.h"

namespace kll
{
    class Engine : public ofxLuaListener
    {
    public:
        void Setup();
        void Update(float dt);
        void Draw();

    private:
        void ReloadLuaScript();

        void errorReceived(string &msg) override;
        void OnLuaScriptFolderChanged(const void *sender, string &fullPath);

        MidiTriggers mTriggers;
        Environment mEnvironment;
        ofxLua mLua;

        LuaMidiSender mLuaMidiSender;

        FolderWatcher mLuaScriptFolderWatcher;


    };
}


#endif //OFAPP_ENGINE_H
