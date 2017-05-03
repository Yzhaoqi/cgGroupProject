#include "Cube.h"

Cube::Cube(position _pos) : Cube(_pos, CubeColor()){}

Cube::Cube(position _pos, CubeColor _cubeColor) : Cube(_pos, _cubeColor, 3) {}

Cube::Cube(position _pos, CubeColor _cubeColor, int _order) : pos(_pos), cubeColor(_cubeColor), order(_order)
{
	//边长
	lenght = 1;

	posLocalToWorld(pos, center[0], center[1], center[2]);

	//计算正方形的顶点坐标
	float v[8][3];
	//0: left-top-back
	//1: left-top-front
	//2: left-bottom-front
	//3: left-bottom-back
	//4: right-top-back
	//5: right-top-front
	//6: right-bottom-front
	//7: right-bottom-back
	float lenHalf = lenght / 2;
	//x
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = center[0] - lenHalf;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = center[0] + lenHalf;
	//y
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = center[1] + lenHalf;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = center[1] - lenHalf;
	//z
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = center[2] - lenHalf;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = center[2] + lenHalf;

	for (int i = 0; i < 8; i++) {
		vertex[i] = glm::make_vec3(v[i]);
	}
}

void Cube::setLocation(position _pos)
{
	translate((_pos.x - pos.x) * lenght, (_pos.y - pos.y) * lenght, (_pos.z - pos.z) * lenght);

	pos = _pos;

	posLocalToWorld(pos, center[0], center[1], center[2]);
}

position Cube::getLocation()
{
	return pos;
}

void Cube::setColor(CubeColor _cubeColor)
{
	cubeColor = _cubeColor;
	
	colors[0][0] = cubeColor.left[0] / 255.0f;
	colors[0][1] = cubeColor.left[1] / 255.0f;
	colors[0][2] = cubeColor.left[2] / 255.0f;

	colors[1][0] = cubeColor.down[0] / 255.0f;
	colors[1][1] = cubeColor.down[1] / 255.0f;
	colors[1][2] = cubeColor.down[2] / 255.0f;

	colors[2][0] = cubeColor.right[0] / 255.0f;
	colors[2][1] = cubeColor.right[1] / 255.0f;
	colors[2][2] = cubeColor.right[2] / 255.0f;

	colors[3][0] = cubeColor.up[0] / 255.0f;
	colors[3][1] = cubeColor.up[1] / 255.0f;
	colors[3][2] = cubeColor.up[2] / 255.0f;

	colors[4][0] = cubeColor.front[0] / 255.0f;
	colors[4][1] = cubeColor.front[1] / 255.0f;
	colors[4][2] = cubeColor.front[2] / 255.0f;

	colors[5][0] = cubeColor.back[0] / 255.0f;
	colors[5][1] = cubeColor.back[1] / 255.0f;
	colors[5][2] = cubeColor.back[2] / 255.0f;
}

void Cube::display()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		glColor3fv(colors[i]);
		glVertex3fv(glm::value_ptr(vertex[faces[i][0]]));
		glVertex3fv(glm::value_ptr(vertex[faces[i][1]]));
		glVertex3fv(glm::value_ptr(vertex[faces[i][2]]));
		glVertex3fv(glm::value_ptr(vertex[faces[i][3]]));
	}
	glEnd();
}

void Cube::rotateCube(const int axis, const int direction)
{
	float angle = 0.0f;
	float axis_x = 0.0f;
	float axis_y = 0.0f;
	float axis_z = 0.0f;

	if (direction == CLOCKWISE) {
		angle = -90.0f;
	} else if (direction == EASTERN) {
		angle = 90.0f;
	}

	if (axis == XAXIS) {
		axis_x = 1.0f;
	} else if (axis == YAXIS) {
		axis_y = 1.0f;
	} else if (axis == ZAXIS){
		axis_z = 1.0f;
	}

	rotate(angle, axis_x, axis_y, axis_z);
}

//angle_in_degrees
void Cube::rotate(float angle, float x, float y, float z)
{
	float angle_ = angle / 180 * M_PI;
	for (auto& v : vertex) {
		v = glm::rotate(v, angle_, glm::vec3(x, y, z));
	}
}

void Cube::translate(float x, float y, float z)
{
	for (auto& v : vertex) {
		v = glm::vec3(glm::translate(glm::vec3(x, y, z)) * glm::vec4(v, 1));
	}
}

void Cube::posLocalToWorld(position p, float & x, float & y, float & z)
{
	float pos0[3]; //(0,0,0)的位置
	if (order % 2 == 0) { //如果是偶数阶
		pos0[0] = pos0[1] = pos0[2] = 0.0f - (order / 2) * lenght + (float)lenght / 2.0f;
	}
	else {
		pos0[0] = pos0[1] = pos0[2] = 0.0f - (order / 2) * lenght;
	}
	x = pos0[0] + lenght * pos.x;
	y = pos0[1] + lenght * pos.y;
	z = pos0[2] + lenght * pos.z;
}
