/*
    Main method for executing the raytracer on objects placed into the scene.
    Sets up the camera, viewing area, adds the necessary object, and performs an intersection test for each ray cast from the camera to the pixels, building the image.
*/

#include "ray.h"
#include "framebuffer.h"
#include "polymesh.h"
#include "hit.h"
#include "object.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "localLighting.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void generateColour(Object &obj, Light light);

int main(int argc, char *argv[])
{
    float imageHeight = 512;
    float imageWidth = 512;

    float halfHeight = imageHeight/2;
    float halfWidth = imageWidth/2;

    FrameBuffer *fb = new FrameBuffer(imageHeight, imageWidth);

    Scene scene;
    Camera camera(0, 0, 0);

    camera.setLookAt(0, 0, 7);

    camera.distance = 3;

    LocalLighting lightModel;
    lightModel.ambientIntensity = 0.15f;

    Vertex lightPoint = Vertex(0, 0, 1);
    Vector lightDirection;
    lightDirection.createVector(lightPoint, camera.lookAt);
    lightDirection.normalise();

    Light pointLight = Light (Vertex(1,1,1), Vector(1, 0, 1), lightPoint, 0.75f);
    
    scene.addLight(pointLight);

    Object teapot = Object("teapot.ply", Vertex(1.0f, 0.0f, 0.0f), Vertex(-0.25f, 2.0f, 20.0f));
    teapot.ambientCoeff = 0.1f;
    teapot.diffuseCoeff = 0.7f;
    teapot.specularCoeff = 0.01f;

    scene.addObject(teapot);

    for (int i = 0; i < imageHeight; i++)
    {
        for(int j = 0; j < imageWidth; j++)
        {
            float pixel_x = j / imageWidth - 0.5f;
            float pixel_y = i / imageHeight - 0.5f;
            Vertex pixel = Vertex (pixel_x, pixel_y, camera.distance);
            Vector rayVect;
            rayVect.createVector(camera.position, pixel);
            rayVect.normalise();

            Ray ray = Ray(pixel, rayVect);
            Hit hit;
            hit.flag = false;
            hit.t = 100000;

            Vertex colour = scene.raytrace(ray, lightModel, camera);

            fb->plotPixel(j, i, colour.x, colour.y, colour.z);
            // fb->plotDepth(j, i, hit.t);
        }
    }
    fb->writeRGBFile((char *)"teapotFinal.ppm");
    // fb->writeDepthFile((char*)"teapotFinalDepth.ppm");
}