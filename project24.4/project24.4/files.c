#include "files.h"


void openAndCheckFileForTextRead(char* fileName, FILE** fp) {
	*fp = fopen(fileName, "r");
	checkIfFileOpened(*fp); // also if file is empty, exit
}

void checkIfFileOpened(FILE* fpname)
{
	if (fpname == NULL)
	{
		printf("ERROR! could not open the file.");
		exit(1);
	}
}