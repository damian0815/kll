//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_ENVIRONMENT_H
#define OFAPP_ENVIRONMENT_H

#include "../kll.h"
#include "ofMain.h"
#include <map>
#include "../Objects/Block.h"
#include "gvec3.h"
#include "../Objects/TunnelSection.h"
#include "../Render/Shader.h"
#include "Light.h"

using std::map;

namespace kll
{
    class Object;
    class Behaviour;

    class Environment
    {
    public:
        Environment();
        static Environment* GetInstance() { return mInstance; }

        bool HasObject(Object *o) { return std::find(mObjects.begin(), mObjects.end(), o) != mObjects.end(); }
        void AddObject(Object *o);

        void RemoveObject(Object *o);

        void Draw();
        void Update(float dt);

        kll::Block * AddBlock(kll::gvec3 initialPos, kll::gvec3 dimensions);
        kll::TunnelSection *AddTunnelSection(float length, float radius, int segments=8, int slices=2);

        void PrintHello() { fmt::print("hello!\n"); }

        void Clear();

        kll::Lighty * GetLight() { return &mLight; }

        const vector<kll::Object *> &GetAllObjects() { return mObjects; }

    private:

        kll::Lighty mLight;

        vector<Object*> mObjects;

        static Environment *mInstance;

    };

}


#endif //OFAPP_ENVIRONMENT_H
