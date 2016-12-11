//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_BLOCK_H
#define OFAPP_BLOCK_H

#include "Object.h"
#include "Mesh.h"

namespace kll
{

    class Block: public Object
    {
    public:
        Block(vec3 initialPos, vec3 dimensions);
        void DrawImpl() override;

        void UpdateImpl(float dt) override;

    private:
        Mesh mMesh;

    };

}

#endif //OFAPP_BLOCK_H
