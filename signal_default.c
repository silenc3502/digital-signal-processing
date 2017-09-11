#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

#define SLICE	36

float common_angles[5] = {15.0, 30.0, 45.0, 60.0, 75.0};
float freq_table[5] = {1000.0, 2400.0, 5000.0, 24000.0, 77000.0};

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
	float step, time = 0.0;

	time = step = get_step(SLICE, period);

	while(cnt++ < 36)
	{
		printf("%.1fcos(%f * %.8f) = %f\n", amplitude, ang_vel,
			time, amplitude * cos(ang_vel * time));
		time += step;
	}
}

void sin_sim(float amplitude, float ang_vel, float period)
{
	int cnt = 0;
	float step, time = 0.0;

	time = step = get_step(SLICE, period);

	while(cnt++ < 36)
	{
		printf("%.1fsin(%f * %.8f) = %f\n", amplitude, ang_vel,
			time, amplitude * sin(ang_vel * time));
		time += step;
	}
}

int main(int argc, char **argv)
{
	float amplitude, angle, period, frequency, radian, angular_velocity;
	float step = 0.0;

	srand(time(NULL));

	set_rand_amplitude(&amplitude);
	set_angle_with_common_angles(&angle);
	angle2radian(&angle, &radian);
	set_rand_frequency(&frequency);
	calc_period(&frequency, &period);
	calc_angular_velocity(&frequency, &angular_velocity);

	printf("amplitude = %f\n", amplitude);
	printf("angle = %f degree\n", angle);
	printf("radian = %f\n", radian);
	printf("frequency = %f\n", frequency);
	printf("period = %f\n", period);
	printf("angular_velocity = %f\n", angular_velocity);

	cos_sim(amplitude, angular_velocity, period);
	sin_sim(amplitude, angular_velocity, period);

	return 0;
}
