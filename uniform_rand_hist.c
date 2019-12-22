#include <stdlib.h>
#include <string.h>
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

int *get_sample(int num)
{
	int i;
	int *values = (int *)calloc(num, sizeof(int));

	if(values)
	{
		for(i = 0; i < num; i++)
		{
			values[i] = rand();
		}
	}

	return values;
}

int *make_hist(int *sbuf, int num)
{
	int i;
	int *hbuf = NULL;
	// 85899346 * 50 = 4294967300
	// uint max      = 4294967295
	// 42949673 * 50 = 2147483650
	int width_range = 42949673;

	hbuf = (int *)malloc(sizeof(int) * RAND_MAX / width_range);
	memset(hbuf, 0x0, (RAND_MAX / width_range) * sizeof(int));

	printf("num of hbuf elements = %d\n", RAND_MAX / width_range);

	for(i = 0; i < num; i++)
	{
		hbuf[sbuf[i] / width_range]++;
	}

	return hbuf;
}

void print_hist(int *hbuf)
{
	int i;
	int width_range = 42949673;
	int hist_range = RAND_MAX / width_range;

	for(i = 0; i < hist_range; i++)
	{
		printf("hbuf[%d] = %d\n", i, hbuf[i]);
	}
}

int main(void)
{
	int *sbuf = NULL;
	int *hist_buf = NULL;

	srand(time(NULL));

#if _DEBUG_
	chk_rand_max();
#endif

	if((sbuf = get_sample(NMAX)) != NULL)
	{
		hist_buf = make_hist(sbuf, NMAX);
		print_hist(hist_buf);
		free(hist_buf);
		free(sbuf);
	}
	
	return 0;
}
