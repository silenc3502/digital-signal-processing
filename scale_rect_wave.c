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

	glutSwapBuffers();
}

void sineWave(void)
{
	float wavelength = 2.0 * M_PI;
	float amplitude = 1;
	float inc = 2.0 * M_PI / 1024.0;
	float k, x, y, yp = 0, y2, y2p = 0, cx, cy, cy2;
	int i, cache = 0;

	glBegin(GL_LINES);
	glColor3f(1,1,0);
	for(x=-M_PI;x<=M_PI;x+=inc)
	{
		yp = 0;

		for(i = 1; i < 10; i++)
			yp += ((1.0 - cos(i * M_PI)) / (i * M_PI)) * sin(i * x);

		y = yp + 0.5;

		if(cache)
		{
			glVertex2f(cx, cy);
			glVertex2f(x, y);
		}

		cache = 1;
		cx = x;
		cy = y;
	}
	glEnd();

	cache = 0;

	glBegin(GL_LINES);
	glColor3f(1,0,1);
	for(x=-M_PI;x<=M_PI;x+=inc)
	{
		yp = 0;

		for(i = 1; i < 10000; i++)
			yp += ((1.0 - cos(i * M_PI)) / (i * M_PI)) * sin(i * x);

		y = yp + 0.5;

		if(cache)
		{
			glVertex2f(cx, cy);
			glVertex2f(x, y);
		}

		cache = 1;
		cx = x;
		cy = y;
	}
	glEnd();
}

void originAxis(void)
{
	glBegin(GL_LINES);
	glColor3f(0,0,1);
	glVertex3f(-100,0,0);
	glVertex3f(100, 0, 0);
	glColor3f(1,0,0);
	glVertex3f(0,-100,0);
	glVertex3f(0, 100, 0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0, 0, 1);
	glEnd();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Fourier Series(Rectangular Wave)");

	glOrtho(-1.1 * M_PI, 1.1 * M_PI, -0.5, 1.3, -1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutMainLoop();

	return EXIT_SUCCESS;
}
