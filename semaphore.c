/* gcc sema_vorgabe.c -o sema_vorgabe -lpthread */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_1; 
sem_t sem_2;

void *print_stern (void *dummy) {
   char ch = '*';

   while(1) {
      sem_wait(&sem_1);
      putchar(ch);
      fflush(stdout);
      sem_post(&sem_2);
  }

  return NULL;
}

void *print_minus (void *dummy) {
   char ch = '-';

   while(1) {
      sem_wait(&sem_2);
      putchar(ch);
      fflush(stdout);
      sem_post(&sem_1);
   }

  return NULL;
}

int main () {
   pthread_t tref1, tref2;
 
   if(sem_init(&sem_1, 0, 0)){
	perror("sem_1 init fail");
	return -1;
   }
   if(sem_init(&sem_2, 0, 1)){
	perror("sem_2 init fail");
   	return -1;
   }
  
   if (pthread_create (&tref1, NULL, print_minus, NULL)) {
      fprintf(stderr, "error: creating thread 1 failed.\n");
      return EXIT_FAILURE;
   }
 
   if (pthread_create (&tref2, NULL, print_stern, NULL)) {
      fprintf(stderr, "error: creating thread 2 failed.\n");
      return EXIT_FAILURE;
   }

   if (pthread_join (tref1, NULL)) {
      fprintf(stderr, "error: joining thread 1 failed.\n");
      return EXIT_FAILURE;
   }
   if (pthread_join (tref2, NULL)) {
      fprintf(stderr, "error: joining thread 2 failed.\n");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
