#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "glm.hpp"
#include "Cimg.h"

using namespace std;

class Sphere 
{
	public:

	glm::vec3 pos;
	float rad;
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spe;
	float shi;

	Sphere() {

		pos = glm::vec3(0, 0, 0);
		rad = 0;
		amb = glm::vec3(0, 0, 0);
		dif = glm::vec3(0, 0, 0);
		spe = glm::vec3(0, 0, 0);
		shi = 0.f;
	}

	Sphere(glm::vec3 position, float radius, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {

		pos = position;
		rad = radius;
		amb = ambient;
		dif = diffuse;
		spe = specular;
		shi = shininess;
	}
	void toString() {

		cout << "Sphere Info:\nPosition: (" << pos.x << " " << pos.y << " " << pos.z << ")\n";
		cout << "Radius: " << rad << "\n";
		cout << "Ambient: (" << amb.x << " " << amb.y << " " << amb.z << ")\n";
		cout << "Diffuse: (" << dif.x << " " << dif.y << " " << dif.z << ")\n";
		cout << "Specular: (" << spe.x << " " << spe.y << " " << spe.z << ")\n";
		cout << "Shininess: " << shi << "\n\n";
	}
	float intersection(
		glm::vec3& rayOrigin,
		glm::vec3& rayDirection,
		float* const& t,
		glm::vec3* const& sphereNormal ) {

		float xo = rayOrigin.x;
		float yo = rayOrigin.y;
		float zo = rayOrigin.z;

		float xc = pos.x;
		float yc = pos.y;
		float zc = pos.z;

		float xd = rayDirection.x;
		float yd = rayDirection.y;
		float zd = rayDirection.z;

		float a = (xd)*(xd) + (yd)*(yd) + (zd)*(zd);

		float b = 2 * (xd*(xo - xc) + yd*(yo - yc) + zd*(zo - zc));

		float c = (xo - xc)*(xo - xc) + (yo - yc)*(yo - yc) + (zo - zc)*(zo - zc) - rad*rad;

		float b4ac = (b*b) - (4 * a*c);

		if (!(b4ac > 0)) {
			return -1;
		}

		float t0 = (-b + glm::sqrt(b4ac)) / (2 * a);
		float t1 = (-b - glm::sqrt(b4ac)) / (2 * a);

		*t = min(t0, t1);
		
		*sphereNormal = glm::normalize((rayOrigin + rayDirection * *t) - pos);

		return *t;

	}

	void setTo(Sphere sp) {

		pos = sp.pos;
		rad = sp.rad;
		amb = sp.amb;
		dif = sp.dif;
		spe = sp.spe;
		shi = sp.shi;
	
	}

};
