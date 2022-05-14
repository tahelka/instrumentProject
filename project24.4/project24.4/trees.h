#ifndef __TREES_H
#define __TREES_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include "lists.h"


#define MAX_INSTRUMENT_LENGTH 152 // the maximum length is 150 + 1 for '\0' + 1 
// for preventing the case that there is no '\n' at the end

#define NOT_FOUND -1 // belongs to find id Q2 !!!!!!!!!!!!
#define DEFUALT_ID -1

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

// Q1

// this function creates instrument tree from file
InstrumentTree getInstrumentsTreeFromFile(FILE* ptrInstrumentsFile, int* numOfInstruments);
// this function creates new tree node with data
TreeNode* createNewTNode(char* instrumentName, unsigned short id, TreeNode* left, TreeNode* right);
// this function adds a new node to instrument tree by BST insert
void addNewTNodeToInstrumentsBinaryTree(InstrumentTree* tr, TreeNode* newNode);
// this function is a helper function to addNewTNodeToInstrumentsBinaryTree function
void addNewTNodeToInstrumentsBinaryTreeHelper(TreeNode* root, TreeNode* newNode);
// this function gets a new instrument name from file 
void getNewLineFromFile(FILE* ptrInstrumentsFile, char** instrumentName, char** flagStr);
// this function shrinks the physical size of instrument name string to the actual logical size
void shrinkAllocationStr(char** strPtr);


// Q2

// this function finds id of required instrument, if there is no such instrument it returns -1
int findInsId(InstrumentTree tree, char* instrument);
// this function is a helper function for findInsId function
int findInsIdHelper(TreeNode* root, char* instrument);

// Q3
void insertToMusicianNameArr(char** fullName, char* name);
// checks if the name is valid and not an instrument or price
bool checkMusicianName(InstrumentTree tr, char* str);
Musician* createNewMusician(char** musicianName, MPIList rateList, int concertInstrument_id);
Musician** getMusicianFromFile(InstrumentTree tr, FILE* ptrMusiciansFile, int* numOfMusicians);

// Q4

Musician*** createMusiciansCollection(Musician** musiciansGroup, int numOfInstruments, int numOfMusicians, int** indicesArr);
int* addMusicianToCollection(Musician*** musicianCollection, Musician** musiciansGroup, int numOfMusicians, int numOfInstruments);
// Q5




#endif 
