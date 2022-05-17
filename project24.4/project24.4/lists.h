#ifndef __LISTS_H
#define __LISTS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct
{
	unsigned short insId; // מספר מזהה של כלי נגינה
	char* instrumentName; // name of instrument that the musician will play on it.
	float price; // מחיר שדורש הנגן עבור נגינה בכלי זה
} MusicianPriceInstrument;

typedef struct listNode
{
	MusicianPriceInstrument rate; // תעריף
	struct listNode* next;
	// struct listNode* prev; ?
} ListNode;

typedef struct mplist
{
	ListNode* head;
	ListNode* tail;
} MPIList;

typedef struct musician
{
	char** name; // מערך של השמות המרכיבים את שמו המלא 
	int numOfNames; // num of musician's names
	MPIList instruments; // כלי הנגינה ברשימה מקושרת של MusicianPriceInstrument
	int concertInstrument_id; // the id of the instrument that the musician will play on the concert
} Musician;

typedef int BOOL;
#define FALSE 0
#define TRUE 1

void printList(MPIList* lst);
MPIList copyList(MPIList* lst);
MPIList listConcat(MPIList* l1, MPIList* l2);
void makeEmptyList(MPIList* lst);
BOOL isEmptyList(MPIList* lst);
void insertDataToEndList(MPIList* lst, int id, int price);
ListNode* createNewListNode(MusicianPriceInstrument rate, ListNode* next);
void insertNodeToEndList(MPIList* lst, ListNode* tail);

#endif
