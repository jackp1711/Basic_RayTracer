/*
    Class to store the details of the local lighting model to be accessed by the raytracer method.
    Allows implementation to add as many lights as the scene requires in a vector.
*/
#pragma once

#include "object.h"
#include "scene.h"
#include "light.h"
#include "camera.h"

#include <vector>

using namespace std;

class LocalLighting
{
    public:

    float ambientIntensity = 1;
    vector <Light> lights;

    LocalLighting() = default;
    
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
    
    Vertex generateColour(Hit &hit, Vertex &viewer, Scene &scene);
    bool shadowTest(Object &obj, Hit &h, Light light, Scene &scene);
};