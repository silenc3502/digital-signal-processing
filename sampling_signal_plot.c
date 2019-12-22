#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

#define SLICE	360

void draw_omega_sin(float);
void draw_sin(void);

float common_angles[5] = {15.0, 30.0, 45.0, 60.0, 75.0};
float freq_table[5] = {1000.0, 2400.0, 5000.0, 24000.0, 77000.0};

float theta = 0.0;

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
		glVertex3f(150.0, 0.0, 0.0);
        glVertex3f(-150.0, 0.0, 0.0);
    glEnd();

	glColor3f(0, 1, 0);

    glBegin(GL_LINE_LOOP);
        glVertex3f(0.0, 100.0, 0.0);
        glVertex3f(0.0, -100.0, 0.0);
    glEnd();

	draw_sin();

	glColor3f(0, 1, 0);
	glPointSize(25.0);
	draw_omega_sin(5);

	glColor3f(1, 0, 1);
	glPointSize(15.0);
	draw_omega_sin(4);

	glColor3f(0, 0, 1);
	glPointSize(7.0);
	draw_omega_sin(3);

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

void calc_period(float *freq, float *period)
{
	*period = 1 / (*freq);
}

void calc_angular_velocity(float *freq, float *ang_vel)
{
	*ang_vel = 2 * M_PI * (*freq);
}

float get_step(float slice, float period)
{
	return period / slice;
}

void draw_sin(void)
{
	float amp, period, freq, omega = 0, t = 0.0, step = 0.0;
	float x2 = 0, y2 = 0, cx, cy;
	int cache = 0;

	amp = 35;
	freq = 1;

	calc_period(&freq, &period);
	calc_angular_velocity(&freq, &omega);

	step = get_step(SLICE, period);

	if(t > period)
		t = 0.0;

	glBegin(GL_LINES);
	for(; ; t += step)
	{
		if(t > 3 * period)
		{
			break;
		}

		y2 = amp * sin(omega * t);

		if(cache)
		{
			glVertex2f(-70 + cx * 150, cy);
			glVertex2f(-70 + t * 150, y2);
		}

		cache = 1;
		cx = t;
		cy = y2;
		printf("period = %f, t = %f, y2 = %f\n", period, -70 + t * 150, y2);
	}
	glEnd();
}

void draw_omega_sin(float sample_freq)
{
	float amp, period, freq, omega = 0, t = 0.0, step = 0.0, slice, tmp;
	float x2 = 0, y2, cx, cy, scale_factor;
	int cache = 0;

	amp = 35;
	freq = 1.0;

	calc_period(&freq, &tmp);
	
	calc_period(&sample_freq, &period);
	calc_angular_velocity(&freq, &omega);

	step = get_step(sample_freq / freq, tmp);

	scale_factor = 150.0;

	printf("signal period = %f, step = %f, w = %f\n", tmp, step, omega);

	if(t > tmp)
		t = 0.0;

	for(; ; t += step)
	{
		if(t > 3 * tmp)
			break;

		y2 = amp * sin(omega * t);
		printf("y2 = %f\n", y2);

		if(cache)
		{
			glBegin(GL_POINTS);
				glVertex2f(-70 + cx * 150, cy);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glVertex2f(-70 + cx * 150, cy);
				glVertex2f(-70 + cx * 150, 0);
			glEnd();
		}

		cache = 1;
		cx = t;
		cy = y2;
		printf("t = %f, y2 = %f\n", -70 + t * 150, y2);
	}
}

int main(int argc, char **argv)
{
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
