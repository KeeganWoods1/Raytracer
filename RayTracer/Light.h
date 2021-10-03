#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "glm/glm/glm.hpp"
#include "Cimg.h"

using namespace std;

class Light 
{
public:

	glm::vec3 pos;
	glm::vec3 dif;
	glm::vec3 spe;

	Light() {

		pos = glm::vec3(0, 0, 0);
		dif = glm::vec3(0, 0, 0);
		spe = glm::vec3(0, 0, 0);
	}

	Light(glm::vec3 position, glm::vec3 diffuse, glm::vec3 specular) {

		pos = position;
		dif = diffuse;
		spe = specular;
	}
	void toString() {

		cout << "Light Info:\nPos: (" << pos.x << " " << pos.y << " " << pos.z << ")\n";
		cout << "Diffuse: (" << dif.x << " " << dif.y << " " << dif.z << ")\n";
		cout << "Specular: (" << spe.x << " " << spe.y << " " << spe.z << ")\n\n";
	}

};
