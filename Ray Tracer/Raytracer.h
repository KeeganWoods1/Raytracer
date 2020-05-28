#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "glm.hpp"
#include "Ray.h"
#include "Camera.h"
#include "SceneLoader.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Light.h"
#include "Cimg.h"

using namespace std;

glm::vec3 rayTrace(
	glm::vec3& camPos,
	glm::vec3& rayDir,
	Plane& plane,
	std::vector<Sphere>& spheres,
	std::vector<Light>& lights,
	Mesh& mesh) {

	glm::vec3 current_color = glm::vec3(0, 0, 0);
	glm::vec3 final_color = glm::vec3(0, 0, 0);
	glm::vec3 black = glm::vec3(0, 0, 0);

	float t_near = INFINITY;
	float tp = 0;
	float ts = 0;
	float tm = 0;
	float tps = 0;
	float tss = 0;
	float tms = 0;
	boolean intersected = false;
	glm::vec3 normal;
	glm::vec3 norm;
	glm::vec3 n;

	boolean isPlane = false;
	boolean isSphere = false;
	boolean isMesh = false;

	Sphere sphere;


	//Test scene for intersection

	if (plane.intersection(camPos, rayDir, &tp, &norm) > 0.001f && tp < t_near) {
		t_near = tp;
		normal = norm;
		isPlane = true;
		isSphere = false;
		isMesh = false;
		current_color = plane.amb;
		intersected = true;
	}
	for (int i = 0; i < spheres.size(); i++) {

		if (spheres[i].intersection(camPos, rayDir, &ts, &norm) > 0.001f && ts < t_near) {
			t_near = ts;
			normal = norm;
		    sphere.setTo(spheres[i]);
			isSphere = true;
			isPlane = false;
			isMesh = false;
			current_color = spheres[i].amb;
			intersected = true;
		}
	}
	if (mesh.intersection(camPos, rayDir, &tm, &norm) > 0.001f && tm < t_near) {
		t_near = tm;
		normal = norm;
		isMesh = true;
		isPlane = false;
		isSphere = false;
		current_color = mesh.amb;
		intersected = true;

	}
	
	else if (!intersected) {

		return final_color;
	}

	//Check every light to see if point is in shadow

	for (Light& light : lights) {

		

		glm::vec3 p = camPos + rayDir * t_near;  //Nearest point of intersection

		float t_n;

		glm::vec3 lp = light.pos;

		glm::vec3 dir = glm::normalize(lp - p);

		bool shadowed = false;
		
		//Test for intersections between intersection point and light sources

		if (plane.intersection(p, dir, &tps, &n) > -0.03) {
			shadowed = true;

		}
		for (int i = 0; i < spheres.size(); i++) {
			if (spheres[i].intersection(p, dir, &tss, &n) > -0.03) {
				shadowed = true;
			}
		}
		if (mesh.intersection(p, dir, &tms, &n) > -0.03) {
			
			shadowed = true;
		}

		//Proceed to phong illumination
		
		if (!shadowed) {

			if (isPlane) {

				glm::vec3 l = glm::normalize(light.pos - p);
				float lDotN = std::max(glm::dot(l, normal), 0.0f); //must clamp l.n
				glm::vec3 r = ((2 * lDotN * normal) - l);
				glm::vec3 v = -rayDir;
				float rDotV = std::max(glm::dot(r, v), 0.0f); //must clamp r.v

				current_color += (light.dif) * ((plane.dif * lDotN) + (light.spe) * (plane.spe * pow(rDotV, plane.shi)));

			}
			else if (isSphere) {

				glm::vec3 l = glm::normalize(light.pos - p);
				float lDotN = std::max(glm::dot(l, normal), 0.0f); //must clamp l.n
				glm::vec3 r = (2 * lDotN * normal) - l;
				glm::vec3 v = -rayDir;
				float rDotV = std::max(glm::dot(r, v), 0.0f); //must clamp r.v

				current_color += (light.dif) * ((sphere.dif * lDotN) + (light.spe) * (sphere.spe * pow(rDotV, sphere.shi)));

			}
			else if (isMesh) {

				glm::vec3 l = glm::normalize(light.pos - p);
				float lDotN = std::max(glm::dot(l, normal), 0.0f); //must clamp l.n
				glm::vec3 r = (2 * lDotN * normal) - l;
				glm::vec3 v = -rayDir;
				float rDotV = std::max(glm::dot(r, v), 0.0f); //must clamp r.v

				current_color += (light.dif) * ((mesh.dif * lDotN) + (light.spe) * (mesh.spe * pow(rDotV, mesh.shi)));

			}
		}

	}

		// clamp color values

		current_color.x = std::min(1.0f, current_color.x);
		current_color.y = std::min(1.0f, current_color.y);
		current_color.z = std::min(1.0f, current_color.z);

		return current_color;
	
}
