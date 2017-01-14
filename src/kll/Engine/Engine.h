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
        Engine();
        virtual ~Engine();

        static Engine* GetInstance();

        void Setup();
        void Update(float dt);
        void Draw();

        void RegisterShader(Shader *pShader);
        void UnregisterShader(Shader *pShader);

        void SetIsRetina(bool r) { mIsRetina = r; }

    private:
        void ReloadLuaScript();
        void ReloadShaders();

        void errorReceived(string &msg) override;

        void OnLuaScriptFolderChanged(const void *sender, string &fullPath);
        void OnShaderFolderChanged(const void *sender, string &fullPath);

        ofVec3f GetCameraPositionFromOfModelViewMatrix() const;

        MidiTriggers mTriggers;
        Environment mEnvironment;
        ofxLua mLua;

        vector<Shader*> mShaders;

        LuaMidiSender mLuaMidiSender;

        FolderWatcher mLuaScriptFolderWatcher;
        FolderWatcher mShaderFolderWatcher;

        bool mIsRetina;

    };
}


#endif //OFAPP_ENGINE_H
