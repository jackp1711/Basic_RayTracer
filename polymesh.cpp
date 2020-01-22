/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "polymesh.h"
#include "ray.h"
#include "hit.h"
#include "vertex.h"
#include "vector.h"

using namespace std;


PolyMesh::PolyMesh(const char *file)
{
  Transform *transform = new Transform();

  this->do_construct(file, transform);
}

PolyMesh::PolyMesh(const char *file, Transform *transform)
{
  this->do_construct(file, transform);
}

void PolyMesh::do_construct(const char *file, Transform *transform)
{
  string line;
  string fileLineArray[10000];
  int index = 0;

  ifstream meshFile(file);

  if (meshFile.is_open())
  {
    while ( getline(meshFile, line))
    {
      fileLineArray[index] = line;
      index++;
    }
    meshFile.close();
    
  }
  else
  {
    cout << "Unable to open file";
  }

  istringstream vertex_line(fileLineArray[1]);

  int vArrayIndex = 0;
  string x,y;
  vertex_line >> x >> y >> vertex_count;

  istringstream triangle_line(fileLineArray[2]);

  int tArrayIndex = 0;
  int tStart = vertex_count + 3;
  
  triangle_line >> x >> y >> triangle_count;

  vertex = new Vertex[vertex_count];

  for(int i = 3; i < vertex_count+3; i++)
  {
    istringstream vertexLine(fileLineArray[i]);
    float x,y,z;

    vertexLine >> x >> y >> z;
    vertex[vArrayIndex] = Vertex (x, y ,z);
    transform -> apply(vertex[vArrayIndex]);
    vertex_normals.push_back(Vector(0,0,0));
    vArrayIndex++;
  }

  triangle = new TriangleIndex [triangle_count];

  for(int i = tStart; i < index; i++)
  {
    istringstream triangleLine(fileLineArray[i]);
    int a,x,y,z;
    triangleLine >> a >> x >> y >> z;

    x--;
    y--;
    z--;

    triangle[tArrayIndex][0] = x;
    triangle[tArrayIndex][1] = y;
    triangle[tArrayIndex][2] = z;

    Vertex x1 = vertex[x];
    Vertex y1 = vertex[y];
    Vertex z1 = vertex[z];

    Vector v0, v1, v2;
    v0.createVector(x1, y1);
    v1.createVector(x1, z1);

    v0.cross(v1, v2);

    vertex_normals[x].x += v2.x;
    vertex_normals[x].y += v2.y;
    vertex_normals[x].z += v2.z;

    vertex_normals[y].x += v2.x;
    vertex_normals[y].y += v2.y;
    vertex_normals[y].z += v2.z;

    vertex_normals[z].x += v2.x;
    vertex_normals[z].y += v2.y;
    vertex_normals[z].z += v2.z;

    tArrayIndex++;
  }

  for (int i = 0; i < vertex_normals.size(); i++)
  {
    vertex_normals[i].normalise();
  }
}