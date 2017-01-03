//
// Created by Damian Stewart on 03/01/17.
//

#ifndef OFAPP_TUNNELSECTION_H
#define OFAPP_TUNNELSECTION_H

#include "Object.h"
#include "../Mesh.h"

namespace kll
{

    class TunnelSection : public Object
    {
    public:
        TunnelSection(float length, float radius, int numSegments, int numSlices);

    protected:
        void DrawImpl() override;
        void UpdateImpl(float dt) override { }

    private:
        Mesh mMesh;

    };


}

#endif //OFAPP_TUNNELSECTION_H
