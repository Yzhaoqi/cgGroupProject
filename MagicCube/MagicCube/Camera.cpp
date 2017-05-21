#include "Camera.h"
#include <cmath>

NormalVector::NormalVector() {
    x = 0;
    y = 0;
    z = 1;
}

NormalVector::NormalVector(GLfloat _x, GLfloat _y, GLfloat _z) {
    x = _x;
    y = _y;
    z = _z;
}

void NormalVector::operator=(NormalVector a) {
    x = a.x;
    y = a.y;
    z = a.z;
}

Camera::Camera() {
    cameraFront = NormalVector(0, 0, -1);
    cameraUp = NormalVector(0, 1, 0);
    cameraRight = NormalVector(-1, 0, 0);
    is_active = false;
}

void Camera::initialCamera() {
    cameraPosX = 0;
    cameraPosY = 0;
    cameraPosZ = -5;
}

void Camera::activateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 0.1, 100);
    if (is_active) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(
            cameraPosX, cameraPosY, cameraPosZ,
            cameraPosX - cameraFront.x, cameraPosY - cameraFront.y, cameraPosZ - cameraFront.z,
            cameraUp.x, cameraUp.y, cameraUp.z
        );
    } else {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(5, 5, 5,
            0, 0, 0,
            0.0, 1.0, 0.0);
    }
}

void Camera::move(int direction, GLfloat const distance) {
    if (!is_active) return;
    switch (direction) {
    case MOVE_FORWARD:
        moveForward(distance);
        break;
    case MOVE_BACK:
        moveBack(distance);
        break;
    case MOVE_RIGHT:
        moveRight(distance);
        break;
    case MOVE_LEFT:
        moveLeft(distance);
        break;
    }
}

void Camera::rotate(GLfloat const pitch, GLfloat const yaw) {
    cameraFront.x = -sin(yaw)*cos(pitch);
    cameraFront.y = sin(pitch);
    cameraFront.z = -cos(yaw)*cos(pitch);

    cameraUp.x = sin(yaw)*sin(pitch);
    cameraUp.y = cos(pitch);
    cameraUp.z = cos(yaw)*sin(pitch);

    cameraRight.x = -cos(yaw);
    cameraRight.z = sin(yaw);
}

void Camera::getCameraPos(GLfloat & x, GLfloat & y, GLfloat & z) {
    x = cameraPosX;
    y = cameraPosY;
    z = cameraPosZ;
}

void Camera::getCameraFront(GLfloat & x, GLfloat & y, GLfloat & z) {
    x = cameraFront.x;
    y = cameraFront.y;
    z = cameraFront.z;
}

void Camera::toggle() {
    is_active = !is_active;
}

void Camera::moveForward(GLfloat const distance) {
    cameraPosX += -distance * cameraFront.x;
    cameraPosY += -distance * cameraFront.y;
    cameraPosZ += -distance * cameraFront.z;
}

void Camera::moveBack(GLfloat const distance) {
    moveForward(-distance);
}

void Camera::moveRight(GLfloat const distance) {
    cameraPosX += distance * cameraRight.x;
    cameraPosY += distance * cameraRight.y;
    cameraPosZ += distance * cameraRight.z;
}

void Camera::moveLeft(GLfloat const distance) {
    moveRight(-distance);
}
