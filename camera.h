/*
    Class to store information about the camera in relation to the world coordinate system.
    Includes implementation to set the lookAt point and the position of the camera, updating
    the necessary vectors in the mean time.
*/

#pragma once

#include "vector.h"
#include "vertex.h"

class Camera{
    public:
        Vertex position;

        Vector worldX = Vector(1,0,0);
        Vector worldY = Vector(0,1,0);
        Vector worldZ = Vector(0,0,1);

        Vector up;
        Vector left;
        Vector down;
    
        Vertex eye;
        Vertex lookAt;
    
        Vector lookAtVector;

        float distance;
    
    Camera()
    {
        position.x = 0;
        position.y = 0;
        position.z = 0;
        position.w = 1;
    }

    Camera(float x, float y, float z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
        position.w = 1;
    }

    void setLookAt(float x, float y, float z)
    {
        lookAt.x = x;
        lookAt.y = y;
        lookAt.z = z;
        lookAt.w = 1;

        lookAtVector.x = x - position.x;
        lookAtVector.y = y - position.y;
        lookAtVector.z = z - position.z;

        worldY.cross(lookAtVector, left);
        left.cross(lookAtVector, up);
    }

    void setDistance(float d)
    {
        distance = d;
    }
};