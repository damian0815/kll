//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_ENVIRONMENT_H
#define OFAPP_ENVIRONMENT_H

#include "../kll.h"
#include <map>
#include "../Block.h"

using std::map;

namespace kll
{
    class Object;
    class Behaviour;

    struct gvec3
    {
        gvec3() = default;
        gvec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        gvec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}
        operator vec3() const { return vec3(x, y, z); }
        float x=0, y=0, z=0;
    };

    class Environment
    {
    public:
        Environment() { assert(mInstance == nullptr); mInstance = this; }
        static Environment* GetInstance() { return mInstance; }

        void AddObject(Object *o);
        void AttachBehaviour(Object *target, Behaviour *behaviour);

        void Draw();
        void Update(float dt);

        Block * AddBlock(gvec3 initialPos, gvec3 dimensions);

        void PrintHello() { fmt::print("hello!\n"); }

    private:

        vector<Object*> mObjects;
        map<Object*, vector<Behaviour*>> mBehaviours;

        static Environment *mInstance;
    };

}


#endif //OFAPP_ENVIRONMENT_H
