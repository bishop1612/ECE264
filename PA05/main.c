#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		return EXIT_FAILURE;
	}
	int n = (int) strtol(argv[1], NULL, 10);
	if(n <= 0)
	{
		return EXIT_FAILURE;
	}
	partitionPrime(n);
	return EXIT_SUCCESS;

}