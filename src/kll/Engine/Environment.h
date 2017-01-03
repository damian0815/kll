//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_ENVIRONMENT_H
#define OFAPP_ENVIRONMENT_H

#include "../kll.h"
#include <map>
#include "../Block.h"
#include "gvec3.h"
#include "BehaviourPool.h"

using std::map;

namespace kll
{
    class Object;
    class Behaviour;

    class Environment
    {
    public:
        Environment() { assert(mInstance == nullptr); mInstance = this; }
        static Environment* GetInstance() { return mInstance; }

        bool HasObject(Object *o) { return std::find(mObjects.begin(), mObjects.end(), o) != mObjects.end(); }
        void AddObject(Object *o);

        void RemoveObject(Object *o);

        void AttachBehaviour(Object *target, Behaviour *behaviour);

        void Draw();
        void Update(float dt);

        kll::Block * AddBlock(kll::gvec3 initialPos, kll::gvec3 dimensions);

        void PrintHello() { fmt::print("hello!\n"); }

        kll::BehaviourPool* GetBehaviourPool() { return &mBehaviourPool; }

        void Clear();

    private:

        vector<Object*> mObjects;
        map<Object*, vector<Behaviour*>> mBehaviours;

        BehaviourPool mBehaviourPool;

        static Environment *mInstance;

    };

}


#endif //OFAPP_ENVIRONMENT_H
