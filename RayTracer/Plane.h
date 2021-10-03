#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "glm/glm/glm.hpp"
#include "Cimg.h"

using namespace std;

class Plane 
{	
	public:

	glm::vec3 nor;
	glm::vec3 pos;
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spe;
	float shi;

	Plane() {
		nor = glm::vec3(0, 0, 0);
		pos = glm::vec3(0, 0, 0);
		amb = glm::vec3(0, 0, 0);
		dif = glm::vec3(0, 0, 0);
		spe = glm::vec3(0, 0, 0);
		shi = 0.f;
	}

	Plane(glm::vec3& normal, glm::vec3& position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
		nor = normal;
		pos = position;
		amb = ambient;
		dif = diffuse;
		spe = specular;
		shi = shininess;
	}
	void toString() {

		cout << "Plane Info:\nNormal: (" << nor.x << " " << nor.y << " " << nor.z <<")\n";
		cout << "Position: (" << pos.x << " " << pos.y << " " << pos.z << ")\n";
		cout << "Ambient: (" << amb.x << " " << amb.y << " " << amb.z << ")\n";
		cout << "Diffuse: (" << dif.x << " " << dif.y << " " << dif.z << ")\n";
		cout << "Specular: (" << spe.x << " " << spe.y << " " << spe.z << ")\n";
		cout << "Shininess: " << shi << "\n\n";
	}
	float intersection(
		glm::vec3& rayOrigin,
		glm::vec3& rayDirection,
		float* const& t,
		glm::vec3* const& normal) {

		*t = -(((glm::dot(this->nor, rayOrigin) +
			glm::dot(nor, abs(this->pos)))) /
			glm::dot(nor, rayDirection));

		*normal = glm::normalize(this->nor);

		if (*t < 0.001f) {
			return -1;
		}

		return *t;
	}

};
