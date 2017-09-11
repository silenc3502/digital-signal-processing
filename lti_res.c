#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

int input_sig[5] = {-1, 0, 1, 2};
int samp[5] = {-1, 0, 1, 2};
int impulse[4] = {3, 2, 1};

void convolution(void)
{
	int i, j, in_len, pulse_len, tot_len;
	int *res;

	in_len = sizeof(input_sig) / sizeof(int) - 1;
	pulse_len = sizeof(impulse) / sizeof(int) - 1;
	tot_len = in_len + pulse_len - 1;
	printf("in_len = %d, pulse_len = %d, tot_len = %d\n",
		in_len, pulse_len, tot_len);

	res = (int *)malloc(sizeof(int) * tot_len);
	memset(res, 0, tot_len * sizeof(int));

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 3; j++)
		{
			res[i + j] += input_sig[i] * impulse[j];
			printf("input_sig[%d] * impulse[%d] = %d\n",
				input_sig[i], impulse[j], input_sig[i] * impulse[j]);
		}
	}

	for(i = 0; i < 6; i++)
		printf("res[%d] = %d\n", i, res[i]);

        glColor3f(1.0, 0.0, 1.0);

	for(i = 0; i < 6; i++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f((-1 + i) * 10, res[i] * 10);
		glVertex2f((-1 + i) * 10, 0);
		glEnd();
	}
}

void display(void)
{
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

	convolution();

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

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
			break;
	}
}

#if 0
void test(void)
{
	//glBegin(GL_LINES);
	for(; ; t += step)
	{
		if(t > 3 * period)
		{
			break;
			t = 0.0;
		}

		y2 = amp * sin(omega * t) + noise[idx++];

		//if(cache && !(cnt % 16))
		if(cache)
		{
			glBegin(GL_POINTS);
			glVertex2f(cx * 20000, cy * 5);
			glVertex2f(t * 20000, y2 * 5);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex2f(t * 20000, y2 * 5);
			glVertex2f(t * 20000, 0);
			glEnd();
		}

		cache = 1;
		cx = t;
		cy = y2;
		cnt++;
	}
	//glEnd();
	//glDisable(GL_LINE_STIPPLE);
}
#endif

int main(int argc, char **argv)
{
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
