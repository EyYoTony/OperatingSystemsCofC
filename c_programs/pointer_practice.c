#include <stdio.h>

int main(int argc, char** argv){
	int i = 10;
	int* ptr_i;


	printf("value of i is %d\n", i);

	ptr_i = &i;

	printf("address of i is %lx\n", (unsigned long) ptr_i);

	*ptr_i = 3;

	printf("value of i is now %d\n", i);

	*&i = 5;

	printf("value of i is now %d\n", i);

	return 0;
}