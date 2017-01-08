//
// Created by Damian Stewart on 03/01/17.
//

#include "TunnelSection.h"

#include <glm/gtx/rotate_vector.hpp>

static kll::Mesh BuildTunnelMesh(float length, float radius, int numSegments, int numSlices)
{
    auto segmentAngle = float(2.0 * M_PI) / numSegments;
    auto sliceDistance = length / (numSlices-1);

    vector<vec3> vertices;
    vector<vec2> texCoords;
    for (int whichSlice=0; whichSlice<numSlices; whichSlice++) {
        vec3 tunnelStartCenter(0, 0, 0);
        vec3 tunnelDirection(0, 0, 1);
        auto thisSliceTunnelCenter = tunnelStartCenter + tunnelDirection * (sliceDistance * whichSlice);
        for (int whichSegment = 0; whichSegment < numSegments; whichSegment++) {
            vec3 tunnelOutDirection(1, 0, 0);
            auto thisOutDirection = rotateZ(tunnelOutDirection, segmentAngle * whichSegment);

            vertices.push_back(thisSliceTunnelCenter + thisOutDirection * radius);
            texCoords.push_back(vec2(float(whichSlice)/numSlices, float(whichSegment)/numSegments));
        }
    }

    vector<unsigned int> triangles;
    for (int whichSlice=0; whichSlice<(numSlices-1); whichSlice++) {

        int thisSliceStartVIdx = whichSlice * numSegments;
        int nextSliceStartVIdx = (whichSlice+1) * numSegments;

        for (int whichSegment=0; whichSegment<numSegments; whichSegment++) {
            int thisSegmentStartOffset = whichSegment;
            int nextSegmentStartOffset = (whichSegment+1)%numSegments;
            triangles.push_back(thisSliceStartVIdx + thisSegmentStartOffset);
            triangles.push_back(nextSliceStartVIdx + thisSegmentStartOffset);
            triangles.push_back(thisSliceStartVIdx + nextSegmentStartOffset);

            triangles.push_back(thisSliceStartVIdx + nextSegmentStartOffset);
            triangles.push_back(nextSliceStartVIdx + thisSegmentStartOffset);
            triangles.push_back(nextSliceStartVIdx + nextSegmentStartOffset);
        }
    }

    return kll::Mesh(vertices, triangles, texCoords);
}

void kll::TunnelSection::DrawImpl()
{
    //ofSetColor(1,1,1,GetAlpha());
    mShader.Begin();
    mMesh.Draw();
    mShader.End();
}

kll::TunnelSection::TunnelSection(float length, float radius, int numSegments, int numSlices)
: mMesh(BuildTunnelMesh(length, radius, numSegments, numSlices))
{
    mShader.Reload();
}



