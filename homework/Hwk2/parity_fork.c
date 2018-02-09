#include <stdio.h>     // for printf()
#include <unistd.h>    // for fork(), pid_t
#include <stdlib.h>    // for exit()
#include <sys/types.h>
#include <sys/wait.h>  // for waitpid()

//#define DEBUG 0 
//I am using the int original
int get_parity(int n, int original)
{
	const static char *parity[2] = {"EVEN", "ODD"}; 
	int child_n;
	pid_t child_pid;
	int status;

	if (n < 2){    // base case
		if(n == original){
			printf("The number %d has %s parity\n", original, parity[n%2]);
		}
		exit(n);    // either a 1 or 0 parity
	}

	//if it missed base case, make a new child
	//only the child does this
	if ((child_pid = fork()) == 0) { 
      	get_parity(n/2, original);
  	}

	//wait for child process to finish
	while (waitpid(child_pid, &status, 0) > 0) {
		if (WIFEXITED(status))   // if child terminated normally
    		child_n = WEXITSTATUS(status);   // get (8 bits of) the exit status
	}

	#ifdef DEBUG
  		printf("value from from pid %d = %d\n", getpid(), child_n);
  	#endif

	//parent does this
  	//original parent prints out desired output
  	if(n == original){
  		if (n % 2 == 0) {
  			printf("The number %d has %s parity\n", original, parity[child_n%2]);
  		}
  		else{
  			printf("The number %d has %s parity\n", original, parity[( child_n+1)%2]);
  		}
  	}

  	if (n % 2 == 0) {
		exit(child_n);
	}
	else{
		exit(child_n+1);
	}

}

int main(int argc, char** argv)
{
	if(argc == 1){
		printf("No parameter given, please give a non-negative integer\n");
	}
	else if(argc == 2){
		if((int)strtol(argv[1], NULL, 10) < 0){
			printf("Negative integer given, please give a non-negative integer\n");
		}
		else{
			//since we are exiting, we can not also return the data as they both kill the original process
			printf("output of get_parity: %d\n", get_parity((int)strtol(argv[1], NULL, 10), (int)strtol(argv[1], NULL, 10)));
		}
	}
	else{
		printf("Too many parameters given, please give a non-negative integer\n");
	}

	return 0;
}