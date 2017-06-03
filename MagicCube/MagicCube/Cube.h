#pragma once

#include "stdfax.h"

class Cube
{
public:
	Cube();
	Cube(GLfloat x, GLfloat y, GLfloat z); //center location
	void display(bool is_texture_on); //use in the glut display function
	void highlightDisplay(const GLfloat* color);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z); //Like glRoatef

    //Cube Length, they are the same in a MagicalCube
	static GLfloat length; 
private:
	// Vertex indexs for the 6 faces of a cube.
	static const GLint faces[6][4];
	

	glm::vec3 vertex[8];//vertex coordinates
	GLfloat colors[6][3] {
		{ 1, 0, 0 },//red -- left
		{ 0, 1, 0 },//green -- bottom
		{ 0, 0, 1 },//blue -- right
		{ 1, 1, 0 },//yellow -- top
		{ 1, 0, 1 },//magenta -- front
		{ 0, 1, 1 } //cyan -- back
	};

	glm::vec3 normals[6];
	glm::vec3 center; //Cube cneter
	
};

