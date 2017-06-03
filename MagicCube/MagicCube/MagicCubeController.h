#pragma once

#include "MagicCube.h"

class MagicCubeController {
public:
	MagicCubeController();
	MagicCubeController(int _order);
	
	//call when starting rotation
	void startRotation(bool clockwise);
	//call when ending rotation
	void endRotation();
	//call when rotating in glutIdle function
	void rotateInterpolation();
	//check if arriving destination
	//If arrived, please call endRotation()
	bool isArrivedDestination();
	//To display in the window
	void display(bool is_texture_on);
	
	//change currentFace in many ways...
	void changeCurFace(int face);
	int changeCurFaceRobin();
	int changeCurFaceInLayer(bool forward);
	int changeCurFaceAcrossLayer();

	//change the cube order
	void changeCubeOrder(int _order);

	//the states used to control animation
	enum State {
		ROTATING,
		IDLE
	} controlState = IDLE;

	//the Index of face that controlling now
	int currentFace = 0;
	//rotate speed
	float speed = 2.0f;

	//anticlockwise when > 0
	float anglePerRotation = 90.0f;
private:
	MagicCube magicalCube;
	//used to control the animation ending
	glm::vec3 controlPoint;
	//when ending rotation, need to update the indexes of cube
	std::vector<glm::vec3> desPositions;
	//used to control the rotation direction
	//true if it is clockwise, else if it is anticlockwise
	bool clockwise;

	//animation stop when the distance between control point and destination point less than this distance[Euclidean] 
	const float distanceCheckStop = 0.001f;

	void init(int _order = 3);
	void clear();
};

