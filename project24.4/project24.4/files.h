#ifndef __FILES_H
#define __FILES_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// this function opens a file in read text mode and checks if it opened properly
void openAndCheckFileForTextRead(char* fileName, FILE** fp);
// this function checks if file has opened successfully 
void checkIfFileOpened(FILE* fpname);



#endif 
