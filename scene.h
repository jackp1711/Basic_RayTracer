/*
    Class to store all of the objects in a scene in a single vector for easier implementation of multiple object rendering.
*/

#pragma once

#include "object.h"
#include <vector>
#include <limits>

using namespace std; 


class Scene{
public:
    vector <Object> objects;
    
    Scene()
    {
    }

    Vertex raytrace(Ray ray, Hit hit);

    void addObject(Object obj);

    Object &getObject(int index);

    int getNumOfObjects();
};