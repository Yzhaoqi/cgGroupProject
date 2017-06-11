#include "stdfax.h"

class SkyBox {
public:
	SkyBox();
	SkyBox(float len);
	~SkyBox();

	void display();
private:
	GLfloat length;

	// Vertex indexs for the 6 faces of a cube.
	static const GLint faces[6][4];
	glm::vec3 vertex[8];//vertex coordinates
	glm::vec3 center; //Cube cneter
};

