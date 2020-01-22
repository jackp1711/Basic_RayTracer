/*
    Class for a raytracer object.
*/

#include <string>
using namespace std;

class Raytracer
{
    public:

    Raytracer() = default;

    void Raytracer::generateImage(const std::string &filename);
};