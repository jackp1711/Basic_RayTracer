/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

// Object is the base class for objects.
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "hit.h"
#include "vertex.h"
#include "polymesh.h"
#include "vector.h"
#include "localLighting.h"

#include <string>
class Scene;

class Object {
public:

	PolyMesh *mesh;
	Vertex colour;

	float ambientCoeff = 0.05f;
	float diffuseCoeff = 0.7f;
	float specularCoeff = 0.25f;

	int index;

	Object() = default;

	Object(const std::string &filename, const Vertex &c, const Vertex position )
	{
		Transform *transform =
		new Transform(
			1.0f, 0.0f, 0.0f, position.x,
			0.0f, -1.0f, 0.0f, position.y,
			0.0f, 0.0f, 1.0f, position.z,
			0.0f, 0.0f, 0.0f, 1.0f);
		mesh = new PolyMesh(filename.c_str(), transform);

		this->colour = c;
	}

	void intersection(Ray r, Hit &h);
};

#endif