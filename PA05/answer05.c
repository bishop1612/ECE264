#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Inefficient*/

/*Printing the partitions*/

void printPartition(int * arr, int length)
{
	int ind;
	printf("= ");
	for(ind = 0; ind < length -1 ; ind++)
	{
		printf("%d + ",arr[ind]);
	}
	printf("%d\n", arr[length - 1]);
}

/*Printing the decreasing partitions in reverse order*/

void printPartitiondec(int * arr, int length)
{
	int ind;
	printf("= ");
	for(ind = length - 1; ind > 0 ; ind--)
	{
		printf("%d + ",arr[ind]);
	}
	printf("%d\n", arr[0]);
}

/**
 * Prints all the partitions of a positive integer value.
 *
 * Example:
 * partitionAll(3); // prints the following: (line order not important)
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 *
 * Note: Order does not matter, and neither does white-space. 
 * Hint: look at file: expected/partitionAll.output
 */

void partall(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartition(arr, ind);
		return;
	}
	for(val = 1; val <= left; val++)
	{
		arr[ind] = val;
		partall(arr, ind + 1, left - val);
	}
}


void partitionAll(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	partall(arr, 0, value);
	free(arr);
}

/**
 * Prints all partitions that have strictly increasing values.
 *
 * Example:
 * partitionIncreasing(5); // prints the following: (line order not important)
 * = 1 + 4
 * = 2 + 3
 * = 5
 * 
 * These partitions are excluded because they are not _strictly_ increasing
 * 1 + 1 + 3
 * 2 + 1 + 2
 * 3 + 2
 * 
 * Note:
 * The program should generate only valid partitions.  Do not
 * generates all partitions and then filter for validity. If you 
 * do this, you will almost certainly have trouble understanding the exam.
 *
 * Hint: look at file: expected/partitionIncreasing.output
 */

void partinc(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartition(arr, ind);
		return;
	}
	int min = 1;
	if(ind != 0)
	{
		min = arr[ind - 1] + 1;
	}
	for(val = min; val <= left; val++)
	{
		arr[ind] = val;
		partinc(arr, ind + 1, left - val);
	}
}

void partitionIncreasing(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	partinc(arr, 0, value);
	free(arr);
}

/**
 * Prints all partitions that have strictly decreasing values.
 *
 * Example:
 * partitionDecreasing(5); // prints the following: (line order not important)
 * = 3 + 2
 * = 4 + 1
 * = 5
 * 
 * These partitions are excluded because they are not _strictly_ decreasing
 * 1 + 1 + 3
 * 2 + 1 + 2
 * 
 * See: note on partitionIncreasing(...)
 * Hint: look at file: expected/partitionDecreasing.output
 */
void partdec(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartitiondec(arr, ind);
		return;
	}
	int min = 1;
	if(ind != 0)
	{
		min = arr[ind - 1] + 1;
	}
	for(val = min; val <= left; val++)
	{
		arr[ind] = val;
		partdec(arr, ind + 1, left - val);
	}
}

void partitionDecreasing(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	partdec(arr, 0, value);
	free(arr);
}

/**
 * Prints all partitions comprised solely of odd numbers.
 *
 * Example:
 * partitionOdd(5); // prints the following (line order not important)
 * = 1 + 1 + 1 + 1 + 1
 * = 1 + 1 + 3
 * = 1 + 3 + 1
 * = 3 + 1 + 1
 * = 5
 * 
 * See: note on partitionIncreasing(...)
 * Hint: for odd numbers, (value % 2 != 0)
 * Hint: look at file: expected/partitionOdd.output
 */
void partodd(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartition(arr, ind);
		return;
	}
	for(val = 1; val <= left; val += 2)
	{
		arr[ind] = val;
		partodd(arr, ind + 1, left - val);
	}
}
void partitionOdd(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	partodd(arr, 0, value);
	free(arr);
}
/**
 * Prints all partitions comprised solely of even numbers.
 *
 * Example:
 * partitionEven(6); // prints the following (line order not important)
 * = 2 + 2 + 2
 * = 2 + 4
 * = 4 + 2
 * = 6
 * 
 * See: note on partitionIncreasing(...)
 * Hint: for even numbers, (value % 2 == 0)
 * Hint: you can never partition an odd number with even numbers alone.
 * Hint: look at file: expected/partitionEven.output
 */

void parteven(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartition(arr, ind);
		return;
	}
	for(val = 2; val <= left; val += 2)
	{
		arr[ind] = val;
		parteven(arr, ind + 1, left - val);
	}
}
void partitionEven(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	parteven(arr, 0, value);
	free(arr);
}

/**
 * Prints all partitions that do not have consecutive odd or even numbers.
 * In other words, it only prints partitions that have alternating odd and 
 * even numbers.
 *
 * Example:
 * partitionOddAndEven(5); // prints the following (line order not important)
 * = 1 + 4
 * = 2 + 1 + 2
 * = 2 + 3
 * = 3 + 2
 * = 4 + 1
 * = 5
 *
 * See: note on partitionIncreasing(...)
 * Hint: look at file: expected/partitionOddAndEven.output
 */
void partoddeven(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartition(arr, ind);
		return;
	}
	for(val = 1; val <= left; val++)
	{
		int valid = 0;
		if(ind == 0)
		{
			valid = 1;
		}
		else
		{
			valid = (arr[ind - 1] % 2) != (val % 2);
		}
		if(valid == 1)
		{
			arr[ind] = val;
			partoddeven(arr, ind + 1, left - val);

		}
	}
}
void partitionOddAndEven(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	partoddeven(arr, 0, value);
	free(arr);
}
/**
 * Prints all partitions that comprise solely of prime numbers.
 *
 * Example:
 * partitionPrime(5); // prints the following (line order not important)
 * = 2 + 3
 * = 3 + 2
 * = 5
 * 
 * See: note on partitionIncreasing(...)
 * Hint: you will need to write a function that checks if a number is prime.
 * Hint: 1 is not a prime number.
 * Hint: look at file: expected/partitionPrime.output
 */

/*Function to find out whether a function is prime or not*/

int prime(int n)
{
	int ind;
	int rval = 1;
	for(ind = 2;ind < n; ind++)
	{
		if(n % ind == 0)
		{
			return 0;
		}
	}
	return rval;
}

void partprime(int *arr, int ind, int left)
{
	int val;
	if (left == 0)
	{
		printPartition(arr, ind);
		return;
	}
	for(val = 2; val <= left; val++)
	{
		int valid = 0;
		valid = prime(val);
		if(valid == 1)
		{
			arr[ind] = val;
			partprime(arr, ind + 1, left - val);

		}
	}
}
void partitionPrime(int value)
{
	int *arr;
	arr = malloc(sizeof(int) * value);
	partprime(arr, 0, value);
	free(arr);
}