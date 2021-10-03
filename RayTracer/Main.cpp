#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "RayTracer.h"
#include "Ray.h"
#include "glm/glm/glm.hpp"
#include "Camera.h"
#include "SceneLoader.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Light.h"
#include "Cimg.h"

using namespace std;

float width = 800;
float height = 800;

int main()
{
	Camera cam;
	Plane plane;
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
	Mesh mesh;

	loadScene("Scenes/mesh_scene1.txt", cam, plane, spheres, lights, mesh);

	Ray ray = glm::vec3(0,0,0);
	vector<Ray> rays;
	glm::vec3 pixel_color;

	float height = 2 * cam.f * tan((glm::radians(cam.fov) / 2.0));
	unsigned int pixel_height = round(height); 
	unsigned int pixel_width = round((cam.a) * height);
	
	glm::vec3 centerImageSpace = cam.pos + (cam.camDir * cam.f);
	glm::vec3 bottomLeft = centerImageSpace - glm::vec3(pixel_width / 2.0f + 0.5, pixel_height / 2.0f + 0.5, 0.0f);

	
	//Creates an image with three channels and sets it to black
	cimg_library::CImg<float> image(pixel_width, pixel_height, 1, 3, 0);
	cout << "Rendering image...";
	for (int i = 0; i < pixel_width; i++) {
		for (int j = 0; j <pixel_height ; j++) {

			//Compute the color of each pixel and assign it
			//TODO:	
			
			ray = Ray(glm::normalize(glm::vec3(bottomLeft.x + i, bottomLeft.y + j, bottomLeft.z) - cam.pos));

			glm::vec3 pixel_color = rayTrace(cam.pos, ray.direction, plane, spheres, lights, mesh); // find pixel color using ray tracing
			
			image(i, j, 0) = pixel_color.x * 255.0f; //red
			image(i, j, 1) = pixel_color.y * 255.0f; //green
			image(i, j, 2) = pixel_color.z * 255.0f; //blue

		}
	}
	
	//Save out the image in BMP format. Pixel values must be in the range [0,255]
	image.save("Scene_Rendered_By_Raytracer.bmp");
	//Display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) {
		main_disp.wait();
	}
int i; 
cin >> i;
}
