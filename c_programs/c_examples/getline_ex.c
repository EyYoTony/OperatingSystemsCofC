#include <stdio.h>        // for printf(), fopen(), getline()
#include <stdlib.h>       // for free()

int main(int argc, char* argv[])
{
  char filename[] = "/etc/hosts";  // a string in 'C' is an array of chars
  FILE *fp;               // file pointer
  char *line = NULL;      // NULL is a pointer to "nothing"
  size_t n = 0;           // will contain the size of the allocated buffer
  ssize_t len;            // will contain the length of line read (or -1)

  fp = fopen(filename , "r");
  if (fp == NULL) {       // check if there was an error opening the file
    printf("Failed to open file %s\n", filename);
    return 1;             // a return of non-zero indicates a error
  }

  printf("n before loop is %zu\n", n);  // %zu format specifier for size_t

  // if *lines is NULL and n is 0, then getline() will allocate memory for line
  while ((len = getline(&line, &n , fp)) != -1) {
    /*
      NOTE: line will contain the newline character.  To "strip" off
      the newline character, you can do the following:
    */
    line[len-1] = '\0';
    printf("line: %s\n", line);         // %s format specifier for a string
    printf("len : %zd\n", len);         // %zd format specifier for ssize_t
    printf("n   : %zu\n\n", n);
  }

  free(line);             // if you don't free line, you get a memory leak

  return 0;               // returning 0 from main indicates no error
}
