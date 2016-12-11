//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_ENVIRONMENT_H
#define OFAPP_ENVIRONMENT_H

#include "kll.h"
#include <map>
#include "Block.h"

using std::map;

namespace kll
{
    class Object;
    class Behaviour;

    class Environment
    {
    public:
        void AddObject(shared_ptr<Object> o);
        void AttachBehaviour(Object* target, shared_ptr<Behaviour> behaviour);

        void Draw();
        void Update(float dt);

        Block * AddBlock(vec3 initialPos, vec3 dimensions);

    private:

        vector<shared_ptr<Object>> mObjects;
        map<Object*, vector<shared_ptr<Behaviour>>> mBehaviours;

    };

}


#endif //OFAPP_ENVIRONMENT_H
