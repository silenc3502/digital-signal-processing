#include <stdio.h>
#include <math.h>

int glob = 4;
int count = 0;

#define SLICE		8
#define TWID_FACTOR	(SLICE >> 1) + 1

static void just_for_test(void);

typedef struct complex
{
	double re;
	double im;
} c;

int main(int argc, const char * const argv[])
{
	just_for_test();
	return 0;
}

void just_for_test(void)
{
	c y[8] = {0};
	int ix;
	int ju;
	int iy;
	int i;
	double x[8] = {0};
	double step = 2 * M_PI / SLICE;
	double t = 0;

	for(i = 0; i < SLICE; i++)
	{
		x[i] = sin(t);
		t += step;
	}

#if 0
	static const double x[8] = { 0.0, 0.70710678118654746, 1.0,
		0.70710678118654757, 1.2246467991473532E-16, -0.70710678118654746, -1.0,
		-0.70710678118654768 };
#endif

	int tst;
	double temp_re;
	double temp_im;
	int iheight;
	int istart;
	int j;
	double twid_re;
	double dv0[5] = {0};

	t = 0;

	printf("TWID_FACTOR = %d\n", TWID_FACTOR);
	for(i = 0; i < TWID_FACTOR; i++)
	{
		dv0[i] = cos(t);
		t += step;
	}

#if 0
	static const double dv0[5] = { 1.0, 0.70710678118654757, 0.0,
		-0.70710678118654757, -1.0 };
#endif

	double twid_im;
	double dv1[5] = {0};

	t = 0;

	printf("TWID_FACTOR = %d\n", TWID_FACTOR);
	for(i = 0; i < TWID_FACTOR; i++)
	{
		dv1[i] = -sin(t);
		t += step;
	}

#if 0
	static const double dv1[5] = { 0.0, -0.70710678118654757, -1.0,
		-0.70710678118654757, -0.0 };
#endif

	int ihi;

	ix = 0;
	ju = 0;
	iy = 0;
	printf("Before Reverse Order\n");
	for (i = 0; i < 7; i++) {
		y[iy].re = x[ix];
		y[iy].im = 0.0;

		printf("y[%d].re = %lf\t", iy, y[iy].re);
		printf("y[%d].im = %lf\n", iy, y[iy].im);

		iy = 8;
		tst = 1;
		while (tst) {
			iy >>= 1;
			ju ^= iy;
			tst = ((ju & iy) == 0);
		}

		iy = ju;
		ix++;
	}
	y[iy].re = x[ix];
	y[iy].im = 0.0;

	printf("\nAfter Reverse Order\n");
	for(i = 0; i < SLICE; i++)
	{
		printf("y[%d].re = %lf\t", i, y[i].re);
		printf("y[%d].im = %lf\n", i, y[i].im);
	}
	printf("\nN-2 First Butterfly\n");

	for (i = 0; i <= 7; i += 2) {
		temp_re = y[i + 1].re;
		temp_im = y[i + 1].im;
		y[i + 1].re = y[i].re - y[i + 1].re;
		y[i + 1].im = y[i].im - y[i + 1].im;
		y[i].re += temp_re;
		y[i].im += temp_im;

		printf("y[%d].re = %lf\t", i, y[i].re);
		printf("y[%d].im = %lf\n", i, y[i].im);
		printf("y[%d].re = %lf\t", i+1, y[i+1].re);
		printf("y[%d].im = %lf\n", i+1, y[i+1].im);
	}

	iy = 2;
	ix = 4;
	ju = 2;
	iheight = 5;
	while (ju > 0) {
		// 0 ~ 4
		printf("\nN-%d Butterfly(처음은 짝수 오더)\n", glob);
		for (i = 0; i < iheight; i += ix) {
			temp_re = y[i + iy].re;
			temp_im = y[i + iy].im;
			y[i + iy].re = y[i].re - temp_re;
			y[i + iy].im = y[i].im - temp_im;
			y[i].re += temp_re;
			y[i].im += temp_im;

			printf("y[%d].re = %lf\t", i, y[i].re);
			printf("y[%d].im = %lf\n", i, y[i].im);
			printf("y[%d].re = %lf\t", i+iy, y[i+iy].re);
			printf("y[%d].im = %lf\n", i+iy, y[i+iy].im);
		}
		printf("\n");

		istart = 1;
		printf("\nN-%d Butterfly(처음은 홀수 오더)\n", glob);
		for (j = ju; j < 4; j += ju) {
			printf("twid_re = dv0 =  cos(2 * pi * f * t / fftN의절반)\n");
			printf("twid_im = dv1 = -sin(2 * pi * f * t / fftN의절반)\n");
			twid_re = dv0[j];
			twid_im = dv1[j];
			i = istart;
			ihi = istart + iheight;
			while (i < ihi) {
				temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
				temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
				y[i + iy].re = y[i].re - temp_re;
				y[i + iy].im = y[i].im - temp_im;
				y[i].re += temp_re;
				y[i].im += temp_im;

				printf("y[%d].re = %lf\t", i, y[i].re);
				printf("y[%d].im = %lf\n", i, y[i].im);
				printf("y[%d].re = %lf\t", i+iy, y[i+iy].re);
				printf("y[%d].im = %lf\n", i+iy, y[i+iy].im);

				i += ix;
			}

			istart++;
		}

		ju /= 2;
		iy = ix;
		ix <<= 1;
		iheight -= iy;

		if(ju > 0)
		{
			count++;
			printf("\nFinished N-%d Butterfly\nNow Starting N-%d Butterfly", glob, glob *= 2);
		}
		else
			printf("\nFinished N-%d Butterfly\n", glob);
	}

	for(i = 0; i < SLICE; i++)
	{
		printf("y[%d].rm = %lf\t", i, y[i].re);
		printf("y[%d].im = %lf\n", i, y[i].im);
	}
}
