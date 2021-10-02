#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "Ray.h"
#include "glm/glm/glm.hpp"
#include "Cimg.h"

using namespace std;

class Camera
{	public:

	glm::vec3 pos;
	float fov;
	float f;
	float a;

	const glm::vec3 camDir = glm::vec3(0, 0, -1);

	Camera() {
		pos = glm::vec3(0, 0, 0);
		fov = 0.f;
		f = 0.f;
		a = 0.f;
	}

	Camera(glm::vec3 position, float frameOfView, float focalLength, float aspectRatio) {
		pos = position;
		fov = frameOfView;
		f = focalLength;
		a = aspectRatio;
	}

	void toString() {
		cout << "Camera Info:\nposition: (" << pos.x <<" " <<pos.y <<" " <<pos.z << ")\n";
		cout << "Frame of View: " << fov << "\n";
		cout << "Focal Length: " << f << "\n";
		cout << "Aspect Ratio: " << a << "\n\n";
	}

};
