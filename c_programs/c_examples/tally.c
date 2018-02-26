#include <stdio.h>
#include <pthread.h>

int tally;           // global variable shared by all threads

void* total(void* arg) // *arg is for arguments
{
  int i;
  int n = *((int *) arg);    // NOTE:  compiler can't error check access to N

  for (i = 0; i < n; i++) {
    tally++;
  }

  return NULL;   // technically need to return a pointer to void
}

int main()
{
  const int N = 50;
  pthread_t thread1, thread2;
  int i;
  int mintally = 2*N, maxtally = 0;   // initialize tallies
  
  // doing arbitrarily a millon times to "experimentally" determine min, max
  for (i = 0; i < 1000000; i++) {
    tally = 0;  // initialize shared global variable, tally

    pthread_create(&thread1, NULL, total, (void*) &N);  // create 2 threads
    pthread_create(&thread2, NULL, total, (void*) &N);

    pthread_join(thread1, NULL);  // wait for both threads to complete
    pthread_join(thread2, NULL); 

    if (tally > maxtally) {
      maxtally = tally;
      printf("new maxtally = %d\n", maxtally);
    }
    if (tally < mintally) {
      mintally = tally;
      printf("new mintally = %d\n", mintally);
    }
  }

  printf("tally in range [%d, %d]\n", mintally, maxtally);
  
  return 0;               // technically main() needs to return an int
}
