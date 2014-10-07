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
	printf("Partition All : \n");
	partitionAll(n);
	printf("Partition Increasing : \n");
	partitionIncreasing(n);
	printf("Partition Decreasing : \n");
	partitionDecreasing(n);
	printf("Partition Even : \n");
	partitionEven(n);
	printf("Partition Odd : \n");
	partitionOdd(n);
	printf("Partition Odd and Even : \n");
	partitionOddAndEven(n);
	printf("Partition Prime : \n");
	partitionPrime(n);
	return EXIT_SUCCESS;

}