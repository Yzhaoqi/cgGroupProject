#include "MagicCube.h"

float MagicCube::gap = 0.1f;

MagicCube::MagicCube() : MagicCube(3) {}

MagicCube::MagicCube(int _order) {
	order = _order < 2 ? 2 : _order;
	positionToIndex = std::vector<std::vector<std::vector<int>>>(order,
		std::vector<std::vector<int>>(order, std::vector<int>(order)));
	cubes = std::vector<Cube>(order * order * order);
	faceToPositions = std::vector<std::vector<glm::vec3>>(3 * order);

	//compute the (0, 0, 0) world coordination and the centers
	float unitInterval = Cube::length + gap;
	float minPosX = 0, minPosY = 0, minPosZ = 0;
	centerInLocal = glm::vec3((order - 1) / 2.0f);
	centerInWorld = glm::vec3(0.0f);
	minPosX = minPosY = minPosZ = centerInWorld.x - (centerInLocal.x - 0) * unitInterval;
	
	//initilize
	size_t offsetInAll = 0;
	for (size_t i = 0; i < order; i++) {
		for (size_t j = 0; j < order; j++) {
			for (size_t k = 0; k < order; k++) {
				positionToIndex.at(i).at(j).at(k) = offsetInAll;
				cubes.at(offsetInAll) = Cube(i * unitInterval + minPosX, j * unitInterval + minPosY, k * unitInterval + minPosZ);

				auto posVec = glm::vec3(i, j, k);
				faceToPositions.at(i).push_back(posVec); //face xi
				faceToPositions.at(order + j).push_back(posVec); //face yi
				faceToPositions.at(2 * order + k).push_back(posVec); // face zi

				offsetInAll++;
			}
		}
	}

}

void MagicCube::display() {
	for (auto &c : cubes) {
		c.display();
	}
}

void MagicCube::display(int face) {
	for (auto &p : faceToPositions.at(face)) {
		cubes.at(positionToIndex.at(p.x).at(p.y).at(p.z)).display();
	}
}

void MagicCube::highlightDisplay(int face) {
	for (auto &p : faceToPositions.at(face)) {
		cubes.at(positionToIndex.at(p.x).at(p.y).at(p.z)).highlightDisplay(highlightColor);
	}
}



void MagicCube::rotateInterpolation(int face, float angle) {
	auto axis = faceToAxis(face);
	for (auto& p : faceToPositions.at(face)) {
		cubes.at(positionToIndex.at(p.x).at(p.y).at(p.z)).rotate(angle, axis.x, axis.y, axis.z);
	}
}

glm::vec3 MagicCube::rotateInterpolation(int face, float angle, glm::vec3 & pos) {
	float _angle = (float)(angle / 180 * M_PI);
	pos = glm::rotate(glm::vec3(pos.x - centerInLocal.x, pos.y - centerInLocal.y, pos.z - centerInLocal.z), _angle, faceToAxis(face));
	pos.x += centerInLocal.x;
	pos.y += centerInLocal.y;
	pos.z += centerInLocal.z;
	return pos;
}

std::vector<glm::vec3> MagicCube::rotateDestination(int face, float angle) {
	std::vector<glm::vec3> des;
	float _angle = (float)(angle / 180 * M_PI);
	for (auto &v : faceToPositions.at(face)) {
		auto _v = glm::rotate(glm::vec3(v.x - centerInLocal.x, v.y - centerInLocal.y, v.z - centerInLocal.z), _angle, faceToAxis(face));
		_v.x = ROUND(_v.x + centerInLocal.x);
		_v.y = ROUND(_v.y + centerInLocal.y);
		_v.z = ROUND(_v.z + centerInLocal.z);
		des.push_back(_v);
	}
	return des;
}

glm::vec3 MagicCube::faceToAxis(int face) {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	if (face < order && face >= 0) {
		x = 1.0f;
	} else if (face < 2 * order && face >= order) {
		y = 1.0f;
	} else {
		z = 1.0f;
	}
	return glm::vec3(x, y, z);
}
