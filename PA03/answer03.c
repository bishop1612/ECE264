#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * Append the C-string 'src' to the end of the C-string '*dest'.
 *
 * strcat_ex(...) will append the C-string 'src' to the end of the string
 * at '*dest'. The parameter 'n' is the address of a int that specifies how
 * many characters can safely be stored in '*dest'. 
 *
 * If '*dest' is NULL, or if '*dest' is not large enough to contain the result
 * (that is, the sum of the lengths of *dest, src, and the null byte), then
 * strcat_ex will:
 * (1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))
 * (2) set '*n' to the size of the new buffer
 * (3) copy '*dest' into the beginning of the new buffer
xv * (4) free the memory '*dest', and then set '*dest' to point to the new buffer
 * (5) concatenate 'src' onto the end of '*dest'.
 *
 * Always returns *dest.
 *
 * Why do we need to pass dest as char * *, and n as int *? 
 * Please see the FAQ for an answer.
 *
 * Hint: These <string.h> functions will help: strcat, strcpy, strlen.
 * Hint: Leak no memory.
 */
char * strcat_ex(char * * dest, int * n, const char * src)
{
	//int src_len = strlen(src);
	//int dst_len = strlen(*dest);
	////printf("En\n");
	//printf("After swap, str1 == %p (i.e., '%s'), "
      // "str2 == %p (i.e., '%s')\n", src, src, *dest, *dest);
	char *temp;
	if((*dest == NULL) || ((*dest == NULL? 0:strlen(*dest)) + strlen(src) + 1 > *n))
	{
		temp = malloc((1 + 2 * ( (*dest==NULL?0:strlen(*dest)) + strlen(src)))) ;
		*n = sizeof(temp);
		//printf("value of n is %d\n", *n);
		if(*dest != NULL)
		{
			strcpy(temp,*dest);
			//printf("temp's content after strcpy : %s\n", temp);
		}
		//printf("temp's content after strcpy : %s\n", temp);
		//printf("temp's content after strcpy : %s\n", *dest);
		free(dest);
		//printf("temp's content after strcpy : %s\n", *dest);

		// free(NULL) won't throw an error
		*dest = temp;
	}
	*dest = strcat(*dest,src);
	return *dest;
}
/**
 * Takes a string and splits it into an array of strings according to delimiter.
 * The memory location '*arrLen' is initialized to the length of the returned
 * array.
 *
 * str: A string to split
 * delims: a string that contains a set of delimiter characters. explode(...) 
 *         will split the string at any character that appears in 'delims'.
 * arrLen: pointer to an int that is used to store the resultant length of the
 *         returned array.
 *
 * For example, if delimiter is white space " \t\v\n\r\f", then,
 * int len;
 * char * * strArr = explode("The\nTuring test", " \t\v\n\r\f", &len);
 * // len = 3, strArr[0] is "The", strArr[1] is "Turing", strArr[2] is "test"
 *
 * Hint: you can use <string.h> functions "memcpy" and "strchr"
 *       "memcpy" copies blocks of memory.
 *       "strchr" can be used to tell if a specific character is in delims.
 * Hint: this question is hard; it will help to draw out your algorithm.
 * Hint: read the FAQ...
 */
/*char * * explode(const char * str, const char * delims, int * arrLen)
{
	int N = 0;
	int pos = 0;
	int iter = 0;
	while(str[pos] != '\0')
	{
		if(strchr(delims,str[pos]) != NULL)
		{
			N++;
		}
		pos++;
	}
	char * * strArr = malloc((N+1) * sizeof(char *)); 
	pos = 0;
	arrInd = 0; // this is the next position where we'll create a string
	last = 0; // 1 + the last index we saw a delimiter. Init to 0.
	while(str[pos] != '\0')
	{
		if(strchr(delims,str[pos]) != NULL)
		{
			char *temp;
			while(last == pos)
			{
				temp[iter] = str[last];
				last++;
				iter++;
			}
			strArr[arrInd] = *temp;
			arrInd++;
			iter = 0;
		}
		pos++;
	}
	char *temp;
	while(last == strlen(*str))
	{
		temp[iter] = str[last];
		last++;
		iter++;	
	}
	strArr[arrInd] = *temp;
	*arrLen = strlen(**strArr);
	
	return **strArr;
}*/