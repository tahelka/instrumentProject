#include "concertLists.h"

void printCIList(CIList* lst)
{
	CIListNode* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		printf("ID: %d ", curr->CI.inst);
		printf("amount: %d ", curr->CI.num);
		printf("importance: %d", curr->CI.importance);
		curr = curr->next;
	}
	printf("\n");
}

//
//CIList listConcat(CIList* l1, CIList* l2)
//{
//	CIList res;
//	if (isEmptyList(l1) == TRUE && isEmptyList(l2) == TRUE)
//		makeEmptyList(&res);
//	else if ((isEmptyList(l1) == TRUE))
//		res = *l2;
//	else if ((isEmptyList(l2) == TRUE))
//		res = *l1;
//	else
//	{
//		l1->tail->next = l2->head;
//		res.head = l1->head;
//		res.tail = l2->tail;
//	}
//	return res;
//}

BOOL isEmptyCIList(CIList* lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

// להמשיך מפה
CIListNode* createNewCIListNode(int id, int amount, int importance, CIListNode* next)
{
	CIListNode* res;
	res = (CIListNode*)malloc(sizeof(CIListNode));
	checkMemoryAllocation(res);

	res->CI.importance= importance;
	res->CI.inst= id;
	res->CI.num= amount;
	res->next = next;

	return res;
}

void insertDataToEndCIList(CIList* lst, int id, int amount, int importance)
{
	CIListNode* newTail;
	
	/*newTail->CI.inst= id;
	newTail->CI.importance = importance;
	newTail->CI.num = amount;*/

	newTail = createNewCIListNode(id,amount, importance, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertNodeToEndCIList(CIList* lst, CIListNode* tail)
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

void makeEmptyCIList(CIList* lst) {
	lst->head = lst->tail = NULL;
}




