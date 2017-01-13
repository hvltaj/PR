#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include<errno.h>


void * watek_klient (void * arg);
int l_kf;
pthread_mutex_t mutex_kf, mutex_kr;

main(){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kr, i;
  
  pthread_mutex_init(&mutex_kf, NULL);
  pthread_mutex_init(&mutex_kr, NULL);

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nLiczba wolnych kufli %d\n", l_kf); 
  printf("\nZamykamy pub!\n");


}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j, kufel=0, result;
  int ile_musze_wypic = 2;

  printf("\nKlient %d, wchodzę do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){
    
    while(kufel < 1) {
      result = pthread_mutex_lock(&mutex_kf);
      
      if (result == EBUSY) {
        usleep(100);
        continue;
      }
      if (l_kf > 0) {
        kufel = l_kf--;
        //kufel = 1;
      }
      pthread_mutex_unlock(&mutex_kf);
    }
    printf("\nKlient %d, wybieram kufel %d\n", moj_id, kufel); 
    
    j=0;
    pthread_mutex_lock(&mutex_kr);
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
    usleep(300);
    pthread_mutex_unlock(&mutex_kr);
    
    printf("\nKlient %d, pije\n", moj_id); 
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    
    pthread_mutex_lock(&mutex_kf);
    //kufel = 0;
    kufel = ++l_kf;
    pthread_mutex_unlock(&mutex_kf);
    printf("\nKlient %d, odkladam kufel. Pozostało: %d\n", moj_id, kufel); 
    
    kufel = 0;
  }

  printf("\nKlient %d, wychodzę z pubu\n", moj_id); 
    
  return(NULL);
} 


