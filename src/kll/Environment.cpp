//
// Created by Damian Stewart on 10/12/2016.
//

#include <set>
#include "Environment.h"
#include "Object.h"
#include "Behaviours/Behaviour.h"

using std::set;

namespace kll
{
    Block * Environment::AddBlock(vec3 initialPos, vec3 dimensions)
    {
        auto block = new Block(initialPos, dimensions);
        AddObject(block);
        return block;
    }

    void Environment::AddObject(Object *o)
    {
        mObjects.push_back(o);
    }

    void Environment::Draw()
    {
        for (auto& o: mObjects) {
            o->Draw();
        }

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
            auto it = std::find(mObjects.begin(), mObjects.end(), o);
            assert(it != mObjects.end());
            //fmt::print("erasing object at index {0}\n", it - mObjects.begin());

            delete *it;
            mObjects.erase(it);

            auto& behaviours = mBehaviours[o];
            for (auto b: behaviours) {
                delete b;
            }
            mBehaviours.erase(o);
        }
    }

    void Environment::AttachBehaviour(Object *target, Behaviour *behaviour)
    {
        mBehaviours[target].push_back(behaviour);
    }

}