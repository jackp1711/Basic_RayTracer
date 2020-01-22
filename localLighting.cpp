/*
    Implementation to calculate the ambient, diffuse, and specular lighting for the object and light source passed through.
    An attempt at shadow testing was made, but this was unsuccessful for the moment.
*/
#include "ray.h"
#include "vector.h"
#include "vertex.h" 
#include "light.h"
#include "localLighting.h"
#include "camera.h"
#include "scene.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

bool shadowTest(Object &obj, Hit &h, Light light, Scene &scene);

Vertex LocalLighting::generateColour(Hit &hit, Vertex &viewer, Scene &scene)
{
    Object *obj = hit.what;
    Vertex colour;
    Light light = getLight(0);
    float intensity;

    float ambient = obj->ambientCoeff * ambientIntensity;
    float diffuse = 0;
    float specular = 0;

    float inLine = hit.normal.dot(light.direction);

    if (inLine < 0)
    {
        diffuse = 0;
    }
    else
    {
        diffuse = inLine * obj->diffuseCoeff * light.intensity;
    }

    Vector incident = light.direction;
    incident.normalise();

    Vector viewingDirection;
    viewingDirection.createVector(hit.position, viewer);
    viewingDirection.normalise();

    Vector reflection;
    hit.normal.reflection(incident, reflection);
    reflection.normalise();

    if(reflection.dot(viewingDirection) < 0)
    {
        specular = 0;
    }
    else
    {
        specular = light.intensity * obj->specularCoeff * pow(reflection.dot(viewingDirection), 100);
    }

    intensity = ambient + diffuse + specular;

    if(intensity > 1)
    {
        intensity = 1;
    }

    colour = Vertex(obj->colour.x * intensity, obj->colour.y * intensity, obj->colour.z * intensity);

    return colour;
}

bool LocalLighting::shadowTest(Object &obj, Hit &h, Light light, Scene &scene)
{
    h.position.x = h.position.x + 0.0001*h.normal.x;
    h.position.y = h.position.y + 0.0001*h.normal.y;
    h.position.z = h.position.z + 0.0001*h.normal.z;
    
    Vector toLightVect;
    toLightVect.createVector(h.position, light.position);
    toLightVect.normalise();

    Ray ray = Ray(h.position, toLightVect);
    Hit shadowHit;

    for(int i = 0; i < scene.getNumOfObjects(); i++)
    {
      Object &testObj = scene.getObject(i);
      testObj.intersection(ray, shadowHit);
    }
    return shadowHit.flag;
}