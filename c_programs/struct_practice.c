#include <stdio.h>

int main(int argc, char** argv){

	struct birthday {
		char *name;
		int month;
		int day;
		int year;
	};

	struct birthday bday = {"xyz",1,1,1990};

	char first_letter = bday.name[0];

	printf("value of first_letter is %c\n", first_letter);

	char *name = "hello";

	*name = 'b';

	printf("first char of name is %c\n", *name);

	printf("value of name is %s\n", name);

	return 0;
}