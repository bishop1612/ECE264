/** 
 * Length of C string 'str', excluding the terminating null byte ('\0')
 * 
 * Examples:
 * my_strlen("abc"); // 3
 * my_strlen("");   // 0
 * my_strlen(NULL); // error -- undefined behavior. You do not need to 
 *                  // consider this case. See the README -- FAQ for more info.
 */
#include <stdlib.h>

size_t my_strlen(const char * str) {
	int pos = -1;
	while(str[++pos] != '\0') {}
	return pos;
}

/**
 * Count the number of occurrences of character 'ch' in C string 'str'
 *
 * Examples: 
 * my_countchar("foo", 'o'); // 2
 */
int my_countchar(const char * str, char ch) {
	int n = 0;
	int pos = -1;
	while(str[++pos] != '\0') {
		if(str[pos] == ch) {
			n++;
		}
	}
	return n;
}

/**
 * Return a pointer to the first occurance of character 'ch' in C string 'str'
 * Return NULL if 'ch' is not found.
 *
 * Note that the terminating '\0' character is considered to be part of the 
 * string. Thus, if 'ch' is specified as '\0', then return a pointer to the
 * null terminator of the string.
 *
 * Examples:
 * const char * str = "Hello World!";
 * printf("'%s'\n", my_strchr(str, 'o')); // prints "'o World!'\n"
 * printf("'%s'\n", my_strchr(str, 'z')); // prints "'(null)'\n"
 *                                        // i.e., my_strchr(str, 'z') == NULL
 * printf("'%s'\n", my_strchr(str, '\0')); // prints "''\n"
 *
 * Please read the README FAQ before attempting this function.
 */

char * my_strchr(const char * str, int ch){
	int pos = 0;
	
	if(ch == '\0')
		return "";
	
	while(str[pos] != '\0'){
		if(str[pos] == ch)
		{
			loc = pos;
			return (char *)	pos;
		}
		pos++;
	}
	
	
	
	return NULL;
}


/** 
 * Same as my_strchr(...), except it searches from the right-hand-side 
 *
 * Examples:
 * const char * str = "Hello World!";
 * printf("'%s'\n", my_strrchr(str, 'o')); // prints "'orld!'\n"
 * printf("'%s'\n", my_strrchr(str, 'z')); // prints "'(null)'\n"
 *                                         // i.e., my_strrchr(str, 'z') == NULL
 * printf("'%s'\n", my_strrchr(str, '\0')); // prints "''\n" *
 */
char * my_strrchr(const char * str, int ch) {
	int len = 0;
	int iter = 0;
	len = my_strlen(str);
	int pos = -1;
	char newchar[len+1];
	for(iter = 0;iter <= len;iter++)
	{
		if(str[iter] == (char)ch)
		{
			pos = iter;
		}
	}
	if(pos != -1)
	{	
		iter = 0;
		while(pos >= (len))
		{
			newchar[iter++] = str[pos++];
		}		
	}
	return newchar;
}

/** Finds the first occurance of C-string 'needle' in C-string 'haystack'
 * Return 'haystack' when 'needle' is the empty string (ie, "").
 * The terminating null bytes are not compared.
 *
 * Examples:
 * const char * str = "Hello World!";
 * printf("'%s'\n", my_strstr(str, "World")); // prints "'World!'\n"
 * printf("'%s'\n", my_strstr(str, ""));      // prints "'Hello World!'\n"
 * printf("'%s'\n", my_strstr(str, "hello")); // prints "'(null)'\n"
 *                                      // i.e., my_strstr(str, "hello") == NULL
 */
/*char * my_strstr(const char * haystack, const char * needle) {
	int len,len2 = 0;
	int iter,iter2 = 0;
	len = my_strlen(haystack);
	int pos = 0;
	char str[len + 1] = NULL;
	char newchar[len+1] = NULL;
	for(iter = 0;iter <= len;iter++)
	{
			newchar[iter] = str[pos];
			if(str[pos] == " ")
			{

			}		
	}
	return newchar;

}*/

/**
 * Copys C-string 'src' (including the null-byte terminator) into the memory 
 * pointed to by 'dest'. The strings must not overlap, and 'dest' must be large
 * enough to contain 'src', *including* the terminating null-byte.
 *
 * Returns 'dest'
 *
 * Examples:
 * const char * str = "Hello World!"; // strlen(str) == 12, but 13 bytes with \0
 * char buffer[50];
 * printf("%s\n", my_strcpy(buffer, str)); // prints "Hello World!\n"
 */
char * my_strcpy(char * dest, const char * src)
{
	int len = 0;
	int iter = 0;
	len = my_strlen(src);
	int pos = 0;
	for(iter = 0;iter <= len;iter++)
	{
			dest[iter] = src[pos];
			pos++;		
	}
	return dest;
}
/**
 * Append C-string 'src' to C-string 'dest'. A precondition is 'Dest' must be 
 * large enough to contain both 'dest' and 'src', *including* the terminating
 * null-byte.
 *
 * Returns 'dest'
 *
 * Examples:
 * char buffer[50];
 * my_strcpy(buffer, "Hello ");
 * printf("%s\n", my_strcat(buffer, "Zippy!")); // prints "Hello Zippy!"
 */
char * my_strcat(char * dest, const char * src)
{
	int len,len2 = 0;
	int iter = 0;
	len = my_strlen(src);
	len2 = my_strlen(dest);
	char new[len+len2+1];
	int pos = -1;
	int newpos = 0;
	while(dest[++pos] != '\0') {
		new[newpos] = dest[pos];
		newpos++;
	}
	pos = -1;
	while(src[++pos] != '\0') {
		new[newpos] = src[pos];
		newpos++;
	}
	new[newpos] = '\0';
	return new;
}

/**
 * Returns 1 when 'ch' is a whitespace character, and 0 otherwise.
 *
 * By default, white-space characters are: space ' ', form-feed '\f', 
 * newline '\n', carriage return '\r', horizontal tab '\t' and vertical tab '\v'
 *
 * See the README FAQ for more information.
 *
 * Examples:
 * my_isspace(' '); // 1
 * my_isspace('\f'); // 1
 * my_isspace('\n'); // 1
 * my_isspace('\r'); // 1
 * my_isspace('\t'); // 1
 * my_isspace('\v'); // 1
 * char ch;
 * for(ch = 'A'; ch <= 'Z'; ++ch)
 *    my_isspace(ch); // always 0
 */
int my_isspace(int ch)
{
	int ret = 0;
	if(ch == ' '  || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v')
		ret = 1;
	return ret;
}

/**
 * Convert the initial portion of 'str' to an integer.
 *
 * Implement my_atoi(str) as follows:
 * (1) Increment str to skip all white-space characters as defined by 
 * my_isspace(...)
 * (2) If there is a '-' sign, note that 'str' is a negative number, and 
 * increment str past the minus sign.
 * (3) Initialize a return value "ret" to 0. (int ret = 0)
 * (4) While '0' <= *str <= '9':
 *     (4.a) Multiply ret by 10
 *     (4.b) Add (*str - '0') to ret
 *     (4.c) Increment str
 * (5) If there was a minus sign, return -ret. Otherwise return ret.
 *
 * Examples:
 * my_atoi("0"); // 0
 * my_atoi("-12"); // -12
 * my_atoi("15th of March would be the ides."); // 15
 * my_atoi("4 months to Summer."); // 4
 * my_atoi("\n\f\t\v\r 6 white space characters handled correctly."); // 6
 * my_atoi("garbage should yield 0"); // 0
 */
int my_atoi(const char * str)
{
	int ret = 0;
	int len = 0;
	int iter = 0;
	len = my_strlen(str);
	int pos = 0;
	for(iter = 0;iter <= len;iter++)
	{
		if(my_isspace(str[iter]))
		{
			continue;
		}
		if(str[iter] == '-')
		{
			pos = -1;
		}
		ret = 0;
		while(*str >= '0' && *str <= '9')
		{
			ret *= 10;
			ret += (*str - '0');
			str++;
		}
	}
	if(pos == -1)
		ret = -ret;
	return ret;
}
