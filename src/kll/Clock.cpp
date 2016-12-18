//
// Created by Damian Stewart on 15/12/2016.
//

#include <fmt/format.h>
#include "Clock.h"

static kll::Clock* gInstance = nullptr;

kll::Clock *kll::Clock::Get()
{
    if (gInstance == nullptr) {
        gInstance = new Clock();
    }
    return gInstance;
}

void kll::Clock::Setup(MidiTriggers &midiTriggers)
{
    ofAddListener(midiTriggers.GetTickEvent(), this, &kll::Clock::OnTick);
    ofAddListener(midiTriggers.GetTimeResetEvent(), this, &kll::Clock::OnTimeReset);
}

void kll::Clock::OnTick(const int& count)
{
    ++mBeat;
    //fmt::print("* {0}:{1}\n", mBeat/4, GetBeat(4));
    mEightBarPhase = float(GetBeat(8*4)) / (8*4);
}

void kll::Clock::OnTimeReset()
{
    mBeat = 0;
    mEightBarPhase = 0;
}

void kll::Clock::Update(float dt)
{
    float timeForFullPhase = GetTimeForPhase(8*4);
    float phasePerSecond = 1.0f/timeForFullPhase;

    mEightBarPhase += phasePerSecond * dt;
}

float kll::Clock::GetTimeForPhase(int barLength) const
{
    return barLength * GetSecondsPerBeat();
}

float kll::Clock::GetPhase(int barLength)
{
    auto timeForPhase = GetTimeForPhase(barLength);
    auto timeForFullPhase = GetTimeForPhase(8*4);

    auto ratio = timeForPhase/timeForFullPhase;
    auto phase = fmod(mEightBarPhase, ratio);
    return phase/ratio;
}





