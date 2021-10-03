#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "IndexOBJLoader.h"
#include "glm/glm/glm.hpp"
#include "Cimg.h"

using namespace std;

class Triangle {

public:

	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 normal;

	Triangle() {};

	Triangle(
		glm::vec3 v1,
		glm::vec3 v2,
		glm::vec3 v3
	) {

		vertex1 = v1;
		vertex2 = v2;
		vertex3 = v3;
		
		normal = glm::cross(vertex2 - vertex1, vertex3 - vertex1);
	}

	float triIntersection(
		glm::vec3 orig,
		glm::vec3 dir,
		float* const& t2,
		glm::vec3* const& norm) {

		*norm = normal;
	//determine if point is inside triangle, using algorithm found at: http://geomalgorithms.com/a06-_intersect-2.html

		glm::vec3 edge1 = vertex2 - vertex1; //u
		glm::vec3 edge2 = vertex3 - vertex1; //v

		if (glm::dot(dir, normal) < 0) { return -1; } //ray is parallel to triangle
		if (glm::dot((vertex1 - orig), normal) < 0) { return -1; } //triangle misses plane
		
		float d = glm::dot((vertex1 - orig), normal) / glm::dot(dir, normal);
		glm::vec3 pI = orig + dir * d;
		
		float wDotU = glm::dot((pI - vertex1), edge1);
		float wDotV = glm::dot((pI - vertex1), edge2);
		float uDotV = glm::dot(edge1, edge2);
		float uDotU = glm::dot(edge1, edge1);
		float vDotV = glm::dot(edge2, edge2);

		//find t and s
		
		float t = ((uDotV * wDotU) - (uDotU * wDotV)) / ((uDotV * uDotV) - (uDotU * vDotV)); //distance to point from edge1
		float s = ((uDotV * wDotV) - (vDotV * wDotU)) / ((uDotV * uDotV) - (uDotU * vDotV)); //distance to point from edge2

		if (t < -0.01 || s < -0.01 || s + t > 1.01) { //point is outside of plane
			return -1; 
		} 

		//Intersection with a plane

		*t2 = d;

	if (*t2 > 0.001) {
		return *t2;
	}
	else {
		return -1;
	}
	}


};
