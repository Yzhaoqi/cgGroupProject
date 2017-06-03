#pragma once
#include <windows.h>
#include <GL/GLU.h>

#define PI 3.141592653589793238462643383279502384197169399375105
#define MININUM 0.000000000000000001

class Camera {
public:
    Camera();
    void initialCamera();
    void activateCamera();
    void move(GLfloat a, GLfloat t);
    void getCameraPos(GLfloat &x, GLfloat &y, GLfloat &z);
    void toggle();
private:
    void calculatePos();
private:
    GLfloat cameraPosX, cameraPosY, cameraPosZ;
    GLfloat UpX, UpY, UpZ;
    GLfloat radio;
    GLfloat alpha, theta;
    bool is_active;
};