#pragma once

#include "Cube.h"

#define ROUND(a) (int)((a) + 0.5)

class MagicCube
{
	friend class MagicCubeController;
public:
	//gap between cubes
	static float gap;

	MagicCube();
	MagicCube(int _order); //order ÊÇ½×

	//display all faces
	void display();
	void display(int face);
	void highlightDisplay(int face);
	

	//the following three functions are used to implement animation effect

	//interpolate the world coordinations of cubes
	void rotateInterpolation(int face, float angle);
	//interpolate the local coordination of a cube in MagicalCube
	glm::vec3 rotateInterpolation(int face, float angle, glm::vec3 & pos);
	//get the destination of positions of face
	std::vector<glm::vec3> rotateDestination(int face, float angle);

	//the mapping from face to axis
	glm::vec3 faceToAxis(int face);

	GLfloat highlightColor[4] = {0, 170.0f / 255.0f, 1.0f, 0.3f};
private:
	int order; //½×
	std::vector<Cube> cubes; //Indexes
	std::vector<std::vector<std::vector<int>>> positionToIndex; //the mapping from position to Index

	//the mapping from face to postions
	//the nomal of face is along x/y/z axis is caled [x/y/z][0/1/2/...]
	//order: x0, x1, x2, ... , y0, y1, y2, ... , z0, z1, z2, ...
	std::vector<std::vector<glm::vec3>> faceToPositions;

	glm::vec3 centerInLocal;
	glm::vec3 centerInWorld;
};

