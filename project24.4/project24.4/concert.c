// Q5

#include "concert.h"

Concert* createConcertArr(InstrumentTree tree, int numOfMusicians) {
	Concert* concertArr;
	Concert newConcert;
	char ch;
	char* instrumentName;
	int id;
	int amount;
	int importance;
	int logSize = 0;
	int phySize = 1;
	bool endOfInput = false;
	int numOfConcerts = 0;
	int phyConcertArrSize = 1;

	concertArr = (Concert*)malloc(sizeof(Concert));
	checkMemoryAllocation(concertArr);

	(newConcert.name) = (char*)malloc(sizeof(char));
	checkMemoryAllocation(newConcert.name);


	ch = getchar();


	// maybe to do this in one loop ! 

	while (!endOfInput) { // get the whole concerts

		// get one line, one concert

		makeEmptyCIList(&(newConcert.instruments));

		// get concert name
		while (ch != ' ') {

			if (logSize == phySize) {
				phySize *= 2;
				(newConcert.name) = (char*)realloc(newConcert.name, sizeof(char) * phySize);
				checkMemoryAllocation(newConcert.name);
			}

			(newConcert.name)[logSize] = ch;
			logSize++;

			ch = getchar();
		}

		shrinkAllocationStr(&(newConcert.name));

		// get date and hour of concert dd mm yyyy hh:mm  
		scanf("%d", &(newConcert.date_of_concert.day));
		scanf("%d", &(newConcert.date_of_concert.month));
		scanf("%d", &(newConcert.date_of_concert.year));
		newConcert.date_of_concert.hour = getAndConvertHourOfConcert();

		printf("%d", (newConcert.date_of_concert.day));
		printf("%d", (newConcert.date_of_concert.month));
		printf("%d", (newConcert.date_of_concert.year));
		printf("%0.2f", (newConcert.date_of_concert.hour));

		// FIX: think about better solution
		instrumentName = (char*)malloc(sizeof(char) * MAX_INSTRUMENT_LENGTH);
		checkMemoryAllocation(instrumentName);

		scanf("%s", instrumentName);// name

		while (instrumentName != '\n') {

			// get CInstrument data

			shrinkAllocationStr(&instrumentName);

			id = findInsId(tree, instrumentName);
			scanf("%d", &amount); // amount
			scanf("%d", &importance); // importance

			// update CI list
			insertDataToEndCIList(&(newConcert.instruments), id, amount, importance);

			instrumentName = (char*)malloc(sizeof(char) * MAX_INSTRUMENT_LENGTH);
			checkMemoryAllocation(instrumentName);

			scanf("%s", instrumentName);// name
			
		}

		// add concert to concertArr

		if (numOfConcerts == phyConcertArrSize) {
			phyConcertArrSize *= 2;
			concertArr = (Concert*)realloc(concertArr, sizeof(Concert)*phyConcertArrSize);
			checkMemoryAllocation(concertArr);
		}

		concertArr[numOfConcerts] = newConcert;

		ch = getchar();

		if (ch == '\n') { // if there is an empty line, its end of input

			endOfInput = true;
		}
		else {
			newConcert.instruments.head->CI.num;

		}


	}

	// fix: shrink array, we dont have a general function for that
	// fix: we need to to add this condition for all shrinks arrays. (?) !!!!!!!!
	if (numOfConcerts < phyConcertArrSize) {
		concertArr = (Concert*)realloc(concertArr, sizeof(Concert) * numOfConcerts);
		checkMemoryAllocation(concertArr);
	}

	return concertArr;
}

void manageMusiciansForConcerts(Concert* concertArr, Musician*** musiciansCollection, int concertNum, int* indicesArr, int numOfMusicians) {
	// MS[insID] -> sort by importance and price
// if important -> expensive to cheap
// else -> cheap to expensive

	CIListNode* curr;
	Musician** musiciansForConcertArr;
	int logSize = 0;
	int index;
	bool isConcertOn = true;

	musiciansForConcertArr = (Musician**)malloc(musiciansForConcertArr, sizeof(Musician*));
	checkMemoryAllocation(musiciansForConcertArr);

	for (index = 0; index < concertNum; index++) { // loop concerts

		// להכניס לפה את המאלוק כי אז אנחנו דורסים את מערך המוזיקאים של ההופעות הקודמות
		curr = concertArr[index].instruments.head;
		logSize = 0;


		while (curr = !NULL && isConcertOn) // loop instruments per concert
		{

			// arg1 - arr of musicians, arg2 - importance
			sortMusiciansArrByImportance(musiciansCollection[curr->CI.inst], curr->CI.inst, curr->CI.importance, numOfMusicians);

			// loop Musicians of same instrument

			musiciansForConcertArr = (Musician**)realloc(musiciansForConcertArr, logSize + sizeof(Musician*) * (curr->CI.num));
			checkMemoryAllocation(musiciansForConcertArr);

			for (int i = 0; i < curr->CI.num; i++)
			{
				if (curr->CI.num > indicesArr[curr->CI.inst]) { // אולי להוציא את התנאי מחוץ ללולאה ולהוסיף אותו רק כאשר מגדילים את 
																	// curr->(CI.num)
					isConcertOn = false;

					// לעשות קובץ הדפסות ופונקציה נפרדת לכל הדפסה
					printf("Could not find musicians for the concert %s", concertArr[index].name);
					printf("\n\n");
					break; 	// go to next concert


				}

				// check if Musician was not picked
				else if (musiciansCollection[curr->CI.inst][i]->concertInstrument_id == DEFUALT_ID)
				{
					musiciansForConcertArr[logSize] = musiciansCollection[curr->CI.inst][i];
					musiciansCollection[curr->CI.inst][i]->concertInstrument_id = curr->CI.inst;
					logSize++;
				}
				else {
					(curr->CI.num)++;
				}
			}

			curr = curr->next;

		}

		if (isConcertOn) {
			printConcertDetails(concertArr[index], logSize, musiciansForConcertArr);
		}
	}

	free(musiciansForConcertArr);

}

void printConcertDetails(Concert concert, int numOfConcertMusicians, Musician** musiciansForConcertArr) {

	// FIX: change the name "listNode to MPILNODE !!
	ListNode* playInstrument; // the instrument node that a musician is going to play on a concert
	printf("Concert name: %s\n", concert.name);
	printf("Date: %02d/%02d/%04d %02d:%02d\n", concert.date_of_concert.day, concert.date_of_concert.month, concert.date_of_concert.year, (int)concert.date_of_concert.hour,
		(int)(60 * (concert.date_of_concert.hour - (int)concert.date_of_concert.hour)));
	printf("The next musicians will play on concert:\n");
	for (int i = 0; i < numOfConcertMusicians; i++)
	{
		playInstrument = findInstrumentNode(&(musiciansForConcertArr[i]->instruments), musiciansForConcertArr[i]->concertInstrument_id);
		printf("The musician ");
		printFullName(musiciansForConcertArr[i]->name);
		printf("will play on %s, price: %d\n" , playInstrument->rate.instrumentName, playInstrument->rate.price);
	}
	printf("\n\n");

}

void printFullName(char** fullFame) {
	
}

ListNode* findInstrumentNode(MPIList* lst , int id) {
	ListNode* curr;
	curr = lst->head;

	while (curr!=NULL) {
		if (curr->rate.insId == id) {
			return curr;
		}
		curr = curr->next;
	}
}

bool checkIfMusicianAlreadyPlays(Musician** musiciansForConcertArr, int size, Musician* musician) {

	for (int i = 0; i < size; i++)
	{
		if (musiciansForConcertArr[i] == musician) {
			return true;
		}
	}

	return false;
}

float getAndConvertHourOfConcert() {
	int min, sec;

	scanf("%d", &min);
	getchar();
	scanf("%d", &sec);

	return min + (sec / TOTAL_SECONDS);
}

void sortMusiciansArrByImportance(Musician** musiciansArr, int currInstrumentID, int importance, int size) {

	if (importance == 0) {
		ascendingBubbleSort(musiciansArr, currInstrumentID, size);
	}
	else { // its equal 1
		descendingBubbleSort(musiciansArr, currInstrumentID, size);
	}
}

void ascendingBubbleSort(Musician** musiciansArr, int concertInstrumentID, int size) // sort by price
{
	int i, j;
	ListNode* currInstrument;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			currInstrument = musiciansArr[j]->instruments.head;
			while (currInstrument != NULL) // loop Musician instruments
			{
				if (currInstrument->rate.insId == concertInstrumentID) // finds the correct instrument the Musician plays in concert
				{
					if (currInstrument->rate.price > (currInstrument->next)->rate.price) // swap Musicinas by price
					{
						swap = musiciansArr[j];
						musiciansArr[j] = musiciansArr[j + 1];
						musiciansArr[j + 1] = swap;
					}
				}

				currInstrument = currInstrument->next;
			}
		}
	}

}

void descendingBubbleSort(Musician** musiciansArr, int concertInstrumentID, int size) // sort by price
{
	int i, j;
	ListNode* currInstrument;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			currInstrument = musiciansArr[j]->instruments.head;
			while (currInstrument != NULL) // loop Musician instruments
			{
				if (currInstrument->rate.insId == concertInstrumentID) // finds the correct instrument the Musician plays in concert
				{
					if (currInstrument->rate.price <= (currInstrument->next)->rate.price) // swap Musicinas by price
					{
						swap = musiciansArr[j];
						musiciansArr[j] = musiciansArr[j + 1];
						musiciansArr[j + 1] = swap;
					}
				}

				currInstrument = currInstrument->next;
			}
		}
	}

