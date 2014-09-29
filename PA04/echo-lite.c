#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	/*if(argc < 2)
	{
		print()
	}*/
	int i = 0; 
	for(i = 1; i < argc;i++)
	{
		printf("%s", argv[i]);
		printf(" ");
	}
	printf("\n");
	return EXIT_SUCCESS;
}