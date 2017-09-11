#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

void originAxis(void);
void sineWave(void);
void idle(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	originAxis();
	sineWave();

	//printf("%s\n", gluErrorString(glGetError()));
	glutSwapBuffers();
}

void sineWave(void)
{
	float wavelength = 2;
	float amplitude = 1;
	float inc = 0.05;
	float k, x, y;
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	for(x=-1;x<=1;x+=inc){
		k = 2 * 3.14 / wavelength;
		y = amplitude * sin(k * x);
		glVertex3f(x, y, 0);
	}
	glEnd();

}

void idle(void)
{
	float wavelength = 2;
	float amplitude = 1;
	float inc = 0.05;
	float k, x, y;
	for (x = -1; x <= 1; x += inc){
		glBegin(GL_POINTS);
		glPointSize(200);
		glColor3f(0, 1, 0);
		k = 2 * 3.14 / wavelength;
		y = amplitude * sin(k * x);
		glVertex3f(x, y, 0);
		glEnd();
	}

	glutPostRedisplay();
}

void originAxis(void)
{
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1, 0, 0);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0, 1, 0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0, 0, 1);
	glEnd();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Tutorial 2");

	glOrtho(-1, 1, -1, 1, -1, 1);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

	return EXIT_SUCCESS;
}
