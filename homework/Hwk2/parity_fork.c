#include <stdio.h>     // for printf()
#include <unistd.h>    // for fork(), pid_t
#include <stdlib.h>    // for exit()
#include <sys/types.h>
#include <sys/wait.h>  // for waitpid()



void get_parity(int n)
{
  int fibn_1, fibn_2;   // fib(n-1) and fib(n-2), respectively
  int parity_count;
  pid_t pidn_1;
  int status;           // status used in waitpid()

  //base case - if val = 0
  if (val == 0)
    exit(n);
  
  //if last bit is 0
  //if

  //else last bit is 1

}

int main(int argc, char** argv)
{
  do_fib(LIMIT);

  return 0;
}