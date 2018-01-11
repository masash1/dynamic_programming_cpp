// An implementation file (3/4)

/*----------- FUNCTIONS FOR ANALYSIS ----------*/

// C Headers
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>
#include <string.h>
#include <sys/time.h>

double cpuSecond(void){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double)tp.tv_sec+(double)tp.tv_usec*1.e-6);
}
