#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Plane.h"
#include "Sphere.h"
#include "Light.h"
#include "Mesh.h"
#include "glm/glm/glm.hpp"
#include "Cimg.h"

using namespace std;

bool loadScene(
	const char * path,
	 Camera & temp_cam,
	 Plane & temp_plane,
	 std::vector<Sphere> & scene_spheres,
	 std::vector<Light> & scene_lights,
	 Mesh & temp_mesh){

	int num_of_objects = 0;

	FILE * file;
	int _errno = fopen_S(&file, path, "r");
	if (_errno != 0) 
	{
		printf("(LoadScene)Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "camera") == 0) {

			float cam_pos_x, cam_pos_y, cam_pos_z, cam_fov, cam_f, cam_a;

			fscanf_s(file, "\npos: %f %f %f\nfov: %f\nf: %f\na: %f\n", 
				&cam_pos_x, &cam_pos_y, &cam_pos_z, 
				&cam_fov, 
				&cam_f, 
				&cam_a);

			temp_cam.pos = glm::vec3(cam_pos_x, cam_pos_y, cam_pos_z);
			temp_cam.fov = cam_fov; 
			temp_cam.f = cam_f;
			temp_cam.a = cam_a;

		}
		else if (strcmp(lineHeader, "plane") == 0) {

			Plane pln;
			float pln_nor_x, pln_nor_y, pln_nor_z,
				  pln_pos_x, pln_pos_y, pln_pos_z,
				  pln_amb_x, pln_amb_y, pln_amb_z,
				  pln_dif_x, pln_dif_y, pln_dif_z,
				  pln_spe_x, pln_spe_y, pln_spe_z,
				  pln_shi;

			fscanf_s(file, "\nnor: %f %f %f\npos: %f %f %f\namb: %f %f %f\ndif: %f %f %f\nspe: %f %f %f\nshi: %f\n", 
				&pln_nor_x, &pln_nor_y, &pln_nor_z,
				&pln_pos_x, &pln_pos_y, &pln_pos_z, 
				&pln_amb_x, &pln_amb_y, &pln_amb_z,
				&pln_dif_x, &pln_dif_y, &pln_dif_z,
				&pln_spe_x, &pln_spe_y, &pln_spe_z,
				&pln_shi);

			temp_plane.nor = glm::vec3(pln_nor_x, pln_nor_y, pln_nor_z);
			temp_plane.pos = glm::vec3(pln_pos_x, pln_pos_y, pln_pos_z);
			temp_plane.amb = glm::vec3(pln_amb_x, pln_amb_y, pln_amb_z);
			temp_plane.dif = glm::vec3(pln_dif_x, pln_dif_y, pln_dif_z);
			temp_plane.spe = glm::vec3(pln_spe_x, pln_spe_y, pln_spe_z);
			temp_plane.shi = pln_shi;
			
		}
		else if (strcmp(lineHeader, "sphere") == 0) {

			Sphere spr;
			float spr_pos_x, spr_pos_y, spr_pos_z,
				  spr_rad,
				  spr_amb_x, spr_amb_y, spr_amb_z,
				  spr_dif_x, spr_dif_y, spr_dif_z,
				  spr_spe_x, spr_spe_y, spr_spe_z,
				  spr_shi;

			fscanf_s(file, "\npos: %f %f %f\nrad: %f\namb: %f %f %f\ndif: %f %f %f\nspe: %f %f %f\nshi: %f\n",
				&spr_pos_x, &spr_pos_y, &spr_pos_z,
				&spr_rad,						
				&spr_amb_x, &spr_amb_y, &spr_amb_z,
				&spr_dif_x, &spr_dif_y, &spr_dif_z,
				&spr_spe_x, &spr_spe_y, &spr_spe_z,
				&spr_shi);
				
			spr.pos = glm::vec3(spr_pos_x, spr_pos_y, spr_pos_z);
			spr.rad = spr_rad;
			spr.amb = glm::vec3(spr_amb_x, spr_amb_y, spr_amb_z);
			spr.dif = glm::vec3(spr_dif_x, spr_dif_y, spr_dif_z);
			spr.spe = glm::vec3(spr_spe_x, spr_spe_y, spr_spe_z);
			spr.shi = spr_shi;

			scene_spheres.push_back(spr);

		}
		else if (strcmp(lineHeader, "light") == 0) {

			Light lgt;
			float lgt_pos_x, lgt_pos_y, lgt_pos_z,
				  lgt_dif_x, lgt_dif_y, lgt_dif_z,
				  lgt_spe_x, lgt_spe_y, lgt_spe_z;

			fscanf_s(file, "\npos: %f %f %f\ndif: %f %f %f\nspe: %f %f %f\n",
				&lgt_pos_x, &lgt_pos_y, &lgt_pos_z,
				&lgt_dif_x, &lgt_dif_y, &lgt_dif_z,
				&lgt_spe_x, &lgt_spe_y, &lgt_spe_z);

			lgt.pos = glm::vec3(lgt_pos_x, lgt_pos_y, lgt_pos_z);
			lgt.dif = glm::vec3(lgt_dif_x, lgt_dif_y, lgt_dif_z);
			lgt.spe = glm::vec3(lgt_spe_x, lgt_spe_y, lgt_spe_z);

			scene_lights.push_back(lgt);
			
		}
		else if (strcmp(lineHeader, "mesh") == 0) {

			Mesh msh;
			char msh_file[128];
			float 
				  msh_amb_x, msh_amb_y, msh_amb_z,
				  msh_dif_x, msh_dif_y, msh_dif_z,
				  msh_spe_x, msh_spe_y, msh_spe_z,
				  msh_shi;

			fscanf_s(file, "\nfile: %s\namb: %f %f %f\ndif: %f %f %f\nspe: %f %f %f\nshi: %f\n",
				msh_file, 128,
				&msh_amb_x, &msh_amb_y, &msh_amb_z,
				&msh_dif_x, &msh_dif_y, &msh_dif_z,
				&msh_spe_x, &msh_spe_y, &msh_spe_z,
				&msh_shi);

			temp_mesh.file = msh_file;
			temp_mesh.amb = glm::vec3(msh_amb_x, msh_amb_y, msh_amb_z);
			temp_mesh.dif = glm::vec3(msh_dif_x, msh_dif_y, msh_dif_z);
			temp_mesh.spe = glm::vec3(msh_spe_x, msh_spe_y, msh_spe_z);
			temp_mesh.shi = msh_shi;

			temp_mesh.loadMesh(msh_file);

		}
		else {
			fscanf_s(file, "%d\n", &num_of_objects);
			cout << "Loading scene objects\n";
		}
	}
	return true;
}

	

