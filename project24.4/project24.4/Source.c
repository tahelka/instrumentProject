#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_INSTRUMENT_LENGTH 150
// Structs
typedef struct treeNode {
	char* instrument;
	unsigned short insld;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;


// Functions 
InstrumentTree getInstrumentsTreeFromFile(FILE* ptrInstrumentsFile, int numOfInstruments);
TreeNode* createNewTNode(char* instrumentName, unsigned short id, TreeNode* left, TreeNode* right);
void addNewTNodeToInstrumentsBinaryTree(TreeNode* root, TreeNode* newNode); // Gets an arr of instruments and builds tree from it


void checkIfFileOpened(FILE* fpname);
void checkMemoryAllocation(void* ptr);





void main(int argc, char* argv[])
{
	int numOfInstruments = 0;
	char* instrumentName;

	// Get file and check if open properly
	FILE* ptrInstrumentsFile;

	printf("argc: %d\n", argc);
	printf("first file name: %s\n", argv[1]);

	ptrInstrumentsFile = fopen(argv[1], "r");
	checkIfFileOpened(ptrInstrumentsFile);

	getInstrumentsTreeFromFile(ptrInstrumentsFile, numOfInstruments); // Guitar


		//fClose(ptrInstrumentsFile);
}

InstrumentTree getInstrumentsTreeFromFile(FILE* ptrInstrumentsFile, int numOfInstruments)
{
	int i = 0, size = 0, len = 0;
	char* instrument;
	char* flagStr;
	TreeNode* instrumentNode;
	InstrumentTree instrumentsTree;

	instrument = (char*)malloc(sizeof(char) * MAX_INSTRUMENT_LENGTH);
	checkMemoryAllocation(instrument);

	flagStr = fgets(instrument, MAX_INSTRUMENT_LENGTH, ptrInstrumentsFile); // get instrument name
	while (flagStr != NULL)
	{
		len = strlen(instrument); // we added one for '\0'
		instrument[len - 1] = '\0';
		printf("length is: %d", len);

		// instrument = (char*)realloc(instrument, len);
		checkMemoryAllocation(instrument);

		instrumentNode = createNewTNode(instrument, numOfInstruments, NULL, NULL);
		printf("\nid: %d   name: %s\n", instrumentNode->insld, instrumentNode->instrument);

		//addNewTNodeToInstrumentsBinaryTree();

		numOfInstruments++;

		flagStr = fgets(instrument, MAX_INSTRUMENT_LENGTH, ptrInstrumentsFile); // get the next instrument name

	}


}

TreeNode* createNewTNode(char* instrumentName, unsigned short id, TreeNode* left, TreeNode* right)
{
	TreeNode* res;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(res);

	res->instrument = instrumentName;
	res->insld = id;
	res->left = left;
	res->right = right;

	return res;
}


void checkIfFileOpened(FILE* fpname)
{
	if (fpname == NULL)
	{
		printf("ERROR! could not open the file.");
		exit(1);
	}
}

void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Error allocating memory!");
		exit(1);
	}
}

