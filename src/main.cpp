#define WIDTH 1000
#define HEIGHT 800
#include "GL/gl.h"
#include "GL/glut.h"
#include "GL/glu.h"

#include "../include/game.h"
#include "../include/light.h"

Light *Light::instance = nullptr;

Game *game;

static void mouseMoveWrapper(int x, int y)
{
	game->handleMouseMove(x, y);
}

static void mouseClickWrapper(int button, int status, int x, int y)
{
	game->handleMouseClick(button, status, x, y);
}

static void update(int value)
{
	game->update();
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

static void draw()
{
	game->draw();
}

static void handleKeyboardWrapper(unsigned char key, int x, int y)
{
	game->handleKeyboard(key);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowPosition(1420, 580);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("Side Pocket");

	game = new Game();

	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glutSwapBuffers();
	glutPassiveMotionFunc(mouseMoveWrapper);
	glutDisplayFunc(draw);
	glutKeyboardFunc(handleKeyboardWrapper);
	glutTimerFunc(10, update, 0);
	glutMouseFunc(mouseClickWrapper);

	glutMainLoop();

	return 0;
}
