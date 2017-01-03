//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_MESH_H
#define OFAPP_MESH_H

#include <vector>
#include <glm/glm.hpp>

using std::vector;
using glm::vec3;
struct par_shapes_mesh_s;

namespace kll
{

    class Mesh
    {
    public:
        Mesh() {}
        Mesh(const par_shapes_mesh_s* parShapeMesh);

        void CalculateNormals();

        Mesh(const vector<vec3> &vertices, const vector<int> &triangles)
            : mVertices(vertices), mTriangles(triangles) { CalculateNormals(); }

        void Draw();

        void DrawWireframe();

    private:

        vector<vec3> mVertices;
        vector<vec3> mNormals;
        vector<int> mTriangles;

    };

}


#endif //OFAPP_MESH_H
