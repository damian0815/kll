//
// Created by Damian Stewart on 28/12/16.
//



#include "Engine.h"
#include "../PercussionVisuals.h"
#include "Clock.h"

static const auto SCRIPT_FILE = "testKll.lua";

extern "C" {
    int luaopen_kll(lua_State* l);
}

void kll::Engine::Setup()
{
    mLua.addListener(this);

    mTriggers.Setup();
    mTriggers.GetNoteOnEvent(2).add(&mPercussionVisuals, &PercussionVisuals::OnDrumNote, 0);

    Clock::Get()->Setup(mTriggers);

    mLuaMidiSender.Setup(&mLua, &mTriggers);

    ReloadLuaScript();
}

void kll::Engine::Update(float dt)
{
    mLua.scriptUpdate();
    kll::Clock::Get()->Update(dt);
    mEnvironment.Update(dt);
}

void kll::Engine::Draw()
{
    static float SCREEN_WIDTH = 2;
    float aspectRatio = (float(ofGetHeight())/ofGetWidth());
    float screenHeight = SCREEN_WIDTH * aspectRatio;
    ofSetupScreenPerspective(SCREEN_WIDTH, SCREEN_WIDTH * screenHeight);
    ofTranslate(SCREEN_WIDTH/2, screenHeight/2);
    mEnvironment.Draw();
}

void kll::Engine::errorReceived(string &msg)
{
    fmt::print_colored(fmt::Color::RED, "Lua: {0}\n", msg);
}

void kll::Engine::ReloadLuaScript()
{
    mLua.scriptExit();
    mLua.init(true);
    luaopen_kll(mLua);
    mLua.doScript(SCRIPT_FILE, true);
	mLua.scriptSetup();
}
