#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"

/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv)
{ 
  if(argc != 5){
    printf("This program need 4 parameters as follows: mem size, # of runs, time steps per run, random # seed \n");
  }
  else {
    ///get values from argv and convert them to ints
    int init_size = atoi(*(argv+1));
    int run_num = atoi(*(argv+2));
    int time_passed = atoi(*(argv+3));
    int random_seed = atoi(*(argv+4));
    //set random seed so we get diffferent rng based on seed
    srand(random_seed);
    //rand() % (max_number + 1 - minimum_number) + minimum_number
    //malloc arr
    mem_init(init_size);
    //BESTFIT
    int total_failures = 0;
    int total_probes = 0;
    int total_fragmentation = 0;
    int rand_dur = 0;
    int rand_size = 0;
    int allocate_output = 0;
    
    for(int i = 0; i < run_num; i++){
      rand_dur = rand() % (MAX_DURATION + 1 - MIN_DURATION) + MIN_DURATION;
      rand_size = rand() % (MAX_REQUEST_SIZE + 1 - MIN_REQUEST_SIZE) + MIN_REQUEST_SIZE;
      allocate_output = mem_allocate(BESTFIT, rand_size, rand_dur);
      if(allocate_output == -1){
        total_failures++;
      }
      else{
        total_probes += allocate_output;
      }
      for(int j = 0; j < time_passed; j++){
        mem_single_time_unit_transpired();
      }
      total_fragmentation += mem_fragment_count(MIN_REQUEST_SIZE - 1);
    }
    //output
    printf("Bestfit avg probes: %lf\n", ((double)total_probes/run_num));
    printf("Bestfit avg failures: %lf\n", ((double)total_failures/run_num));
    printf("Bestfit avg fragmentation: %lf\n", ((double)total_fragmentation/run_num));
    mem_clear();

    //FIRSTFIT
    total_failures = 0;
    total_probes = 0;
    total_fragmentation = 0;
    rand_dur = 0;
    rand_size = 0;
    allocate_output = 0;
    
    for(int i = 0; i < run_num; i++){
      rand_dur = rand() % (MAX_DURATION + 1 - MIN_DURATION) + MIN_DURATION;
      rand_size = rand() % (MAX_REQUEST_SIZE + 1 - MIN_REQUEST_SIZE) + MIN_REQUEST_SIZE;
      allocate_output = mem_allocate(BESTFIT, rand_size, rand_dur);
      if(allocate_output == -1){
        total_failures++;
      }
      else{
        total_probes += allocate_output;
      }
      for(int j = 0; j < time_passed; j++){
        mem_single_time_unit_transpired();
      }
      total_fragmentation += mem_fragment_count(MIN_REQUEST_SIZE - 1);
    }
    //output
    printf("Firstfit avg probes: %lf\n", ((double)total_probes/run_num));
    printf("Firstfit avg failures: %lf\n", ((double)total_failures/run_num));
    printf("Firstfit avg fragmentation: %lf\n", ((double)total_fragmentation/run_num));
    mem_clear();

    //NEXTFIT
    total_failures = 0;
    total_probes = 0;
    total_fragmentation = 0;
    rand_dur = 0;
    rand_size = 0;
    allocate_output = 0;
    
    for(int i = 0; i < run_num; i++){
      rand_dur = rand() % (MAX_DURATION + 1 - MIN_DURATION) + MIN_DURATION;
      rand_size = rand() % (MAX_REQUEST_SIZE + 1 - MIN_REQUEST_SIZE) + MIN_REQUEST_SIZE;
      allocate_output = mem_allocate(BESTFIT, rand_size, rand_dur);
      if(allocate_output == -1){
        total_failures++;
      }
      else{
        total_probes += allocate_output;
      }
      for(int j = 0; j < time_passed; j++){
        mem_single_time_unit_transpired();
      }
      total_fragmentation += mem_fragment_count(MIN_REQUEST_SIZE - 1);
    }
    //output
    printf("Nextfit avg probes: %lf\n", ((double)total_probes/run_num));
    printf("Nextfit avg failures: %lf\n", ((double)total_failures/run_num));
    printf("Nextfit avg fragmentation: %lf\n", ((double)total_fragmentation/run_num));
    mem_clear();

    //free arr
    mem_free();
  }
  return 0;
}
