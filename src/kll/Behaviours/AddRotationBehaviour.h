//
// Created by Damian Stewart on 11/12/2016.
//

#ifndef OFAPP_ADDROTATIONBEHAVIOUR_H
#define OFAPP_ADDROTATIONBEHAVIOUR_H

#include "../kll.h"
#include "Behaviour.h"

namespace kll {

class AddRotationBehaviour: public Behaviour
{
public:
    AddRotationBehaviour(Object *target, vec3 angularVelocity);

public:
    void Update(float dt) override;

private:

    vec3 mAngularVelocity;
};

}

#endif //OFAPP_ADDROTATIONBEHAVIOUR_H
