# Band Manager Exercise in C Language

As part of a Introduction to programming course, we were asked to build a manager software for managing bands.
The purpose of the program is to organize performances by assigning musicians from the pool to the performances.


## Project Goals
- Using Data Structures 
- Practice Recursion and Trees
- Working with files
- Creating A matching algorithm based on information

# Instructions
- The program accepts as an argument two parameters which are names of text files. 
1. The first file is the musical instrument file.
2. The second argument of the program is the name of the musicians file.
- Bulding Musicians Stock.
1. We saved all the musicians that are listed in a storage file which is an array of pointers to Musician named MusiciansGroup.
2. We used structs as wise:

```c
typedef struct
{
 short unsigned insId;
 float price;
} MusicianPriceInstrument;

typedef struct
{
 **char name;
 MusicianPriceInstrument; // instruments MPIList
} Musician;

```
- We maintained an array of arrays called MusiciansCollection of pointers to musicians in the MusiciansGroup array.
1. If a musician knows how to play x instruments he will have a total of x votes from MusiciansCollection.
2. The number of members of the MusiciansCollection array will be the number of types of musical instruments.

![Music.jpg](https://user-images.githubusercontent.com/74871538/208752159-aa662966-9cf3-4393-95bd-8c15b4ab4f32.svg)


## Finding a match
Here's the code for maintaing the musicians array and finding the match based on their skills

```c
for (index = 0; index < concertNum; index++) { // loop concerts

		// ìäëðéñ ìôä àú äîàìå÷ ëé àæ àðçðå ãåøñéí àú îòøê äîåæé÷àéí ùì ääåôòåú ä÷åãîåú
		curr = concertArr[index].instruments.head;
		logSize = 0;


		while (curr = !NULL && isConcertOn) // loop instruments per concert
		{

			// sort by importance
			sortMusiciansArrByImportance(musiciansCollection[curr->CI.inst], curr->CI.inst, curr->CI.importance, numOfMusicians);

			musiciansForConcertArr = (Musician**)realloc(musiciansForConcertArr, logSize + sizeof(Musician*) * (curr->CI.num));
			checkMemoryAllocation(musiciansForConcertArr);

			// loop Musicians of same instrument
			for (int i = 0; i < curr->CI.num; i++)
			{
				if (curr->CI.num > indicesArr[curr->CI.inst]) { // àåìé ìäåöéà àú äúðàé îçåõ ììåìàä åìäåñéó àåúå ø÷ ëàùø îâãéìéí àú 

					isConcertOn = false;

					// ìòùåú ÷åáõ äãôñåú åôåð÷öéä ðôøãú ìëì äãôñä
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
				else
					(curr->CI.num)++;
			} // loop Musicians
			curr = curr->next;
		} // loop concert instruments
    
```


 


##### Made by [Ori Nurieli](https://github.com/orinurieli) & [Tahel Karavani](https://github.com/tahelka)  
