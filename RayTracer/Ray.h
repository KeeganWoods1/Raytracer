#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "glm/glm/glm.hpp"
#include "Cimg.h"

using namespace std;

class Ray 
{
	public:

		unsigned int originatingPixel;
		glm::vec3 direction;
		glm::vec3 color;

		Ray() {

			originatingPixel = 0;
			direction = glm::vec3(0, 0, 0);
		}

		Ray(glm::vec3 dir) {
		
			direction = glm::vec3(dir.x, -dir.y, dir.z); // -dir.y to establish "up" side of objects
		}
		void toString() {
			cout << "Ray dir:\n(" << direction.x << " " << direction.y << " " << direction.z << ")";
		}

};
