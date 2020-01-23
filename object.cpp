/*
  Implementation of various methods for Object type objects. Includes the necessary intersection test with a ray to be used in the raytracer.
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "polymesh.h"
#include "ray.h"
#include "hit.h"
#include "object.h"
#include "light.h"
#include "scene.h"
#include "localLighting.h"

using namespace std;

bool triangleIntersect(Vertex p, Vertex a, Vertex b, Vertex c);
bool shadowTest(Object &obj, Hit &h, LocalLighting &lights, Scene scene);

float u, v , w;


/*
  Intersection algorithm adapted from the Möller–Trumbore Algorithm found on wikipedia here: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
*/
void Object::intersection(Ray r, Hit &h)
{
  float epsilon = 0.00000001f;

  for(int i = 0; i < mesh->triangle_count; i++)
  {
    Vertex p0 = mesh->vertex[mesh->triangle[i][0]];
    Vertex p1 = mesh->vertex[mesh->triangle[i][1]];
    Vertex p2 = mesh->vertex[mesh->triangle[i][2]];

    Vector edge1, edge2, vH, s, q;
    float a, f, u, v;
    edge1.createVector(p0, p1);
    edge2.createVector(p0, p2);

    r.direction.cross(edge2, vH);
    a = edge1.dot(vH);

    if (a > -epsilon && a < epsilon)
    {
      continue;
    }
    else
    {
      f = 1.0f/a;

      s = Vector(r.position.x - p0.x, r.position.y - p0.y, r.position.z - p0.z);

      u = f * s.dot(vH);

      if (u < 0.0f || u > 1.0f)
      {
        continue;
      }
      else
      {
        s.cross(edge1, q);

        v = f* r.direction.dot(q);

        if(v < 0.0f || v + u > 1.0f)
        {
         continue;
        }
        else
        {
          float t = f * edge2.dot(q);

          if(t > epsilon && t < 1/epsilon && t < h.t)
          {
            Vertex hitPoint = Vertex((r.position.x + t*r.direction.x), (r.position.y + t*r.direction.y), (r.position.z + t*r.direction.z));

            Vector normal0 = mesh->vertex_normals.at(mesh->triangle[i][0]);
            Vector normal1 = mesh->vertex_normals.at(mesh->triangle[i][1]);
            Vector normal2 = mesh->vertex_normals.at(mesh->triangle[i][2]);

            float w = 1 - u - v;

            normal0 = Vector (normal0.x * w, normal0.y * w, normal0.z * w);
            normal1 = Vector (normal1.x * u, normal1.y * u, normal1.z * u);
            normal2 = Vector (normal2.x * v, normal2.y * v, normal2.z * v);

            Vector hitNormal = Vector (normal0.x + normal1.x + normal2.x, normal0.y + normal1.y + normal2.y, normal0.z + normal1.z + normal2.z);
            hitNormal.normalise();

            h.position = hitPoint;
            h.normal = hitNormal;
            h.what = this;
            h.t = t;
            h.flag = true;
          }
          else
          {
           continue;
          }
        }
      }
    }
  }
}