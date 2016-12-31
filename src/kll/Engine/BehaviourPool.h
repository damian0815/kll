//
// Created by Damian Stewart on 29/12/16.
//

#ifndef OFAPP_BEHAVIOURPOOL_H
#define OFAPP_BEHAVIOURPOOL_H

#include "../Behaviours/ImplodeBehaviour.h"
#include <vector>
using std::vector;

namespace kll {

    class BehaviourPool
    {
    public:
        ImplodeBehaviour* GetNewImplodeBehaviour();

        void GiveBackBehaviour(Behaviour *pBehaviour);

    private:


        vector<ImplodeBehaviour*> mImplodeBehaviours;

    };

}

#endif //OFAPP_BEHAVIOURPOOL_H
