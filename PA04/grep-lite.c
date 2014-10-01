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
		if((strcmp(argv[i],"-n") != 0 ) && (strcmp(argv[i],"-q") != 0) && (strcmp(argv[i],"-v") != 0) )
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
	while(!feof(fptr))
	{
		char buffer[2000];
		fgets(buffer,2000,fptr);
		line++;
		if(argc > 2)
		{
			for(i = 1; i < argc - 1; i++)
			{
				if(strcmp(argv[i],"-v") == 0)
				{
					if((strstr(buffer,argv[argc-1]) == NULL)) 
					{
						if(buffer != NULL){
							fprintf(stdout,"%s",buffer);
						}
						else 
						{
							match = 0;
						}
					}	

				}
				if(strcmp(argv[i],"-n") == 0)
				{
					if((strstr(buffer,argv[argc-1]) != NULL)) 
					{
						if(buffer != NULL){
							fprintf(stdout,"%d:",line);
							fprintf(stdout,"%s",buffer);
							match = 0;
						}
					}	

				}
				if(strcmp(argv[i],"-q") == 0)
				{
					return match;
				}
			}	
		}
		else
		{
			if((strstr(buffer,argv[argc-1]) != NULL)) 
			{
				if(buffer != NULL){
					fprintf(stdout,"%s",buffer);
					match = 0;
				}
			}
		}
	}
	fclose(fptr);


	/*if(argc < 2)
	{
		FILE *fptr = stdin;
		while(!feof(fptr))
		{
			char ch = fgetc(fptr);
			if(ch != EOF)
			{
				printf("%c", ch);
			}
		}
		fclose(fptr);
	}
	
	for(i = 1; i < argc;i++)
	{
		if(strcmp(argv[i],"-") == 0)
		{
			FILE *fptr = stdin;
			while(!feof(fptr))
			{
				char ch = fgetc(fptr);
				if(ch != EOF)
				{
					printf("%c", ch);
				}
			}
			fclose(fptr);
			
		}
		else
		{
			//printf("Hello");
			FILE *fptr;
			//FILE *fout = stdout;
			fptr =fopen(argv[i],"r");
			//printf("%p",fptr);
			if(fptr == NULL)
			{
				//printf("Hello");
				fprintf(stderr,"cat cannot open %s\n",argv[i]);
				return EXIT_FAILURE;
			}
			while(!feof(fptr))
			{
				char ch = fgetc(fptr);
		        
				if(ch != EOF)
				{	
					//fputc(ch,fout);
					fprintf(stdout,"%c",ch);
				}
				//printf(fout,"");
			}
			fclose(fptr);

		}
		
		//printf("%s", argv[i]);
		//printf(" ");
	}
	//printf("\n");*/
	return match;
}