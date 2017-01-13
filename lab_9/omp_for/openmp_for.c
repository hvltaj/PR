#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

int main(){
  
#ifdef   _OPENMP
  printf("\nKompilator rozpoznaje dyrektywy OpenMP\n");
#endif


int i;
#pragma omp parallel for num_threads(4) schedule(dynamic, 3) ordered
	for (i = 0; i < 17; ++i) {
		#pragma omp ordered
		printf("i: %d, ID: %d\n", i, omp_get_thread_num());
	}
  
}
