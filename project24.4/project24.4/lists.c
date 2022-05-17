#include "lists.h"

void printList(MPIList* lst)
{
	ListNode* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		printf("id: %d, price: %0.2f \n", curr->rate.insId, curr->rate.price);
		curr = curr->next;
	}
	printf("\n");
}

MPIList copyList(MPIList* lst)
{
	MPIList res;
	ListNode* curr = lst->head;
	makeEmptyList(&res);
	while (curr != NULL)
	{
		insertDataToEndList(&res, curr->rate.insId, curr->rate.price);
		curr = curr->next;
	}
	return res;
}

MPIList listConcat(MPIList* l1, MPIList* l2)
{
	MPIList res;
	if (isEmptyList(l1) == TRUE && isEmptyList(l2) == TRUE)
		makeEmptyList(&res);
	else if ((isEmptyList(l1) == TRUE))
		res = *l2;
	else if ((isEmptyList(l2) == TRUE))
		res = *l1;
	else
	{
		l1->tail->next = l2->head;
		res.head = l1->head;
		res.tail = l2->tail;
	}
	return res;
}

BOOL isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

ListNode* createNewListNode(MusicianPriceInstrument rate, ListNode* next)
{
	ListNode* res;
	res = (ListNode*)malloc(sizeof(ListNode));
	checkMemoryAllocation(res);
	res->rate = rate;
	res->next = next;
	return res;
}

void insertDataToEndList(MPIList* lst, int id, int price, char* instrumentName)
{
	ListNode* newTail;
	MusicianPriceInstrument rate;
	rate.insId = id;
	rate.price = price;
	rate.instrumentName = instrumentName;

	newTail = createNewListNode(rate, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(MPIList* lst, ListNode* tail)
{
	if (isEmptyList(lst) == TRUE) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

void makeEmptyList(MPIList* lst) {
	lst->head = lst->tail = NULL;
}




