#define _CRT_SECURE_NO_WARNINGS // C compiler, please let me use fopen!

#include <stdio.h> // for C functions
#include <stdlib.h> 


int main(int argc, char *argv[]) {
	int return_value = 0;
	printf("Hello World %s\n", argv[0]);

	FILE* f = fopen("C:\\shy\\lessons\\hello_worlds\\hello_c\\hello.txt", "r");
	if (f == NULL) {
		printf("Can't open file\n");
		return -1; // something went wrong
	}

	fseek(f, 0, SEEK_END);
	int size = ftell(f);

	//char* buffer = (char*)malloc(4000000000 * sizeof(char)); // example of malloc failing, return NULL
	char* buffer = (char*)malloc((size+1) * sizeof(char));
//label: // this is a bad goto
	if (buffer == NULL) {
		printf("Can't allocate memory\n");
		return_value = -2;
		goto release_file;
	}

	fseek(f, 0, SEEK_SET);
	fread(buffer, size, sizeof(char), f);
	buffer[size] = 0;

	printf("Read from file: %s\n", buffer);
	// goto label: // BAD!

	free(buffer);
release_file:
	fclose(f);

	return return_value; // all ok
}
