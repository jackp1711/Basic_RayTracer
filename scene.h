/*
    Class to store all of the objects in a scene in a single vector for easier implementation of multiple object rendering.
*/

#pragma once

#include "object.h"
#include "light.h"
#include "localLighting.h"
#include "camera.h"
#include <vector>
#include <limits>

using namespace std;


class Scene{
public:
    vector <Object> objects;
    vector <Light> lights;
    
    Scene()
    {
    }

    Vertex raytrace(Ray ray, LocalLighting &lightModel, Camera &camera);
    
    void objectTrace(Ray ray, Hit &bestHit);

    void addObject(Object obj);

    Object &getObject(int index);

    int getNumOfObjects();

    void addLight(const Light l)
    {
        lights.push_back(l);
    }

    Light &getLight(int index)
    {
        return lights.at(index);
    }

    int getNumOfLights()
    {
        return lights.size();
    }
};