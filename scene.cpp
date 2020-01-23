/*
    Implementation of the necessary addition and retrival of objects from the scene object vector.
*/

#include "scene.h"
#include <vector>
#include <limits>
#include <iostream>


using namespace std;

Vertex Scene::raytrace(Ray ray, LocalLighting &lightModel, Camera &camera)
{
    Hit shadowHit;
    Hit besthit;
    besthit.flag = false;
    Vertex colour;

    objectTrace(ray, besthit);

    if(besthit.flag)
    {
        // depth = besthit.t;

        for(int i = 0; i < lights.size(); i++)
        {
            Light light = lights.at(i);

            Vector lightDirection = light.direction;

            bool areaLit = true;

            if(lightDirection.dot(besthit.normal) > 0)
            {
                areaLit = false;
            }

            // if(areaLit)
            // {
            //     Ray shadow;

            //     shadow.direction = Vector(-lightDirection.x, -lightDirection.y, -lightDirection.z);
            //     shadow.position = Vertex(besthit.position.x + (0.0001f * shadow.direction.x), 
            //                              besthit.position.y + (0.0001f * shadow.direction.y),
            //                              besthit.position.z + (0.0001f * shadow.direction.z));
                
            //     objectTrace(shadow, shadowHit);

            //     if(shadowHit.flag = true)
            //     {
            //         if(shadowHit.t < 100000.0f)
            //         {
            //             areaLit = false;
            //         }
            //     }
            // }

            if(areaLit)
            {
                colour = lightModel.generateColour(besthit, camera.position, light, besthit.what);
            }
        }
    }
    return colour;
}

void Scene::objectTrace(Ray ray, Hit &bestHit)
{
    for(int i = 0; i < objects.size(); i++)
    {
        Hit obj_hit;
        obj_hit.t = 1000000.0f;
        obj_hit.flag = false;
        Object obj = objects.at(i);

        obj.intersection(ray, obj_hit);

        if(obj_hit.flag)
        {
            if (obj_hit.t > 0.0f)
            {
                if(bestHit.flag == false)
                {
                    bestHit.position = obj_hit.position;
                    bestHit.normal = obj_hit.normal;
                    bestHit.what = obj_hit.what;
                    bestHit.t = obj_hit.t;
                    bestHit.flag = true;
                }
                else if(obj_hit.t < bestHit.t)
                {
                    bestHit.position = obj_hit.position;
                    bestHit.normal = obj_hit.normal;
                    bestHit.what = obj_hit.what;
                    bestHit.t = obj_hit.t;
                    bestHit.flag = true;
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