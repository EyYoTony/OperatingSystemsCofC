#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
  int child_process_status;
  int fds[2];
  pid_t cpid1;
  char* pargs[] = { "ls", NULL };
  char* cargs[] = { "wc", "-l", NULL };
     
  pipe(fds);
     
  if ((cpid1 = fork()) == 0) {
    close(1);                /* close normal stdout */
    dup(fds[1]);             /* make stdout same as fds[1] */
    close(fds[0]);           /* we don't need this */
    execv("/bin/ls", pargs);
  }
  else{   
    close(0);               /* close normal stdin */
    dup(fds[0]);            /* make stdin same as fds[0] */
    close(fds[1]);          /* we don't need this */
    execv("/usr/bin/wc", cargs);
  }
  close(fds[0]);
  waitpid(cpid1, &child_process_status, 0);
  return 0;
}
