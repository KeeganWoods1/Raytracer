#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "IndexOBJLoader.h"
#include "Triangle.h"
#include "glm.hpp"
#include "Cimg.h"

using namespace std;

class Mesh 
{
	public:

	string file;
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spe;
	float shi;

	std::vector<Triangle> triangles;
	std::vector<int> vertexIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	Mesh() {
		file;
		amb = glm::vec3(0, 0, 0);
		dif = glm::vec3(0, 0, 0);
		spe = glm::vec3(0, 0, 0);
		shi = 0.f;

	}

	Mesh(char* const& fl, glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular, float& shininess) {
		file = fl;
		amb = ambient;
		dif = diffuse;
		spe = specular;
		shi = shininess;
	}

	void loadMesh(char* const& fl) {

		loadOBJ(fl, vertexIndices, vertices, normals, uvs);

		for (int i = 0; i < vertexIndices.size(); i+=3) {
			Triangle temp = Triangle(vertices[vertexIndices[i+2]], vertices[vertexIndices[i + 1]], vertices[vertexIndices[i]]);

			triangles.push_back(temp);
		}
	
	}

	void toString() {

		cout << "Mesh Info:\nFile Name: " << file << "\n";
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

		*t = INFINITY;

		float tp;
		glm::vec3 tn;

		for (int i = 0; i < this->triangles.size(); i++) {
			if (triangles[i].triIntersection(rayOrigin, rayDirection, &tp, &tn) > 0.000f && tp < *t) {

				*t = tp;
				*normal = -tn;
			}
		
		}
		if (*t == INFINITY) return -1;

		return *t ;

	}

};


