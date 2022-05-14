#include "utils.h"


void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Error allocating memory!");
		exit(1);
	}
}
