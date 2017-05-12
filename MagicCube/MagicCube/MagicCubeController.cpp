#include "MagicCubeController.h"


MagicCubeController::MagicCubeController() : MagicCubeController(3) {}

MagicCubeController::MagicCubeController(int _order) {
	init(_order);
}

void MagicCubeController::startRotation(bool _clockwise) {
	clockwise = _clockwise;
	float angle = clockwise ? -anglePerRotation : anglePerRotation;
	desPositions = magicalCube.rotateDestination(currentFace, angle);
	controlPoint = magicalCube.faceToPositions.at(currentFace).at(0);//use face[0] as destination signal
	
	controlState = ROTATING;
}

void MagicCubeController::endRotation() {
	//at first, copy the old cube indexes into a temp variable
	int len = desPositions.size();
	std::vector<int> oldIndexes(len);
	for (size_t i = 0; i < len; i++) {
		auto p = magicalCube.faceToPositions.at(currentFace).at(i);
		oldIndexes.at(i) = magicalCube.positionToIndex.at(p.x).at(p.y).at(p.z);
	}
	//then according to the mapping from oldPositions to desPositions, apply the old cube index to the new position
	for (size_t i = 0; i < len; i++) {
		auto p = desPositions.at(i);
		magicalCube.positionToIndex.at(p.x).at(p.y).at(p.z) = oldIndexes.at(i);
	}

	controlState = IDLE;
}

//interpolate both world coodinations and control point
void MagicCubeController::rotateInterpolation() {
	if (controlState == ROTATING) {
		float angle = clockwise ? -speed : speed;
		magicalCube.rotateInterpolation(currentFace, angle); 
		magicalCube.rotateInterpolation(currentFace, angle, controlPoint);
	}
}

bool MagicCubeController::isArrivedDestination() {
	if (glm::distance(controlPoint, desPositions.at(0)) < distanceCheckStop) {
		return true;
	} else {
		return false;
	}
}

void MagicCubeController::display() {
	//the drawing order is important
	//first
	magicalCube.display();
	magicalCube.highlightDisplay(currentFace);
	//last
}

void MagicCubeController::changeCurFace(int face) {
	face = face < 0 ? 0 : face;
	face = face >= magicalCube.faceToPositions.size() ? magicalCube.faceToPositions.size() - 1 : face;

	currentFace = face;
}

int MagicCubeController::changeCurFaceRobin() {
	currentFace++;
	if (currentFace == magicalCube.faceToPositions.size()) {
		currentFace = 0;
	}
	return currentFace;
}

int MagicCubeController::changeCurFaceInLayer(bool forward) {
	int curIndex = currentFace % magicalCube.order;
	int layerOffset = currentFace / magicalCube.order;
	forward ? curIndex++ : curIndex--;
	curIndex = (curIndex < 0) ? magicalCube.order - 1 : curIndex;
	curIndex = (curIndex >= magicalCube.order) ? 0 : curIndex;
	currentFace = layerOffset * magicalCube.order + curIndex;
	return currentFace;
}

int MagicCubeController::changeCurFaceAcrossLayer() {
	int layerOffset = currentFace / magicalCube.order;
	layerOffset++;
	layerOffset %= 3;
	currentFace = layerOffset * magicalCube.order;
	return currentFace;
}

void MagicCubeController::changeCubeOrder(int _order) {
	clear();
	init(_order);
}

void MagicCubeController::init(int _order) {
	magicalCube.MagicCube::~MagicCube();
	magicalCube = MagicCube(_order);
	controlPoint = glm::vec3(0);
	desPositions = std::vector<glm::vec3>();
}

void MagicCubeController::clear() {
	currentFace = 0;
	speed = 2.0f;
	anglePerRotation = 90.0f;
	controlState = IDLE;

	clockwise = false;
}
