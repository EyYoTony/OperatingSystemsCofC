#include <stdio.h>     // for printf()
#include <unistd.h>    // for fork(), pid_t
#include <stdlib.h>    // for exit()
#include <sys/types.h>
#include <sys/wait.h>  // for waitpid()

// Copyright (c) 2017,2018 Anthony Leclerc <leclerca@cofc.edu>
// All rights reserved. No warranty, explicit or implicit, provided.

// value for which to compute the Fibonacci number
#define LIMIT 7
#define DEBUG 0

void do_fib(int n)
{
  int fibn_1, fibn_2;   // fib(n-1) and fib(n-2), respectively
  int fibn;             // sum of fib(n-1) and fib(n-2)
  pid_t pidn_1, pidn_2; // pids for fib(n-1) and fib(n-2), respectively
  int status;           // status used in waitpid()

  if (n < 2)    // base case
    exit(n);    // fib(1) = 1 and fib(0) = 0  (ie. just return n)

  if ((pidn_1 = fork()) == 0) {  // only "child" enters the if statement
    do_fib(n-1);   //  NOTE:  each do_fib() call executes and exit()
    // So, don't need an exit here nor use an if-else statement
  }

  if ((pidn_2 = fork()) == 0) {  // only "child" enters the if statement
    do_fib(n-2);   //  NOTE:  each do_fib() call executes and exit()
    // So, don't need an exit here nor use an if-else statement
  }

  while (waitpid(pidn_1, &status, 0) > 0) { // wait for fib(n-1) child to finish
    if (WIFEXITED(status))   // if child terminated normally
      fibn_1 = WEXITSTATUS(status);   // get (8 bits of) the exit status
  }

  while (waitpid(pidn_2, &status, 0) > 0) { // wait for fib(n-1) child to finish
    if (WIFEXITED(status))   // if child terminated normally
      fibn_2 = WEXITSTATUS(status);   // get (8 bits of) the exit status
  }

  fibn = fibn_1 + fibn_2;     // add fib(n-1) and fib(n-2) exit status'

#ifdef DEBUG   // compile-time "directive" check
  // output below useful for understanding what's going on
  printf("fib from pid %d = %d\n", getpid(), fibn);  // note getpid()
#endif

  if (n == LIMIT)
    printf("fib(%d) = %d\n", LIMIT, fibn);

  exit(fibn);  // exit with fib value so as to return it to the waiting parent
}

int main(int argc, char** argv)
{
  do_fib(LIMIT);

  return 0;
}
