#include <stdio.h>
#include <stdlib.h>

int main(void){

	struct birthday {
		char *name;
		int month;
		int day;
		int year;
	};

	struct birthday bday = {"xyz",1,1,1990};

	char first_letter = bday.name[0];

	printf("value of first_letter is %c\n", first_letter);

	char *name_arr = strdup("hello");

	*name_arr = 'b';

	printf("address of name is %p\n", &name_arr);

	printf("first char of name is %c\n", *name_arr);

	printf("value of name is %s\n", name_arr);

	free(name_arr);

	return 0;
}