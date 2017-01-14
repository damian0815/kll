//
// Created by Damian Stewart on 10/12/2016.
//

#include "Block.h"
#include <OpenGL/OpenGL.h>
#include "../../3rdparty/par_shapes.h"

namespace kll
{

    void Block::DrawImpl()
    {
        mMesh.Draw();
    }

    Block::Block(vec3 initialPos, vec3 dimensions)
    : Object(initialPos), mUnscaledDimensions(dimensions)
    {
        auto parMesh = par_shapes_create_cube();
        par_shapes_scale(parMesh, dimensions.x, dimensions.y, dimensions.z);
        par_shapes_translate(parMesh, -dimensions.x/2, -dimensions.y/2, -dimensions.z/2);
        par_shapes_compute_normals(parMesh);

        mMesh = Mesh(parMesh);

        par_shapes_free_mesh(parMesh);
    }

    kll::gvec3 Block::GetScaledDimensions()
    {
        return mUnscaledDimensions * GetScale();
    }

    void Block::SetScaledDimensions(kll::gvec3 d)
    {
        vec3 desiredScale(d.x / mUnscaledDimensions.x, d.y / mUnscaledDimensions.y, d.z / mUnscaledDimensions.z);
        SetScale(desiredScale);
    }
}
