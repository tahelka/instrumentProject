#ifndef __CONCERT_H
#define __CONCERT_H

// Ori and Tahel

#define _CRT_SECURE_NO_WARNINGS

#define TOTAL_SECONDS 60.00

// dlskjflksdjflksd 
// tahhhhhhhhhhhhhhhhhhhhhhhhhhhhh

#include <stdio.h>
#include <stdlib.h>
#include "trees.h"
#include "utils.h"
#include "concertLists.h"
#include "lists.h"

typedef struct date
{
	int day, month, year;
	float hour;
} Date;

typedef struct concert
{
	Date date_of_concert; // ההופעה קיום תאריך
	char* name; // שם ההופעה
	CIList instruments; // ConcertInstrument כלי הנגינה ברשימה מקושרת של 

} Concert;

Concert* createConcertArr(InstrumentTree tree);
float getAndConvertHourOfConcert();

#endif