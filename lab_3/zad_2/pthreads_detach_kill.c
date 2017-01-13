#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;

#define WYMIAR 300
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];


double czasozajmowacz(){
  int i, j, k;
  int n=WYMIAR;
  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
  for(i=0;i<ROZMIAR;i++) b[i]=1.0*(ROZMIAR-i);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i+n*j]=0.0;
      for(k=0;k<n;k++){
	c[i+n*j] += a[i+n*k]*b[k+n*j];
      }
    }
  }
  return(c[ROZMIAR-1]);
}

void * zadanie_watku2 (void * arg_wsk)
{
	czasozajmowacz();

	printf("\twatek potomny: i: %i, ID:%lu\n", *(int*)arg_wsk, pthread_self());

	return(NULL);
}

int main()
{
	pthread_t tid[10];
	pthread_attr_t attr;
	void *wynik;
	int i;

	//Wątek przyłączalny
	for (i = 0; i < 10; ++i) {
	
		printf("watek glowny: tworzenie watku potomnego nr %i\n", i);
		int *id = malloc(sizeof i);
		*id = i;

		pthread_create(&tid[i], NULL, zadanie_watku2, id);
	}
	
	for (i = 0; i < 10; ++i) {
		pthread_join(tid[i], NULL);
	}


	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}


