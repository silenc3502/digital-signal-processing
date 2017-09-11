#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void gen_gaussian_rand_num_arr(float *data, float mean, float std, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		float x1, x2, s = 0, tmp = 0;

		do
		{
			x1 = 2 * ((float) rand() / RAND_MAX) - 1;
			x2 = 2 * ((float) rand() / RAND_MAX) - 1;
			s = pow(x1, 2.0) + pow(x2, 2.0);
		} while(s >= 1 || s == 0);

		s = sqrt((-2 * log(s)) / s);
		tmp = x1 * s;
		tmp = (std * tmp) + mean;

		data[i] = tmp;		
	}
}

void print_gpdf_num(float *data, int len)
{
	int i;

	for(i = 0; i < len; i++)
		printf("data[%d] = %f\n", i, data[i]);
}

int main(void)
{
	float data[100] = {0};
	int dlen = sizeof(data) / sizeof(float);

	srand(time(NULL));

	// sample data vector, mean = 0, variation = 1
	gen_gaussian_rand_num_arr(data, 0, 1, dlen);
	print_gpdf_num(data, dlen);

	return 0;
}
