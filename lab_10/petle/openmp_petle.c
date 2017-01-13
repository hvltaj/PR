#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

main ()
{
  double a[WYMIAR][WYMIAR];
  int n,i,j;

  for(i=0;i<WYMIAR;i++) for(j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  n=WYMIAR;

  double suma=0.0;
  for(i=0;i<WYMIAR;i++) {
    for(j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

//==================================================================================
  double suma_parallel=0.0;
  double sum1 = 0.0;
  #pragma omp parallel for reduction(+:suma_parallel) private(j) ordered
  for(i=0;i<WYMIAR;i++) {
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      printf("[%d][%d] ID: %d\n", i, j, omp_get_thread_num());
    }
    //suma_parallel += sum1;
  }
  printf("Suma wyrazów tablicy równolegle 1: %lf\n", suma_parallel);


//==================================================================================
  suma_parallel=0.0;
  double sum_th[4];
  
  for(i=0;i<WYMIAR;i++) {
  
    for(j=0; j<4; j++)
    	sum_th[j] = 0.0;
  
    #pragma omp parallel for num_threads(4) firstprivate(i) ordered
    for(j=0;j<WYMIAR;j++) {
      sum_th[omp_get_thread_num()] += a[i][j];
      #pragma omp ordered
      printf("[%d][%d] ID: %d\n", i, j, omp_get_thread_num());
    }
    
    for(j=0; j<4; j++)
    	suma_parallel += sum_th[j];
    
  }
  printf("Suma wyrazów tablicy równolegle 2: %lf\n", suma_parallel);


//==================================================================================
  suma_parallel=0.0;
  for(i=0;i<WYMIAR;i++) {
    #pragma omp parallel for reduction(+:suma_parallel) firstprivate(i) ordered
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      printf("[%d][%d] ID: %d\n", i, j, omp_get_thread_num());
    }
  }
  printf("Suma wyrazów tablicy równolegle 3: %lf\n", suma_parallel);


//==================================================================================
  suma_parallel=0.0;
  #pragma omp parallel for private(j) ordered
  for(i=0;i<WYMIAR;i++) {
    double sum = 0.0;
    for(j=0;j<WYMIAR;j++) {
      sum += a[i][j];
      #pragma omp ordered
      printf("[%d][%d] ID: %d\n", i, j, omp_get_thread_num());
    }
    #pragma omp atomic
    suma_parallel += sum;
  }
  printf("Suma wyrazów tablicy równolegle 4: %lf\n", suma_parallel);

//==================================================================================
  suma_parallel=0.0;
  #pragma omp parallel for reduction(+:suma_parallel) private(j) ordered
  for(i=0;i<WYMIAR;i++) {
    int id1 = omp_get_thread_num();
    #pragma omp parallel for reduction(+:suma_parallel) firstprivate(id1, i) ordered
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      printf("[%d][%d] ID: %d, %d\n", i, j, id1, omp_get_thread_num());
    }
  }
  printf("Suma wyrazów tablicy równolegle blokowo: %lf\n", suma_parallel);

/*  
  double 
  suma_parallel=0.0;
  for(i=0;i<WYMIAR;i++) {
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
    }
  }
  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
*/

}
