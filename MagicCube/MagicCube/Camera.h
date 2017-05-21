#pragma once
#include <windows.h>
#include <GL/GLU.h>

#define MOVE_FORWARD 1
#define MOVE_BACK 2
#define MOVE_RIGHT 3
#define MOVE_LEFT 4

struct NormalVector {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    NormalVector();
    NormalVector(GLfloat _x, GLfloat _y, GLfloat _z);
    void operator = (NormalVector a);
};

class Camera {
public:
    Camera();
    void initialCamera();
    void activateCamera();
    void move(int direction, GLfloat const distance);
    void rotate(GLfloat const pitch, GLfloat const yaw);
    void getCameraPos(GLfloat &x, GLfloat &y, GLfloat &z);
    void getCameraFront(GLfloat &x, GLfloat &y, GLfloat &z);
    void toggle();
private:
    void moveForward(GLfloat const distance);
    void moveBack(GLfloat const distance);
    void moveRight(GLfloat const distance);
    void moveLeft(GLfloat const distance);
private:
    GLfloat cameraPosX, cameraPosY, cameraPosZ;
    NormalVector cameraFront;
    NormalVector cameraRight;
    NormalVector cameraUp;
    bool is_active;
};