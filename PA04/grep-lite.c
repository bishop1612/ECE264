#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	/*if(argc < 2)
	{
		print()
	}*/
	int i = 0;
	int q = 0;
	int v = 0;
	int n = 0;
	for(i = 1; i < argc;i++)
	{
		if(strcmp(argv[i],"--help") == 0)
		{
			printf("Usage: grep-lite [OPTION]... PATTERN\n");
			printf("Search for PATTERN in standard input. PATTERN is a\n");
			printf("string. grep-lite will search standard input line by\n");
			printf("line, and (by default) print out those lines which\n");
			printf("contain pattern as a substring.\n\n");
			printf(" -v, --invert-match     print non-matching lines\n");
			printf(" -n, --line-number      print line numbers with output\n");
			printf(" -q, --quiet            suppress all output\n\n");
			printf("Exit status is 0 if any line is selected, 1 otherwise;\n");
			printf("if any error occurs, then the exit status is 2.\n");
			return EXIT_SUCCESS;
		}		
	}
	for(i = 1; i < argc - 1;i++)
	{
		if(strcmp(argv[i],"-v") == 0 || strcmp(argv[i],"--invert-match") == 0)
		{
			v = 1;
		
		}
		if(strcmp(argv[i],"-n") == 0 || strcmp(argv[i],"--line-number") == 0)
		{
			n = 1;
		}
		if(strcmp(argv[i],"-q") == 0 || strcmp(argv[i],"--quiet") == 0 )
		{
			q = 1;
		}
		if(n != 1 && q != 1 && v != 1)
		{
			fprintf(stderr,"%s is an unrecognised argument\n",argv[i]);
			return 2;
		}

	}
	if(argv[argc-1][0] == '-')
	{
		fprintf(stderr,"%s is an unrecognised pattern\n",argv[argc-1]);
		return 2;
	}
	

	FILE *fptr = stdin;
	int line = 0;
	int match = 1;
	char buffer[2000];
	while(fgets(buffer,2000,stdin) != NULL)
	{
		//char matchstr[2000];
		//fgets(buffer,2000,stdin);
		line++;
		//char ch = fgetc(fptr);
		//matchstr = strstr(buffer,argv[argc-1]);
		if(strstr(buffer,argv[argc-1]) != NULL)
		{
			match = 0;
		}
		if(q == 1)
		{
			continue;
		}
		if(v == 1)
		{
			if(strstr(buffer,argv[argc-1]) == NULL)
			{
				if(n == 1)
				{
					fprintf(stdout,"%d:",line);
				}
				fprintf(stdout,"%s",buffer);
			}
			else
			{
				match = 0;
			}
		}
		else
		{
			if(strstr(buffer,argv[argc-1]) != NULL)
			{
				if(n == 1)
				{
					fprintf(stdout,"%d:",line);
				}
				fprintf(stdout,"%s",buffer);
				match = 0;
			}

		}
		//if(ch == EOF)
		//{
			//break;
		//}
	}
	fclose(fptr);
	return match;
}