#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NMAX		10000000

#if _DEBUG_
void chk_rand_max(void)
{
	printf("rand max(int) = %d\n", RAND_MAX);
	printf("rand min(int) = %d\n", -RAND_MAX - 1);
	printf("range = %u\n", 2 * (unsigned int)RAND_MAX + 1);
}
#endif

void get_sample(double *hist, int num, double mean, double std_dev)
{
	int i;
	int idx;
	int cnt = 0;
	int range = 20;		// 1 / width_range
	double width_range = 0.05;

	printf("num of hbuf elements = %d\n", range);

	for(i = 0; i < num; i++)
	{
        double x, y, r;

        do
        {
            x = 2.0 * rand() / RAND_MAX - 1;
            y = 2.0 * rand() / RAND_MAX - 1;
   
            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);

        double d = sqrt(-2.0 * log(r) / r);
        double n1 = x * d;
   	    double result = n1 * std_dev + mean;
		idx = result / width_range;

#if 1
		if(idx >= range || idx < 0)
		{
			cnt++;
			continue;
		}
#endif

		hist[idx]++;
    }

#if 1
	printf("It's for Outlier: idx overflow = %d\n", cnt);
#endif
}

void print_hist(double *hbuf)
{
	int i;
	double width_range = 0.05;
	int hist_range = 20;	// 1 / width_range

	for(i = 0; i < hist_range; i++)
	{
		printf("hbuf[%d] = %lf\n", i, hbuf[i]);
	}
}

int main(void)
{
	int range = 20;

	double *hist = (double *)malloc(sizeof(double) * range);
	memset(hist, 0x0, sizeof(double) * range);

	srand(time(NULL));

#if _DEBUG_
	chk_rand_max();
#endif

	get_sample(hist, NMAX, 0.5, 0.2);
	print_hist(hist);

	free(hist);
	
	return 0;
}
