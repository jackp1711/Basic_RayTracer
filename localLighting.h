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

    LocalLighting(){};
    
    Vertex generateColour(Hit &hit, Vertex &viewer, Light &light, Object *obj);
};