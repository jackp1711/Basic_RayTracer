/*
    Implementation to calculate the ambient, diffuse, and specular lighting for the object and light source passed through.
    An attempt at shadow testing was made, but this was unsuccessful for the moment.
*/
#include "ray.h"
#include "vector.h"
#include "vertex.h" 
#include "light.h"
#include "camera.h"
#include "scene.h"
#include "localLighting.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

Vertex LocalLighting::generateColour(Hit &hit, Vertex &viewer, Light &light, Object *obj)
{
    // Object *obj = hit.what;
    Vertex colour;
    float intensity;
    float scaling = 100;

    float ambient = 0.2f;
    float diffuse = 0.7f;
    float specular = 0.1f;

    float inLine = hit.normal.dot(light.direction);

    if (inLine < 0)
    {
        diffuse = 0;
    }
    else
    {
        diffuse *= inLine * light.intensity; cout<< diffuse << endl;
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
        specular *= light.intensity * pow(reflection.dot(viewingDirection), 100);
    }

    intensity = ambient + diffuse + specular;

    if(intensity > 1)
    {
        intensity = 1;
    }
    
    colour = Vertex(obj->colour.x * intensity, obj->colour.y * intensity, obj->colour.z * intensity);

    return colour;
}