//
// Created by Damian Stewart on 10/12/2016.
//

#include <set>
#include "Environment.h"
#include "Object.h"
#include "Behaviour.h"

using std::set;

namespace kll
{
    Block * Environment::AddBlock(vec3 initialPos, vec3 dimensions)
    {
        auto block = std::make_shared<Block>(initialPos, dimensions);
        AddObject(block);
        return block.get();
    }

    void Environment::AddObject(shared_ptr<Object> o)
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
            if (mBehaviours.count(o.get())) {
                auto behaviours = mBehaviours[o.get()];
                for (auto &b: behaviours) {
                    b->Update(dt);
                }

                if (std::any_of(behaviours.begin(), behaviours.end(), [](auto b) {
                    return b->ShouldObjectBeDestroyed();
                })) {
                    //fmt::print("will remove object {0}\n", (void*)o.get());
                    objectsToDestroy.insert(o.get());
                }
            }
        }

        for (auto o: objectsToDestroy) {
            auto it = std::find_if(mObjects.begin(), mObjects.end(), [o](auto obj) {
                return obj.get() == o;
            });
            assert(it != mObjects.end());
            //fmt::print("erasing object at index {0}\n", it - mObjects.begin());
            mObjects.erase(it);
            mBehaviours.erase(o);
        }
    }

    void Environment::AttachBehaviour(Object* target, shared_ptr<Behaviour> behaviour)
    {
        mBehaviours[target].push_back(behaviour);
    }

}