#include <stdio.h>
#include <stdlib.h>

int main(void){

	int *x;

	x = (int*)malloc(100*sizeof(int));

	*x = 39;

	*(x+(10*sizeof(int))) = 27;

	printf("This is the address of x: %p\n", x);
		
	printf("This is the value of x[10]: %i\n", *(x+(10*sizeof(int))));

	free(x);

	return 0;
}