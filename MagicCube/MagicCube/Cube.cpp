#include "Cube.h"

GLfloat texMapping[6][4][2]{
    { { 0.0, 1.0f / 3 },{ 0.0, 2.0f / 3 },{ 0.25, 2.0f / 3 },{ 0.25, 1.0f / 3 } },
    { { 0.25, 1.0f / 3 },{ 0.25, 2.0f / 3 },{ 0.5, 2.0f / 3 },{ 0.5, 1.0f / 3 } },
    { { 0.5, 1.0f / 3 },{ 0.5, 2.0f / 3 },{ 0.75, 2.0f / 3 },{ 0.75, 1.0f / 3 } },
    { { 0.75, 1.0f / 3 },{ 0.75, 2.0f / 3 },{ 1, 2.0f / 3 },{ 1, 1.0f / 3 } },
    { { 0.5, 2.0f / 3 },{ 0.5, 1 },{ 0.75, 1 },{ 0.75, 2.0f / 3 } },
    { { 0.5, 0 },{ 0.5, 1.0f / 3 },{ 0.75, 1.0f / 3 },{ 0.75, 0 } }
};

extern GLuint textureID;

GLint const Cube::faces[6][4] = {
	{ 0, 1, 2, 3 },//left
	{ 3, 2, 6, 7 },//bottom
	{ 7, 6, 5, 4 },//right
	{ 4, 5, 1, 0 },//top
	{ 5, 6, 2, 1 },//front
	{ 7, 4, 0, 3 } //back
};

GLfloat Cube::length = 1;

Cube::Cube() : Cube(0, 0, 0) {
}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z) : center{ x, y, z } {
	GLfloat v[8][3];
	//0: left-top-back
	//1: left-top-front
	//2: left-bottom-front
	//3: left-bottom-back
	//4: right-top-back
	//5: right-top-front
	//6: right-bottom-front
	//7: right-bottom-back
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

	normals[0] = glm::vec3(-1, 0, 0);
	normals[1] = glm::vec3(0, -1, 0);
	normals[2] = glm::vec3(1, 0, 0);
	normals[3] = glm::vec3(0, 1, 0);
	normals[4] = glm::vec3(0, 0, 1);
	normals[5] = glm::vec3(0, 0, -1);
}

void Cube::display(bool is_texture_on) {
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        if (!is_texture_on) glColor3fv(colors[i]);
        else glColor3f(1.0, 1.0, 1.0);
        glNormal3fv(glm::value_ptr(normals[0]));
        for (int j = 0; j < 4; j++) {
            if(is_texture_on) glTexCoord2f(texMapping[i][j][0], texMapping[i][j][1]);
            glVertex3fv(glm::value_ptr(vertex[faces[i][j]]));
        }
    }
	glEnd();
}

void Cube::highlightDisplay(const GLfloat* color) {
	//启用融合效果
	//If enabled, blend the computed fragment color values with the values in the color buffers.
	glEnable(GL_BLEND);
	//设置融合方式
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		glColor4fv(color);
		glVertex3fv(glm::value_ptr(vertex[faces[i][0]] + (vertex[faces[i][0]] - center) * 0.1f));
		glVertex3fv(glm::value_ptr(vertex[faces[i][1]] + (vertex[faces[i][1]] - center) * 0.1f));
		glVertex3fv(glm::value_ptr(vertex[faces[i][2]] + (vertex[faces[i][2]] - center) * 0.1f));
		glVertex3fv(glm::value_ptr(vertex[faces[i][3]] + (vertex[faces[i][3]] - center) * 0.1f));
	}
	glEnd();

	glDisable(GL_BLEND);
}

//angle_in_degrees
void Cube::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat angle_ = angle / 180 * M_PI;
	glm::mat4 rotationMatrix = glm::rotate(angle_, glm::vec3(x, y, z));
	for (auto& v : vertex) {
	//	v = glm::rotate(v, angle_, glm::vec3(x, y, z));
		v = glm::vec3(rotationMatrix * glm::vec4(v, 1.0f));
	}
	center = glm::rotate(center, angle_, glm::vec3(x, y, z));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(rotationMatrix));
	for (size_t i = 0; i < 6; i++) {
		normals[i] = glm::vec3(rotationMatrix * glm::vec4(normals[i], 1.0f));
	}
}
