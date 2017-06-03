#include "Camera.h"
#include <cmath>

Camera::Camera() {
    initialCamera();
}

void Camera::initialCamera() {
    alpha = PI / 4;
    theta = PI / 8;
    radio = 5;
    calculatePos();
    is_active = false;
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
            0, 0, 0,
            UpX, UpY, UpZ
        );
    } else {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(5, 5, 5,
            0, 0, 0,
            0.0, 1.0, 0.0);
    }
}

void Camera::move(GLfloat a, GLfloat t) {
    alpha += a;
    theta += t;
    if (theta > PI / 3) {
        theta = PI / 3;
    } else if (theta < -PI / 3) {
        theta = -PI / 3;
    }
    calculatePos();
}

void Camera::getCameraPos(GLfloat & x, GLfloat & y, GLfloat & z) {
    x = cameraPosX;
    y = cameraPosY;
    z = cameraPosZ;
}

void Camera::toggle() {
    is_active = !is_active;
}

void Camera::calculatePos() {
    cameraPosX = radio*cos(theta)*cos(alpha);
    cameraPosZ = radio*cos(theta)*sin(alpha);
    cameraPosY = radio*sin(theta);
    UpX = UpZ = 0;
    UpY = 1;
    //UpX = cos(theta)*cos(alpha);
    //UpZ = cos(theta)*sin(alpha);
    //if (cameraPosY == 0) {
    //    UpY = 1;
    //} else if (cos(theta) == 0) {
    //    UpY = 0;
    //    UpX = -cos(alpha);
    //    UpZ = sin(alpha);
    //} else if (cameraPosY < 0) {
    //    UpX = -UpX;
    //    UpZ = -UpZ;
    //    UpY = (UpX * UpX + UpZ * UpZ) / sin(theta);
    //} else {
    //    UpY = (UpX * UpX + UpZ * UpZ) / (-sin(theta));
    //}
}

