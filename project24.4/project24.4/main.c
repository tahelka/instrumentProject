#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ours includes
#include "trees.h"
#include "prints.h"
#include "files.h"


void main(int argc, char* argv[])
{
	FILE* ptrInstrumentsFile;
	FILE* ptrMusiciansFile;
	char* instrumentName;
	InstrumentTree tree;
	Musician** musiciansGroup;
	Musician*** MusiciansCollection;
	int numOfInstruments;
	int numOfMusicians;
	int insId;
	int* indicesArr; // helper array for the size of every musicians's instrument array
	instrumentName = "Guitar"; // when do we need to get an instrument name ????


	printf("%s ", argv[2]);
	printf("%s\n", argv[1]);

	//Q1
	openAndCheckFileForTextRead(argv[1], &ptrInstrumentsFile);
	//Q3
	openAndCheckFileForTextRead(argv[2], &ptrMusiciansFile);

	//Q1
	tree = getInstrumentsTreeFromFile(ptrInstrumentsFile, &numOfInstruments);
	//Q2
	insId = findInsId(tree, instrumentName);
	//Q3
	musiciansGroup = getMusicianFromFile(tree, ptrMusiciansFile, &numOfMusicians);
	//Q4
	// maybe calloc? or to allocate memory in each node of the str to 1 size (cuz there is at least one player)
	MusiciansCollection = (Musician***)malloc(sizeof(Musician**) * numOfInstruments);
	checkMemoryAllocation(MusiciansCollection);
		
	MusiciansCollection = createMusiciansCollection(musiciansGroup, numOfInstruments, numOfMusicians, &indicesArr);
	// delete
	for (int i = 0; i < numOfInstruments; i++) {
		printf("the num of Musicians who plays the instrument with the id %d is: %d\n", i, indicesArr[i]);
	}
	
	printTreeInorder(tree);


	fclose(ptrInstrumentsFile);
}

