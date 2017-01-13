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

struct struktura { int a; char b; double c; };

void * zadanie_watku3 (void * arg_wsk)
{
	czasozajmowacz();

	
	struct struktura *s = arg_wsk;
	s->a++;
	s->b++;
	s->c++;
	
	struct struktura l;
	l = *( (struct struktura*) arg_wsk);
	l.a++;
	l.b++;
	l.c++;
	
	printf("\twatek potomny: lokalne a=%i, b=%c, c=%f\n", l.a, l.b, l.c);

	return(NULL);
}

int main()
{
	pthread_t tid[10];
	pthread_attr_t attr;
	void *wynik;
	int i;

	struct struktura str = {1, 'a', 2.0};
	
	for (i = 0; i < 10; ++i) {
	
		printf("watek glowny: tworzenie watku potomnego nr %i\n", i);

		pthread_create(&tid[i], NULL, zadanie_watku3, &str);
	}
	
	for (i = 0; i < 10; ++i) {
		pthread_join(tid[i], NULL);
	}
	

	printf("\twatek glowny: a=%i, b=%c, c=%f\n", str.a, str.b, str.c);

	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}


