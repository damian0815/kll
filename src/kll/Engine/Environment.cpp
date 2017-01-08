//
// Created by Damian Stewart on 10/12/2016.
//

#include <set>
#include "Environment.h"
#include "../Behaviours/Behaviour.h"

using std::set;

namespace kll
{
    Environment* Environment::mInstance = nullptr;

    Environment::Environment()
    {
        assert(mInstance == nullptr);
        mInstance = this;

    }

    Block * Environment::AddBlock(kll::gvec3 initialPos, kll::gvec3 dimensions)
    {
        auto block = new Block(initialPos, dimensions);
        AddObject(block);
        return block;
    }

    kll::TunnelSection *Environment::AddTunnelSection(float length, float radius, int segments, int slices)
    {
        auto section = new TunnelSection(length, radius, segments, slices);
        AddObject(section);
        return section;
    }

    void Environment::AddObject(Object *o)
    {
        mObjects.push_back(o);
    }

    void Environment::Draw()
    {
        mLight.Enable();
        for (auto& o: mObjects) {
            o->Draw();
        }
        mLight.Disable();
    }

    void Environment::Update(float dt)
    {
       set<Object*> objectsToDestroy;

        for (auto& o: mObjects) {
            o->Update(dt);
            if (mBehaviours.count(o)) {
                auto& behaviours = mBehaviours[o];
                for (auto b: behaviours) {
                    b->Update(dt);
                }

                if (std::any_of(behaviours.begin(), behaviours.end(), [](auto b) {
                    return b->ShouldObjectBeDestroyed();
                })) {
                    objectsToDestroy.insert(o);
                }
            }
        }

        for (auto o: objectsToDestroy) {
            RemoveObject(o);
        }
    }

    void Environment::RemoveObject(Object *o)
    {
        auto it = find(mObjects.begin(), mObjects.end(), o);
        assert(it != mObjects.end());
        //fmt::print("erasing object at index {0} ({1} remain)\n", it - mObjects.begin(), mObjects.size());
        mObjects.erase(it);

        auto& behaviours = mBehaviours[o];
        for (auto b: behaviours) {
            mBehaviourPool.GiveBackBehaviour(b);
        }
        mBehaviours.erase(o);

        delete o;
    }

    void Environment::AttachBehaviour(Object *target, Behaviour *behaviour)
    {
        mBehaviours[target].push_back(behaviour);
    }

    void Environment::Clear()
    {
        for (int i=mObjects.size()-1; i>=0; i--) {
            RemoveObject(mObjects[i]);
        }

    }



}