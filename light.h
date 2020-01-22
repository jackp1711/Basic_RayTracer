/*
    Class to store the data for different types of light to be used in local lighting generation, such as directional, and point lights.
*/
#pragma once

#include "vector.h"
#include "vertex.h"

class Light{

    public:

    Vertex colour;
    Vertex position;
    Vector direction;
    float intensity;

    Light() = default;

    Light(const Vertex &c, const Vector &d, float i)
    {
        this->colour = c;
        this->direction = d;
        this->intensity = i;
    }

    Light(const Vertex &col, const Vector &dir, const Vertex &point, float intens)
    {
        this->colour = col;
        this->direction = dir;
        this->position = point;
        this->intensity = intens;
    }
};