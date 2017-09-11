#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include <math.h>


//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float rotate =0.0;

float start = 0.0;
void drawSinWave()
{
	float radius = 7.5;
	float x2=0,y2,cx,cy,fx,fy;
	float cos_y,cache_cos_y;
	int cache = 0;
	start += 1.0;
	if(start >360) {
		start = 0;
	}
	glBegin(GL_LINES);
	float angle = 0;
	for(angle=start; ; angle+=1.0) {
		if(angle>1020) {
			break;
			angle = 0.0;
		}
		float rad_angle = angle * 3.14 / 180;
		x2 = x2+0.1;
		y2 = radius * sin((double)rad_angle);
		cos_y = radius * sin((double)-rad_angle);
		if (cache) {
			glVertex2f(cx,cy);
			glVertex2f(x2,y2);

			glVertex2f(cx,cache_cos_y);
			glVertex2f(x2,cos_y);

		} else {
			fx = x2;
			fy = y2;
		}
		cache = 1;
		cx = x2;
		cy = y2;
		cache_cos_y = cos_y;
	}
	glEnd();
}

void display(void) {
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glLineWidth(10);
	glLoadIdentity();
	glTranslatef(-40,0,-30);
	glColor3f(1,0,0);

	drawSinWave();
	glutSwapBuffers();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
	}
}

int main (int argc, char **argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE);
	glutInitWindowSize (1200, 800);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("A Sine wave");

	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc (keyboard);
	glutMainLoop ();
	return 0;
}
