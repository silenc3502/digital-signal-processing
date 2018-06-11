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
	float wavelength = 2.0 * M_PI;
	float amplitude = 1;
	float inc = 2.0 * M_PI / 256.0;
	float k, x, y, yp = 0, cx, cy;
	int cache = 0;

	glBegin(GL_LINES);
	glColor3f(0,1,0);
	for(x=-M_PI;x<=M_PI;x+=inc){
		k = 2 * 3.14 / wavelength;
		y = amplitude * sin(k * x);

		if(cache)
		{
			glVertex2f(cx, cy);
			glVertex2f(x, y);
		}

		cache = 1;
		cx = x;
		cy = y;

		printf("x = %f, y = %f\n", x, y);
	}
	glEnd();

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

	glOrtho(-M_PI, M_PI, -2.0, 2.0, -1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutMainLoop();

	return EXIT_SUCCESS;
}
