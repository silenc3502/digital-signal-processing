#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float gaussian_probability_density_function(float x, float m, float s)
{
	float inv_sqrt_2pi = 1.0 / sqrt(2.0 * M_PI);
	float a = (x - m) / s;
	float res = (inv_sqrt_2pi / s) * expf(-0.5f * pow(a, 2.0));
	printf("inv_sqrt_2pi = %f, a = %f, res = %f\n", inv_sqrt_2pi, a, res);
	return res;
}

int main(void)
{
	// sample data, mean = 0, variation = 1
	gaussian_probability_density_function(1, 0, 1);
	return 0;
}
