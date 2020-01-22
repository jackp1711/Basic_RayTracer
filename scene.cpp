/*
    Implementation of the necessary addition and retrival of objects from the scene object vector.
*/

#include "object.h"
#include "scene.h"
#include <vector>
#include <limits>

Vertex Scene::raytrace(Ray ray, Hit hit)
{
    Hit shadowHit;
    Hit besthit;
    Vertex colour;

    objectTrace(ray, besthit);


    return colour;
}

void objectTrace(Ray ray, Hit &bestHit)
{
    for(int i = 0; i < objects.size(); i++)
    {
        Hit obj_hit;
        obj_hit.flag = false;
        Object obj = objects.at(i);

        obj.intersection(ray, obj_hit);

        if(obj_hit.flag)
        {
            if (obj_hit.t > 0.0f)
            {
                if(bestHit.flag == false)
                {
                    bestHit = obj_hit;
                }
                else if(obj_hit.t < bestHit.t)
                {
                    bestHit = obj_hit;
                }
            }
        }

    }
}

void Scene::addObject(Object obj)
{
    objects.push_back(obj);
    obj.index = objects.size() - 1;
}

Object& Scene::getObject(int index)
{
    return objects.at(index);
}

int Scene::getNumOfObjects()
{
    return objects.size();
}