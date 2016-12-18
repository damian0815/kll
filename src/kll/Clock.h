//
// Created by Damian Stewart on 15/12/2016.
//

#ifndef OFAPP_CLOCK_H
#define OFAPP_CLOCK_H

#include "../MidiTriggers.h"

namespace kll
{

    class Clock
    {

    public:
        static Clock* Get();

        void Setup(MidiTriggers& midiTriggers);

        int GetBeat(int barLength = 4) { return mBeat % barLength; }

        void Update(float dt);

        float GetPhase(int barLength = 4);

    private:
        void OnTick(const int& count);
        void OnTimeReset();

        float GetTimeForPhase(int barLenght) const;
        float GetSecondsPerBeat() const { return float(60.0f / this->mBpm); }

        int mBpm = 132;
        int mBeat = 0;

        float mEightBarPhase = 0;

    };

}

#endif //OFAPP_CLOCK_H
