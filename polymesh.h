/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#pragma once

#include "vertex.h"
#include "transform.h"
#include "hit.h"
#include "ray.h"

#include <vector>

typedef int TriangleIndex[3];

class PolyMesh {
public:
	int vertex_count;
	int triangle_count;
        Vertex *vertex;
	TriangleIndex *triangle;

	std::vector <Vector> vertex_normals;

	void do_construct(const char *file, Transform *transform);
	
	PolyMesh(const char *file);
	PolyMesh(const char *file, Transform *transform);
};
