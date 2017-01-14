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
        ofLoadMatrix(ofGetCurrentMatrix(OF_MATRIX_MODELVIEW) * mCamera.GetTransform());

        mLight.Enable();
        for (auto& o: mObjects) {
            o->Draw();
        }
        mLight.Disable();
    }

    void Environment::Update(float dt)
    {
        ofLoadMatrix(mCamera.GetTransform());
        vector<Object*> expiredObjects;

        for (auto o: mObjects) {
            o->Update(dt);

            if (o->GetRemainingLifetime() <= 0) {
                expiredObjects.push_back(o);
            }
        }

        for (auto o: expiredObjects) {
            RemoveObject(o);
        }
    }

    void Environment::RemoveObject(Object *o)
    {
        auto it = find(mObjects.begin(), mObjects.end(), o);
        assert(it != mObjects.end());
        //fmt::print("erasing object at index {0} ({1} remain)\n", it - mObjects.begin(), mObjects.size());
        mObjects.erase(it);

        delete o;
    }

    void Environment::Clear()
    {
        for (int i=mObjects.size()-1; i>=0; i--) {
            RemoveObject(mObjects[i]);
        }

    }

}