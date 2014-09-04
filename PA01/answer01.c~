#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
    int iter;
    int sum = 0;
    for(iter = 0; iter < len; iter++)
    {
    	sum += array[iter];
    }
    return sum;
}

int arrayCountNegative(int * array, int len)
{
    int iter;
    int count = 0;
    for(iter = 0; iter < len; iter++)
    {
    	if(array[iter] < 0)
    		count++;
    }
    return count;
}

int arrayIsIncreasing(int * array, int len)
{    
    int ret = 0;
    if(len == 0)
    	return 1;
    int iter;
    int count = 0;
    for(iter = 0; iter < len - 1; iter++)
    {
    	if(array[iter] <= array[iter + 1])
    		count++;
    }
    if((count != (len - 1)) )
    	ret = 0;
    if(count == (len - 1))
    	ret = 1;
    return ret;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    int iter;
    int index = -1;
    for(iter = 0; iter < len; iter++)
    {
    	if(needle == haystack[iter])
    	{
    		index = iter;
    	}
    }
    return index;
}

int arrayFindSmallest(int * array, int len)
{
    int ret = 0;
    if(len == 0)
    	ret = 0;
    int iter;
    int small = array[0];
    for(iter = 0; iter < len; iter++)
    {
    	if(array[iter] <= small)
    		small = array[iter];
    }
    for(iter = 0; iter < len; iter++)
    {
    	if(array[iter] == small)
    		return iter;
        
    }
    return ret;
}
