#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void main(void) {
  close(1);
  int fd = open("out.txt", O_RDWR);  //fd returns the index of the opened file on the FDT
  printf("This is the value of fd: %d\n", fd);
  write(fd, "hello\n", 6); //Writes to out.txt
}

/*

Table Defaults
0 - stdin 
1 - stdout
2 - stderr

*/

/*

execv ends the process and converts it to the command given while using the same FDT

execv("/bin/ls", pargs);
execv("/usr/bin/wc", cargs);
char* pargs[] = {"ls", NULL};
char* cargs[] = {"wc", "-l", NULL}

*/