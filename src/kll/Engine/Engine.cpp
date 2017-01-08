//
// Created by Damian Stewart on 28/12/16.
//



#include "Engine.h"
#include "Clock.h"
#include "LuaHelpers.h"

static const auto SCRIPT_FILE = "lua/testKll.lua";

extern "C" {
    int luaopen_kll(lua_State* l);
}

static kll::Engine* gInstance = nullptr;

kll::Engine::~Engine()
{
    gInstance = nullptr;
}

kll::Engine::Engine()
{
    assert(gInstance == nullptr);
    gInstance = this;
}

kll::Engine* kll::Engine::GetInstance()
{
    return gInstance;
}


void kll::Engine::Setup()
{
    mLua.addListener(this);

    mTriggers.Setup();

    Clock::Get()->Setup(mTriggers);

    mLuaMidiSender.Setup(&mLua, &mTriggers);

    mLuaScriptFolderWatcher.GetChangedEvent().add(this, &Engine::OnLuaScriptFolderChanged, 0);
    mShaderFolderWatcher.GetChangedEvent().add(this, &Engine::OnShaderFolderChanged, 0);

    const bool MAKE_ABSOLUTE = true;
    mShaderFolderWatcher.Setup(ofToDataPath("shaders", MAKE_ABSOLUTE));
    mLuaScriptFolderWatcher.Setup(ofToDataPath("lua", MAKE_ABSOLUTE));

    ReloadLuaScript();
    ReloadShaders();

    ofEnableDepthTest();
}

void kll::Engine::Update(float dt)
{


    mLuaScriptFolderWatcher.Update();
    mShaderFolderWatcher.Update();

    if (mLua.isValid()) {
        CallLuaFunction(&mLua, "update", dt);
    }
    mTriggers.Update();

    kll::Clock::Get()->Update(dt);
    mEnvironment.Update(dt);
}


void kll::Engine::Draw()
{
    float SCREEN_WIDTH = 2;

    float aspectRatio = (float(ofGetHeight())/ofGetWidth());
    float screenHeight = SCREEN_WIDTH * aspectRatio;
    ofSetupScreenPerspective(SCREEN_WIDTH, screenHeight);
    ofTranslate(SCREEN_WIDTH / 2, screenHeight / 2);
    mEnvironment.Draw();
}

void kll::Engine::errorReceived(string &msg)
{
    fmt::print_colored(fmt::Color::RED, "Lua: {0}\n", msg);
}

void kll::Engine::ReloadLuaScript()
{
    mLua.scriptExit();

    mEnvironment.Clear();

    mLua.init(true);
    luaopen_kll(mLua);
    mLua.doScript(SCRIPT_FILE, true);
	mLua.scriptSetup();
}

void kll::Engine::OnLuaScriptFolderChanged(const void *sender, string &fullPath)
{
    fmt::print("Reloading lua script because {0} changed\n", fullPath);
    ReloadLuaScript();
}

void kll::Engine::ReloadShaders()
{
    for (const auto shader: mShaders) {
        shader->Reload();
    }
}

void kll::Engine::OnShaderFolderChanged(const void *sender, string &fullPath)
{
    fmt::print("Reloading shaders because {0} changed\n", fullPath);
    ReloadShaders();
}

void kll::Engine::RegisterShader(kll::Shader *pShader)
{
    auto it = std::find(mShaders.begin(), mShaders.end(), pShader);
    assert(it == mShaders.end());
    mShaders.push_back(pShader);
}

void kll::Engine::UnregisterShader(kll::Shader *pShader)
{
    auto it = std::find(mShaders.begin(), mShaders.end(), pShader);
    assert(it != mShaders.end());
    mShaders.erase(it);
}


