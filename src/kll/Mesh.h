//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_MESH_H
#define OFAPP_MESH_H

#include <gl/ofShader.h>
#include <vector>
#include <glm/glm.hpp>
#include <gl/ofVbo.h>

using std::vector;
using glm::vec3;
using glm::vec2;
struct par_shapes_mesh_s;

namespace kll
{

    class Mesh
    {
    public:
        Mesh() {}
        Mesh(const par_shapes_mesh_s* parShapeMesh);
        Mesh(const vector<vec3> &vertices, const vector<unsigned int> &triangles, const vector<vec2>& texCoords);

        void Draw();

        void DrawWireframe();

    private:

        void CalculateNormals();

        vector<ofVec3f> mVertices;
        vector<ofVec3f> mNormals;

        vector<unsigned int> mTriangles;

        ofMesh mMesh;

        void PopulateMesh();
    };

}


#endif //OFAPP_MESH_H
