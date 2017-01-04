//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_BLOCK_H
#define OFAPP_BLOCK_H

#include "../Mesh.h"
#include "Object.h"

namespace kll
{

    class Block: public kll::Object
    {
    public:
        Block(vec3 initialPos, vec3 dimensions);

    protected:
        void DrawImpl() override;
        void UpdateImpl(float dt) override {};

    private:
        Mesh mMesh;

    };

}

#endif //OFAPP_BLOCK_H
