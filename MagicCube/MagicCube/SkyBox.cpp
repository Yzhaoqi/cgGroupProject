#include "SkyBox.h"

static GLfloat texMapping[6][4][2]{
	{ { 0.0, 1.0f / 3 },{ 0.0, 2.0f / 3 },{ 0.25, 2.0f / 3 },{ 0.25, 1.0f / 3 } },
	{ { 0.25, 1.0f / 3 },{ 0.25, 2.0f / 3 },{ 0.5, 2.0f / 3 },{ 0.5, 1.0f / 3 } },
	{ { 0.5, 1.0f / 3 },{ 0.5, 2.0f / 3 },{ 0.75, 2.0f / 3 },{ 0.75, 1.0f / 3 } },
	{ { 0.75, 1.0f / 3 },{ 0.75, 2.0f / 3 },{ 1, 2.0f / 3 },{ 1, 1.0f / 3 } },
	{ { 0.5, 2.0f / 3 },{ 0.5, 1 },{ 0.75, 1 },{ 0.75, 2.0f / 3 } },
	{ { 0.5, 0 },{ 0.5, 1.0f / 3 },{ 0.75, 1.0f / 3 },{ 0.75, 0 } }
};

extern GLuint textureID;

GLint const SkyBox::faces[6][4] = {
	{ 0, 1, 2, 3 },//left
	{ 3, 2, 6, 7 },//bottom
	{ 7, 6, 5, 4 },//right
	{ 4, 5, 1, 0 },//top
	{ 5, 6, 2, 1 },//front
	{ 7, 4, 0, 3 } //back
};

SkyBox::SkyBox() : SkyBox(20) {}

SkyBox::SkyBox(float len) {
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	GLfloat v[8][3];
	this->length = len;
	GLfloat lenHalf = length / 2;
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


SkyBox::~SkyBox() {}

void SkyBox::display() {
	glBindTexture(GL_TEXTURE_2D, textureID);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glTexCoord2f(texMapping[i][j][0], texMapping[i][j][1]);
			glVertex3fv(glm::value_ptr(vertex[faces[i][j]]));
		}
	}
	glEnd();
}
