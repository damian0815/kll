//
// Created by Damian Stewart on 10/12/2016.
//

#include "Mesh.h"
#include <OpenGl/gl.h>
#include "../3rdparty/par_shapes.h"
#include <glm/gtx/normal.hpp>

using std::pair;
using glm::vec2;

static vector<ofVec3f> toOfVector(const vector<vec3> &x)
{
    vector<ofVec3f> result;
    std::transform(x.begin(), x.end(), std::back_inserter(result),
                   [](const auto& v) { return ofVec3f(v.x, v.y, v.z); });
    return result;
}

static vector<ofVec2f> toOfVector(const vector<vec2> &x)
{
    vector<ofVec2f> result;
    std::transform(x.begin(), x.end(), std::back_inserter(result),
                   [](const auto& v) { return ofVec2f(v.x, v.y); });
    return result;
}

static void PopulateVectorFromFloatArray(vector<ofVec3f>& vector, float* source, int numPoints)
{
    vector.resize((unsigned long) numPoints);
    for (int i=0; i < numPoints; i++) {
        vector[i] = ofVec3f(source[i*3+0], source[i*3+1], source[i*3+2]);
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

    PopulateMesh();
}


kll::Mesh::Mesh(const vector<vec3> &vertices, const vector<unsigned int> &triangles, const vector<vec2>& texCoords)
                : mVertices(toOfVector(vertices)), mTriangles(triangles)
{
    CalculateNormals();
    PopulateMesh();
}

static void glVertex3f(const ofVec3f &v)
{
    glVertex3f(v.x, v.y, v.z);
}

static void glNormal3f(const ofVec3f &n)
{
    glNormal3f(n.x, n.y, n.z);
}

void kll::Mesh::Draw()
{
    mMesh.draw();
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

static ofVec3f CalculateTriangleNormal(const ofVec3f &a, const ofVec3f &b, const ofVec3f &c)
{
    return ((b-a).cross(c-a)).getNormalized();
}

void kll::Mesh::CalculateNormals()
{
    vector<ofVec3f> vertexNormalAccumulator(mVertices.size());
    for (int triIdx=0; triIdx<mTriangles.size()/3; triIdx++) {
        const auto* tData = &mTriangles[triIdx*3];
        auto triangleNormal = CalculateTriangleNormal(mVertices[tData[0]], mVertices[tData[1]], mVertices[tData[2]]);

        for (int i=0; i<3; i++) {
            vertexNormalAccumulator[tData[i]] += triangleNormal;
        }
    }

    for (auto& v: vertexNormalAccumulator) {
        v.normalize();
    }

    mNormals = vertexNormalAccumulator;
}

void kll::Mesh::PopulateMesh()
{
    mMesh.clear();
    mMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mMesh.addVertices(mVertices);
    mMesh.addNormals(mNormals);
    mMesh.addIndices(mTriangles);
}




