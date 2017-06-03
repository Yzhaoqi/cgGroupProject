#include "stdfax.h"
#include "MagicCubeController.h"
#include "Camera.h"
#include "SOIL.h"

GLuint textureID;

MagicCubeController mcc;
Camera camera;
float mouseX, mouseY;
float yaw, pitch;

bool toggle_texture;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.activateCamera();
	mcc.display(toggle_texture);
	glutSwapBuffers();
}

void idle() {
	if (clock() % (CLOCKS_PER_SEC / 60) == 0) { //FPS = 60
		switch (mcc.controlState) {
		case MagicCubeController::IDLE :
			break;
		case MagicCubeController::ROTATING :
			mcc.rotateInterpolation();
			if (mcc.isArrivedDestination()) {
				mcc.endRotation();
			}
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        mouseX = x;
        mouseY = y;
    }
}

void mouseMotion(int x, int y) {
}

void keyboard(unsigned char key, int x, int y) {
	if (mcc.controlState == MagicCubeController::IDLE) {
        switch (key) {
        case 'w':
            camera.move(0, -0.1);
            break;
        case 's':
            camera.move(0, 0.1);
            break;
        case 'a':
            camera.move(-0.1, 0);
            break;
        case 'd':
            camera.move(0.1, 0);
            break;
        case 't':
            toggle_texture = !toggle_texture;
            break;
        }
	}
}

void specialKeyboard(int key, int x, int y) {
	if (mcc.controlState == MagicCubeController::IDLE) {
		switch (key) {
		case GLUT_KEY_SHIFT_L:
			mcc.changeCurFaceAcrossLayer();
			break;
		case GLUT_KEY_LEFT:
			mcc.changeCurFaceInLayer(false);
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			mcc.changeCurFaceInLayer(true);
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			mcc.startRotation(false);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			mcc.startRotation(true);
			glutPostRedisplay();
			break;
        case GLUT_KEY_CTRL_L:
            camera.toggle();
            break;
		default:
			break;
		}
	}
}

void reshape(int w, int h) {
	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5,
        0, 0, 0,     /* center is at (0, 0, 0) */
        0.0, 1.0, 0.0);      /* up is in positive Y direction */
}

void selectMagicalCube(int order) {
	if (mcc.controlState == MagicCubeController::IDLE) {
		mcc.changeCubeOrder(order);
	}
}

void mainMenu(int i) {}

void addMenu() {
	int selectCube_submenu;

	selectCube_submenu = glutCreateMenu(selectMagicalCube);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);

	glutCreateMenu(mainMenu);
	glutAddSubMenu("order", selectCube_submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initLight() {
    glEnable(GL_LIGHTING);
    glLoadIdentity();
	GLfloat light_position[] = { -5.0f, 5.0f, -5.0f, 1.0 };
    GLfloat light1_position[] = {5.0f, 5.0f, 5.0f, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);
}

GLuint textureFromFile(std::string path) {
	//Generate texture ID and load texture data
	std::string filename = path;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == 0) std::cout << "no";
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureID;
}

int main(int argc, char* argv) {
    camera.initialCamera();
    pitch = yaw = 0;
    toggle_texture = false;

	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("MagicalCube");
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	textureID = textureFromFile("awesomeface1.png");

    initLight();

	glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeyboard);
    
	addMenu();

	glutMainLoop();
	return 0;
}