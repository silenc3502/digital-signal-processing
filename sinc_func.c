#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/glut.h>

#define SLICE	360

void draw_omega_sin(void);

float common_angles[5] = {15.0, 30.0, 45.0, 60.0, 75.0};
float freq_table[5] = {1000.0, 2400.0, 5000.0, 24000.0, 77000.0};

float theta = 0.0;

void rect_pulse_signal(void)
{
	float t, T = 0.01;
	float amp = 100;
	float step = 0.0;
	float omega = 2 * M_PI * 100;	// frequency = 5 Hz
	float x = 0, x2 = 0, y, cx, cy;
	int cache = 0;

	//t = step = T / 100;
	step = T / 100;
	t = -3 * T;

	printf("step = %f\n", step);

	if(t > T)
		t = 0.0;
	
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	for(; ; t += step)
	{
		if(t > 3 * T)
		{
			break;
			t = 0.0;
		}

		//float rad_angle = angle * (M_PI / 180.0);
		//x2 += x;		// time += step;
		//x2 += 0.1;
		y = amp * (sin(omega * t) / (omega * t));
		//y2 = radius * sin((double)rad_angle);

		if(cache)
		{
			glVertex2f(cx * 3000, cy * 1);
			glVertex2f(t * 3000, y * 1);
		}

		cache = 1;
		cx = t;
		cy = y;
		printf("t = %f, y = %f\n", t * 3000, y * 1);
	}
	glEnd();
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

	rect_pulse_signal();
	//draw_omega_sin();
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

void set_rand_amplitude(float *amp)
{
	*amp = rand() % 3 + 3;
}

void set_angle_with_common_angles(float *angle)
{
	*angle = common_angles[rand() % 5];
}

void angle2radian(float *angle, float *radian)
{
	*radian = *angle * M_PI / 180.0;
}

void radian2angle(float *angle, float *radian)
{
	*angle = *radian * 180.0 / M_PI;
}

void set_rand_frequency(float *freq)
{
	*freq = freq_table[rand() % 5];
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

void cos_sim(float amplitude, float ang_vel, float period)
{
	int cnt = 0;
	float step, t = 0.0;

	t = step = get_step(SLICE, period);

	while(cnt++ < 36)
	{
		printf("%.1fcos(%f * %.8f) = %f\n", amplitude, ang_vel,
			t, amplitude * cos(ang_vel * t));
		t += step;
	}
}

void sin_sim(float amplitude, float ang_vel, float period)
{
	int cnt = 0;
	float step, t = 0.0;

	t = step = get_step(SLICE, period);

	while(cnt++ < 36)
	{
		printf("%.1fsin(%f * %.8f) = %f\n", amplitude, ang_vel,
			t, amplitude * sin(ang_vel * t));
		t += step;
	}
}

void draw_omega_sin(void)
{
	float amp, angle, period, freq, rad, omega, t, step = 0.0;
	float radius = 3.0;
	float x = 0, x2 = 0, y2, cx, cy;
	float tmp;
	int cache = 0;

	srand(time(NULL));

	amp = 10;
	freq = 100.0;
	
	calc_period(&freq, &period);
	calc_angular_velocity(&freq, &omega);

	t = step = get_step(SLICE, period);

	if(t > period)
		t = 0.0;

	glBegin(GL_LINES);
	for(; ; t += step)
	{
		if(t > 3 * period)
		{
			break;
			t = 0.0;
		}

		//float rad_angle = angle * (M_PI / 180.0);
		//x2 += x;		// time += step;
		//x2 += 0.1;
		y2 = amp * sin(omega * t);
		//y2 = radius * sin((double)rad_angle);

		if(cache)
		{
			glVertex2f(cx * 4000, cy);
			glVertex2f(t * 4000, y2);
		}

		cache = 1;
		cx = t;
		cy = y2;
		//printf("t = %f, y2 = %f\n", t * 4000, y2);
	}
	glEnd();
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
	//glutIdleFunc(display);
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
