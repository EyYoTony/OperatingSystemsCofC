#include <stdio.h>   // for printf()
#include <unistd.h>  // for fork(), getpid(), getppid()
#include <wait.h>

int main(int argc, char** argv)
{
  int pid;

  pid = fork();
  if(pid > 0) {
    // parent process
    printf("This is the parent [Process pid: %d].\n", getpid());
    printf("parent waiting on child...\n");
    wait(NULL);
    printf("parent done waiting on child\n");
  }
  else if(pid == 0)  {
    // child process
    printf("fork created [Process id: %d].\n", getpid());
    printf("fork parent process id: %d.\n", getppid());
    printf("child waiting for 2 seconds...\n");
    sleep(2);
    printf("child done waiting\n");
  }
  else {
    //fork creation failed
    printf("fork creation failed!!!\n");
  }

  return 0;
}
