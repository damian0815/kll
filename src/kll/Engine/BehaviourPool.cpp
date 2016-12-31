//
// Created by Damian Stewart on 29/12/16.
//

#include <fmt/format.h>
#include "BehaviourPool.h"

kll::ImplodeBehaviour *kll::BehaviourPool::GetNewImplodeBehaviour()
{
    if (mImplodeBehaviours.size() == 0) {
        return new ImplodeBehaviour();
    }

    auto behaviour = mImplodeBehaviours.back();
    mImplodeBehaviours.erase(mImplodeBehaviours.end()-1);
    behaviour->Reset();
    return behaviour;
}

void kll::BehaviourPool::GiveBackBehaviour(kll::Behaviour *pBehaviour)
{
    auto implodeBehaviour = dynamic_cast<ImplodeBehaviour*>(pBehaviour);
    if (implodeBehaviour != nullptr) {
        mImplodeBehaviours.push_back(implodeBehaviour);
        return;
    }

    fmt::print("Unknown behaviour - deleting\n");
    delete pBehaviour;

}
