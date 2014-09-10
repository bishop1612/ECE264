#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "answer02.h"

#define BUFFER_LEN 1024

int main(int argc, char * * argv)
{
    printf("Welcome to PA02.\n"
	   "\n"
	   "You are encouraged to edit this file in order to test\n"
	   "the behavior of the functions you write in answer02.c\n"
	   "\n"
	   "This file will not be marked, and should not be\n"
	   "submitted.\n"
	   "\n"
	   "Don't forget to post questions on blackboard, and ask\n"
	   "the TAs and your classmates for help.\n"
	   "\n");

    const char * s1 = "Hello World!";
    const char * s2 = "";
    const char * s3 = "foo";

    // -- my_strlen, should be: 12, 0, and 3
    printf("my_strlen(\"%s\") = %d\n", s1, (int) my_strlen(s1));
    printf("my_strlen(\"%s\") = %d\n", s2, (int) my_strlen(s2));
    printf("my_strlen(\"%s\") = %d\n", s3, (int) my_strlen(s3));

    // -- my_countchar, should be: 3, 0, and 2
    printf("my_countchar(\"%s\", 'l') = %d\n", s1, (int) my_countchar(s1, 'l'));
    printf("my_countchar(\"%s\", 'o') = %d\n", s2, (int) my_countchar(s2, 'o'));
    printf("my_countchar(\"%s\", 'o') = %d\n", s3, (int) my_countchar(s3, 'o'));

    // -- my_strchr, should be: "llo World!", "(null)", and ""
    //printf("my_strchr(\"%s\", '\\0') = %s\n", s1,  (my_strrchr(s1, '\\0')));
    printf("my_strchr(\"%s\", 'o') = %s\n", s2, my_strchr(s2, 'o'));
    printf("my_strchr(\"%s\", '\\0') = %s\n", s3, my_strchr(s3, '\0'));

    printf("my_strrchr(\"%s\", 'l') = %s\n", s1, my_strrchr(s1, 'l'));
    printf("my_strrchr(\"%s\", 'o') = %s\n", s2, my_strrchr(s2, 'o'));
    printf("my_strrchr(\"%s\", '\\0') = %s\n", s3, my_strrchr(s3, '\0'));

    // -- my_strstr, should be: "World!", "Hello World!", "(null)"
    printf("my_strstr(\"%s\", \"World\") = %s\n", s1, my_strstr(s1, "World"));
    printf("my_strstr(\"%s\", \"\") = %s\n", s1, my_strstr(s1, ""));
    printf("my_strstr(\"%s\", \"hello\") = %s\n", s1, my_strstr(s1, "hello"));

    // -- my_strcpy. For this function you need a buffer where you
    // copy the string to. 
    char buffer[BUFFER_LEN];
    my_strcpy(buffer, s1);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s1, buffer);
    my_strcpy(buffer, s2);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s2, buffer);
    my_strcpy(buffer, s3);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s3, buffer);

    // -- my_strcat. You will have to do this yourself... just
    char buffer2[50];
    my_strcpy(buffer2, "Hello ");
    my_strcpy(buffer2, "Hey ");
    printf("%s\n", my_strcat(buffer2, "Baby!")); // prints "Hello Zippy!"
    // -- my_isspace. You will have to do this for yourself.
    printf("\n%d", my_isspace(' '));
    printf("\n%d", my_isspace('\f'));
    printf("\n%d", my_isspace('\n'));
    printf("\n%d", my_isspace('\r'));
    printf("\n%d", my_isspace('\t'));
    printf("\n%d", my_isspace('A'));
    // -- my_atoi. You will have to do this for yourself.
    //printf("%d",my_atoi("0")); // 0
    printf("\nmyatoi1 : %d",my_atoi("-9")); // -12
    printf("\nmyatoi1 : %d",my_atoi("15th of March would be the ides.")); // 15
    printf("\nmyatoi1 : %d",my_atoi("4 months to Summer.")); // 4
    printf("\nmyatoi1 : %d",my_atoi("\n\f\t\v\r 6 white space characters handled correctly.")); // 6
    printf("\nmyatoi1 : %d",my_atoi("garbage should yield 0"));
    return EXIT_SUCCESS;
}


