//
// Created by Damian Stewart on 10/12/2016.
//

#include "Mesh.h"
#include <OpenGl/gl.h>
#include "../3rdparty/par_shapes.h"
#include <glm/gtx/normal.hpp>

using std::pair;
using glm::vec2;


static void PopulateVectorFromFloatArray(vector<vec3>& vector, float* source, int numPoints)
{
    vector.resize((unsigned long) numPoints);
    for (int i=0; i < numPoints; i++) {
        vector[i] = vec3(source[i*3+0], source[i*3+1], source[i*3+2]);
    }
}


kll::Mesh::Mesh(const par_shapes_mesh *parShapeMesh)
{
    PopulateVectorFromFloatArray(mVertices, parShapeMesh->points, parShapeMesh->npoints);
    PopulateVectorFromFloatArray(mNormals, parShapeMesh->normals, parShapeMesh->npoints);

    mTriangles.resize((unsigned long) (parShapeMesh->ntriangles * 3));
    for (int i=0; i<parShapeMesh->ntriangles*3; i++) {
        mTriangles[i] = parShapeMesh->triangles[i];
    }
}

static void glVertex3f(const vec3 &v)
{
    glVertex3f(v.x, v.y, v.z);
}

static void glNormal3f(const vec3 &n)
{
    glNormal3f(n.x, n.y, n.z);
}

static void glTexCoord2f(const vec2& st)
{
    glTexCoord2f(st.s, st.t);
}

void kll::Mesh::Draw()
{
    ofMesh mesh(OF_PRIMITIVE_TRIANGLES, toOfVector(mVertices));
    mesh.addIndices(mTriangles);
    mesh.addNormals(toOfVector(mNormals));
    mesh.draw();
}

void kll::Mesh::DrawWireframe()
{
    glBegin(GL_LINES);
    for (int triIdx=0; triIdx<mTriangles.size()/3; triIdx++) {
        unsigned int* triangle = &mTriangles[triIdx*3];
        for (int i=0; i<3; i++) {
            glVertex3f(mVertices[triangle[i]]);
            glVertex3f(mVertices[triangle[(i+1)%3]]);
        }
    }
    glEnd();
}

void kll::Mesh::CalculateNormals()
{
    vector<vec3> vertexNormalAccumulator(mVertices.size());
    for (int triIdx=0; triIdx<mTriangles.size()/3; triIdx++) {
        const auto* tData = &mTriangles[triIdx*3];
        auto triangleNormal = glm::triangleNormal(mVertices[tData[0]], mVertices[tData[1]], mVertices[tData[2]]);

        for (int i=0; i<3; i++) {
            vertexNormalAccumulator[tData[i]] += triangleNormal;
        }
    }

    for (auto& v: vertexNormalAccumulator) {
        v = glm::normalize(v);
    }

    mNormals = vertexNormalAccumulator;
}

vector<ofVec3f> kll::Mesh::toOfVector(const vector<vec3> &x)
{
    vector<ofVec3f> result;
    std::transform(x.begin(), x.end(), std::back_inserter(result),
                   [](const auto& v) { return ofVec3f(v.x, v.y, v.z); });
    return result;
}

kll::Mesh::Mesh(const vector<vec3> &vertices, const vector<unsigned int> &triangles)
                : mVertices(vertices), mTriangles(triangles)
{
    CalculateNormals();
}




