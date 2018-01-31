#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
  pid_t child_pid, wpid;
  int status;

  child_pid = fork();
  if (child_pid == -1) {      /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (child_pid == 0) {       /* This is the child */
    /* Child does some work and then terminates */
    /* Child does some work and then terminates */
    printf("fork created child [Process id: %d].\n", getpid());
    printf("waiting for 2 seconds...\n");
    sleep(2);
  } else {                    /* This is the parent */
    
    do {  /* This loop in case we had forked multiple children above */
      wpid = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
      if (wpid == -1) {
	perror("waitpid");
	exit(EXIT_FAILURE);
      }

      if (WIFEXITED(status)) {
	printf("child exited, status = %d\n", WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
	printf("child killed (signal %d)\n", WTERMSIG(status));
      } else if (WIFSTOPPED(status)) {
	printf("child stopped (signal %d)\n", WSTOPSIG(status));
      } else if (WIFCONTINUED(status)) {
	printf("child continued\n");
      } else {    /* Non-standard case -- may never happen */
	printf("Unexpected status (0x%x)\n", status);
      }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 0;
}
