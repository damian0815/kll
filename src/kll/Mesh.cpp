//
// Created by Damian Stewart on 10/12/2016.
//

#include "Mesh.h"
#include <OpenGl/gl.h>
#include "../3rdparty/par_shapes.h"

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

void kll::Mesh::Draw()
{
    glBegin(GL_TRIANGLES);
    for (int triIdx=0; triIdx<mTriangles.size()/3; triIdx++) {
        int* triangle = &mTriangles[triIdx*3];
        for (int i=0; i<3; i++) {
            glVertex3f(mVertices[triangle[i]]);
            glNormal3f(mNormals[triangle[i]]);
        }
    }
    glEnd();

}
