#include <stdio.h>        // for printf(), fopen(), getline()
#include <stdlib.h>       // for free()
#include <string.h>       // for strdup(), strsep()
#include <ctype.h>        // for isspace()

// trim() function "lifted" from stackoverflow (question 122616)
// NOTE:  currently not using in main() below, but good example of pointers
char *trim(char *str)
{
  size_t len = 0;
  char *frontp = str;
  char *endp = NULL;

  if(str == NULL) { return NULL; }
  if(str[0] == '\0') { return str; }

  len = strlen(str);
  endp = str + len;

  /* Move the front and back pointers to address the first non-whitespace
   * characters from each end.
   */
  while(isspace((unsigned char) *frontp))
    ++frontp;
  
  if(endp != frontp) {
    while(isspace((unsigned char) *(--endp)) && endp != frontp)
      ;
  }

  if(str + len - 1 != endp)
    *(endp + 1) = '\0';
  else if(frontp != str &&  endp == frontp)
    *str = '\0';

  /* Shift the string so that it starts at str so that if it's dynamically
   * allocated, we can still free it on the returned pointer.  Note the reuse
   * of endp to mean the front of the string buffer now.
   */
  endp = str;
  if(frontp != str) {
    while(*frontp)
      *endp++ = *frontp++;
    *endp = '\0';
  }

  return str;
}

int main(int argc, char* argv[])
{
  char *filename;         // filename to read
  FILE *fp;               // file pointer
  char *line = NULL;      // NULL is a pointer to "nothing"
  size_t n = 0;           // will contain the size of the allocated buffer
  ssize_t len;            // will contain the length of line read (or -1)
  char *cline;            // copy of line
  char *token;            // for breaking up line in word tokens

  if (argc < 2) {
    fprintf(stderr, "USAGE: %s filename\n", argv[0]);
    return 1;
  }

  // Demo note:  try it on CSCI340_Syllabus_Fall16.tex

  filename = argv[1];     // filename "points" to second argument on cmdline

  fp = fopen(filename , "r");
  if (fp == NULL) {       // check if there was an error opening the file
    fprintf(stderr, "Failed to open file %s\n", filename);
    return 2;             // a return of non-zero indicates a error
  }

  // if *lines is NULL and n is 0, then getline() will allocate memory for line
  while ((len = getline(&line, &n , fp)) != -1) {
    line[len-1] = '\0';           // strip off newline
    cline = strdup(line);         // copy of line for strsep()

    if (cline[0] != '\0') {
      // NOTE: strsep() modifies cline
      while ((token = strsep(&cline, " \t\n.,"))) {  // string of delim chars
	if (token[0] != '\0')     // could have multiple delimeters "in a row"
	  printf("%s\n", token);
      }
    }

    free(cline);
  }

  free(line);             // if you don't free line, you get a memory leak

  return 0;               // returning 0 from main indicates no error
}
