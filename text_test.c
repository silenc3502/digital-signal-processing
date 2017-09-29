#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>

void drawString (char *s)
{
	unsigned int i;

	for (i = 0; i < strlen (s); i++)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_10, s[i]);
}

void drawStringBig (char *s)
{
	unsigned int i;

	for (i = 0; i < strlen (s); i++)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, s[i]);
}

void display(void)
{
	static char label[100];

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(-100.0, 0.0, 0.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 100.0, 0.0);
	glVertex3f(0.0, -100.0, 0.0);
	glEnd();

	//draw_omega_sin();
	glColor3f (1.0F, 1.0F, 1.0F);
	sprintf (label, "X Axis");
	glRasterPos2f (101.0, 0.0);
	drawStringBig (label);

	glColor3f (1.0F, 1.0F, 1.0F);
	sprintf (label, "Y Axis ");
	glRasterPos2f (1.0, 95.0);
	drawStringBig (label);

	glColor3f (1.0F, 1.0F, 1.0F);
	sprintf (label, "O");
	glRasterPos2f (0.85, 0.85);
	drawString (label);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	GLfloat n_range = 100.0f;

	if(h == 0)
		h = 1;

        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if(w <= h)
                glOrtho(-n_range, n_range, -n_range * h / w, n_range * h / w, -n_range, n_range);
        else
                glOrtho(-n_range * w / h, n_range * w / h, -n_range, n_range, -n_range, n_range);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

int main(int argc, char **argv)
{
        float amplitude, angle, period, frequency, radian, angular_velocity;
        float step = 0.0;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE);
        glutInitWindowSize(1200, 800);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Digital Signal Processing");

	glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutMainLoop();

        return 0;
}
