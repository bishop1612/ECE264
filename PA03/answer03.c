#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cmpstringp ( const void * arg1 , const void * arg2 )
{
	// ptr1 and ptr2 are string *
	// string is char * , thus ptr1 and ptr2 are char * *
	const char * const * ptr1 = ( const char * *) arg1 ;
	const char * const * ptr2 = ( const char * *) arg2 ;
	const char * str1 = * ptr1 ;
	const char * str2 = * ptr2 ;
	return strcmp(str1,str2);
}
int comparefunc ( const void * arg1 , const void * arg2 ) // for
{
	const char * ptr1 = ( const char *) arg1 ;
	const char * ptr2 = ( const char *) arg2 ;
	char val1 = * ptr1 ;
	char val2 = * ptr2 ;
	// printf (" comparefunc : % d % d \ n " , val1 , val2 ) ;
	if ( val1 < val2 ) { return -1; }
	if ( val1 == val2 ) { return 0; }
	return 1;
}
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
	int destlen = 0;
	int srclen = 0;
	if(src != NULL){
		srclen = strlen(src);
	}
	if(*dest != NULL){
		destlen = strlen(*dest);
	}
	if((*dest == NULL) || ((destlen + srclen + 1) > *n))
	{
		char *temp = malloc(1 + 2 * (destlen + srclen)) ;
		//temp = '';
		*n = (1 + 2 * (destlen + srclen));

		if(*dest != NULL)
		{
			strcpy(temp,*dest);
			free(*dest);
		}
		*dest = temp;
	}
	//printf("\n%s\n",*dest);
	if(destlen == 0)
	{
		strcpy(*dest,src);
		return *dest;
	}
	else
	{
		*dest = strcat(*dest,src);
	}
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

char * * explode(const char * str, const char * delims, int * arrLen)
{
	int N = 0;
	int pos = 0;
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
	int arrInd = 0; // this is the next position where we'll create a string
	int last = 0; // 1 + the last index we saw a delimiter. Init to 0.
	int diff = 0;
	while(str[pos] != '\0')
	{
		if(strchr(delims,str[pos]) != NULL)
		{
			diff = pos - last;
			if(diff != 0){
				strArr[arrInd] = malloc((diff) * sizeof(char *));
				memcpy(strArr[arrInd], &str[last] , (diff)*sizeof(char));
				strArr[arrInd][diff] = '\0';
			}
			else
			{
				strArr[arrInd] = malloc((1) * sizeof(char *));
				//memcpy(strArr[arrInd], &str[last] , (diff)*sizeof(char));
				strArr[arrInd][diff] = '\0';

			}
			//printf("%s", temp);0
			last = pos + 1;
			arrInd++;
		}
		//iter = 0;
		pos++;
	}
	//printf("%d",pos);
	diff = strlen(str) - last;
	//printf("%d",strlen("Hello"));
	if(diff != 0)
	{
		strArr[arrInd] = malloc((diff) * sizeof(char *));
		memcpy(strArr[arrInd], &str[last] , (diff)*sizeof(char));
		strArr[arrInd][diff] = '\0';
	}	
	else
	{
		strArr[arrInd] = malloc((1) * sizeof(char *));
		//memcpy(strArr[arrInd], &str[last] , (diff)*sizeof(char));
		strArr[arrInd][diff] = '\0';
	}
	
	*arrLen = N+1;
	
	//printf("Last : %d",arrInd);
	/*while(last < strlen(str))
	{

	}*/
	/*char *temp2;
	while(last == strlen(str))
	{
		*temp2 = str[last];
		last++;
		temp2++;	
	}
	strArr[arrInd] = temp2;
	int iter = 0;
	while(iter <= N+1)
	{
		printf("%s", strArr[iter]);
		iter++;
	}*/
	
	return (char **)strArr;
}
/**
 * Takes an array of strings, and concatenates the elements into a single
 * string, placing 'glue' between each successive element.
 *
 * strArr: an array of strings
 * len: the length of the array 'strArr'
 * glue: string to concatenate between each element of 'strArr'
 *
 * For example:
 * int len;
 * char * * strArr = explode("100 224 147 80", " ", &len);
 * char * str = implode(strArr, len, ", ");
 * printf("(%s)\n", str); // (100, 224, 147, 80)
 *
 * Hint: use strcat_ex in a for loop.
 */
char * implode(char * * strArr, int len, const char * glue) 
{
	int i = 0;
	char *str = '\0';
	int n = 0;
	for(i = 0;i < len;i++)
	{
		strcat_ex(&str, &n, strArr[i]);
		if(i != len - 1)
		{
			strcat_ex(&str, &n, glue);
		}
	}
	return str;
}
/**
 * Takes an array of C-strings, and sorts them alphabetically, ascending.
 *
 * arrString: an array of strings
 * len: length of the array 'arrString'
 *
 * For example, 
 * int len;
 * char * * strArr = explode("lady beatle brew", " ", &len);
 * sortStringArray(strArr, len);
 * char * str = implode(strArr, len, " ");
 * printf("%s\n"); // beatle brew lady
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_ understand the typecasts.
 */
void sortStringArray(char * * arrString, int len)
{
	if(arrString != NULL)
	{
		qsort(&arrString[0] , len , sizeof ( char *) , cmpstringp ) ;
	}
}
/**
 * Sorts the characters in a string.
 *
 * str: string whose characters are to be sorted
 *
 * For example, 
 * char * s1 = strdup("How did it get so late so soon?");
 * sortStringCharacters(s1)
 * // s1 is now "       ?Haddeegiilnooooossstttw"
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_  understand the typecasts.
 */
void sortStringCharacters(char * str)
{
	//printf("%p\n",&str);
	if(str != NULL)
	{
		qsort (str, strlen(str) , sizeof ( char ) , comparefunc ) ;
	}	

	//printf("%s\n",str);
}
/**
 * Safely frees all memory associated with strArr, and then strArr itself.
 * Passing NULL as the first parameter has no effect.
 *
 * strArr: an array of strings
 * len: the length of 'strArr'
 *
 * int len;
 * const char * abe = "Give me six hours to chop down a tree and I will spend\n"
 *                    "the first four sharpening the axe.";
 * char * * strArr = explode(abe, "\n ");
 * destroyStringArray(strArr, len); // cleans memory -- no memory leaks
 * destroyStringArray(NULL, 0); // does nothing, does not crash.
 */
void destroyStringArray(char * * strArr, int len)
{
	//printf("%d\n", len);
	if(strArr != NULL)
	{	
		int i = 0;
		for(i = 0;i < len;i++)
		{
			free(strArr[i]);
		}
		free(strArr);
	}
}