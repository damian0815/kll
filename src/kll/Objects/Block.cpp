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
    : Object(initialPos)
    {
        auto parMesh = par_shapes_create_cube();
        par_shapes_scale(parMesh, dimensions.x, dimensions.y, dimensions.z);
        par_shapes_translate(parMesh, -dimensions.x/2, -dimensions.y/2, -dimensions.z/2);
        par_shapes_compute_normals(parMesh);

        mMesh = Mesh(parMesh);

        par_shapes_free_mesh(parMesh);

    }


}