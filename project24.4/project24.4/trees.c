#include "trees.h"

// Q1

InstrumentTree getInstrumentsTreeFromFile(FILE* ptrInstrumentsFile, int* instrumentID)
{
	TreeNode* instrumentNode;
	InstrumentTree instrumentsTree;
	char* instrumentName;
	char* flagStr = '1';
	*instrumentID = 0;

	instrumentsTree.root = NULL;

	getNewLineFromFile(ptrInstrumentsFile, &instrumentName, &flagStr); // get first instrument name

	while (flagStr != NULL)
	{
		shrinkAllocationStr(&instrumentName); // shrinking str to the actually length of the instrument name

		instrumentNode = createNewTNode(instrumentName, *instrumentID, NULL, NULL);

		addNewTNodeToInstrumentsBinaryTree(&instrumentsTree, instrumentNode);

		(*instrumentID)++;

		getNewLineFromFile(ptrInstrumentsFile, &instrumentName, &flagStr); // get the next instrument name

	}
	(*instrumentID)++; // because the index starts with zero
	return instrumentsTree;
}

void shrinkAllocationStr(char** strPtr) {
	int len;

	len = strlen(*strPtr); // strlen does not include '\0' 
								   // however fgets adds '\n' at the end of the string 
								   // so we dont need to add one for '\0'

	(*strPtr)[len - 1] = '\0';

	*strPtr = (char*)realloc(*strPtr, len);
	checkMemoryAllocation(*strPtr);
}

void getNewLineFromFile(FILE* ptrInstrumentsFile, char** instrumentName, char** flagStr) {

	*instrumentName = (char*)malloc(sizeof(char) * MAX_INSTRUMENT_LENGTH);
	checkMemoryAllocation(*instrumentName);

	*flagStr = fgets(*instrumentName, MAX_INSTRUMENT_LENGTH, ptrInstrumentsFile);
}

void addNewTNodeToInstrumentsBinaryTree(InstrumentTree* tr, TreeNode* newNode) {
	if (tr->root == NULL) {
		tr->root = newNode;
	}
	else {
		addNewTNodeToInstrumentsBinaryTreeHelper(tr->root, newNode);
	}
}

void addNewTNodeToInstrumentsBinaryTreeHelper(TreeNode* root, TreeNode* newNode)
{
	TreeNode* curr;
	int strCheck = 0;

	strCheck = strcmp(root->instrument, newNode->instrument);

	// Recursion call
	if (strCheck > 0) // root instrument > newNode instrument
	{
		if (root->left == NULL) // if root has no left child
			root->left = newNode;
		else
			addNewTNodeToInstrumentsBinaryTreeHelper(root->left, newNode);
	}
	else if (strCheck < 0) // root instrument < newNode instrument
	{
		if (root->right == NULL) // if root has no right child
			root->right = newNode;
		else
			addNewTNodeToInstrumentsBinaryTreeHelper(root->right, newNode);
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


// Q2

/* Searching for a value in a binary tree - returning the address of the node
containing it or NULL */
int findInsId(InstrumentTree tree, char* instrument)
{
	return findInsIdHelper(tree.root, instrument);
}

int findInsIdHelper(TreeNode* root, char* instrument)
{
	int res;

	if (root == NULL)
		return NOT_FOUND;

	else if (strcmp(root->instrument, instrument) == 0) // if those instrument names are the same
		return root->insld;
	else
	{
		res = findInsIdHelper(root->left, instrument);

		if (res == NOT_FOUND) // Not found in left side, so check on the right side
			res = findInsIdHelper(root->right, instrument);

		return res;
	}
}



// Q3


// get one musician to pointer array
Musician** getMusicianFromFile(InstrumentTree tr, FILE* ptrMusiciansFile, int* numOfMusicians)
{
	// get new musician from file
	Musician** musiciansGroup;
	char** musicianDetails;
	char seperators[30] = " ,.;:?!-\t'()[]{}<>~_";
	char* token;
	char* flagStr = '1';
	int index = 0;
	int insId;
	float price = 0;

	bool endOfName = false; // end of musician's full name


	musiciansGroup = (Musician**)malloc(sizeof(Musician*));
	checkMemoryAllocation(musiciansGroup);

	getNewLineFromFile(ptrMusiciansFile, &musicianDetails, &flagStr); // get first musician with details

	while (flagStr != NULL) // loop musicians in musiciansGroup
	{

		musiciansGroup[index] = (Musician*)malloc(sizeof(Musician));
		checkMemoryAllocation(musiciansGroup[index]);

		musiciansGroup[index]->name = (char*)malloc(sizeof(char));
		checkMemoryAllocation(musiciansGroup[index]->name);

		musiciansGroup[index]->concertInstrument_id = DEFUALT_ID;

		makeEmptyList(&(musiciansGroup[index]->instruments));


		// לבדוק האם חייב להקטין את המערך (ועל הדרך להפטר מה"באק סלש אן" או שאפשר גם בלי זה והשורה הזו מיותרת
		// ERROR?
		shrinkAllocationStr(&musicianDetails); // shrinking str to the actually length 

		// strtok
		token = strtok(musicianDetails, seperators); // first token
		printf("__________ \n");

		printf("\nMusicina Full name: ");

		// walk through other tokens 
		while (token != NULL)
		{
			// Name tokens
			if (!endOfName && checkMusicianName(tr, token))
				insertToMusicianNameArr(&(musiciansGroup[index]->name), token);

			// Instruments detailes tokens
			else {
				endOfName = true;

				printf("\n\n");
				// ERROR - NOT PRINTING THE ACCORDIANS OF THE LAST MUSICIAN!!
				printf("Intrument: %s\n", token);

				insId = findInsId(tr, token);

				price = atoi(strtok(NULL, seperators));
				printf("Price: %0.2f", price);

				insertDataToEndList(&(musiciansGroup[index]->instruments), insId, price);
			}
			// next token
			token = strtok(NULL, seperators);
		}

		printf("\n");
		printf("Instrument list: \n");
		printList(&(musiciansGroup[index]->instruments)); // check

		getNewLineFromFile(ptrMusiciansFile, &musicianDetails, &flagStr); // get the next musician with details

		index++;
		endOfName = false;
	}

	*numOfMusicians = index + 1;
	return musiciansGroup;
}

// מערכים עדיף להחזיר כפרמטר סטטי ולא גנרי
void insertToMusicianNameArr(char*** fullName, char* token) {
	static int logSize = 1;
	static int phySize = 1;
	char** tempFullName;
	char* newName;
	int length = strlen(token) + 1;

	newName = (char*)malloc(sizeof(char) * length);
	checkMemoryAllocation(newName);

	newName = token;

	if (logSize == phySize) {
		phySize *= 2;

		(*fullName) = (char*)realloc(*fullName, sizeof(char) * phySize); // ERROR? maybe change: (*fullName) --> fullName[logSize]
		checkMemoryAllocation(*fullName);
	}

	(*fullName)[logSize - 1] = newName;

	printf("%s ", (*fullName)[logSize - 1]);

	logSize++;
}



// checks if the name is valid and not an instrument or price
bool checkMusicianName(InstrumentTree tr, char* str)
{
	// str has to be a name (not in the instruments tree)
	if (findInsId(tr, str) == NOT_FOUND)
		return true;
	// str is an instrument
	else
		return false;
}

// delete ?

//// create a new musician in the arr
//Musician* createNewMusician(char** musicianName, MPIList rateList, int concertInstrument_id)
//{
//	Musician* newMusician;
//	newMusician = (Musician*)malloc(sizeof(Musician));
//
//	newMusician->name = musicianName;
//	newMusician->concertInstrument_id = concertInstrument_id;
//
//	// another option, use copyList()
//	newMusician->instruments.head = rateList.head;
//	newMusician->instruments.tail = rateList.tail;
//}


// Q4

Musician*** createMusiciansCollection(Musician** musiciansGroup, int numOfInstruments, int numOfMusicians, int** indicesArr) {
	Musician*** musicianCollection;

	musicianCollection = (Musician***)malloc(sizeof(Musician**) * numOfInstruments);
	checkMemoryAllocation(numOfInstruments);

	// allocate first Musician for each collection
	for (int i = 0; i < numOfInstruments; i++)
		musicianCollection[i] = (Musician**)malloc(sizeof(Musician*)); // insID = 0

	*(indicesArr) = addMusicianToCollection(musicianCollection, musiciansGroup, numOfMusicians, numOfInstruments); // מכניס כל מוזיקאי למקום שלו בהתאם לכלים עליהם הוא מנגן

	return musicianCollection;
}

int* addMusicianToCollection(Musician*** musicianCollection, Musician** musiciansGroup, int numOfMusicians, int numOfInstruments)
{
	int* indices; // helper array for the size of every musicians's instrument array
	int id;
	ListNode* curr;

	indices = (int*)malloc(sizeof(int) * numOfInstruments);
	checkMemoryAllocation(indices);

	for (int i = 0; i < numOfInstruments; i++)
		indices[i] = 0;

	// loop musicianGroup
	for (int i = 0; i < numOfMusicians; i++)
	{
		curr = musiciansGroup[i]->instruments.head;

		// loop musician instruments list
		while (curr != NULL)
		{
			id = curr->rate.insId;

			// ריאלוק מקצה מקום אחד למרות שבסיבוב הראשון יש מקום (מהמאלוק). מיותר?
			musicianCollection[id] = (Musician**)realloc(musicianCollection[id], indices[id] + 1);
			checkMemoryAllocation(musicianCollection[id]);

			// add the musician to the right index in the MusiciansCollection by insID of the instrument
			musicianCollection[id][indices[id]] = musiciansGroup[i];

			indices[id]++;

			// move to the next instrument on the list
			curr = curr->next;
		}

	}
	return indices;
}



