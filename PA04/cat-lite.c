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
			printf("Usage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\n\nExamples:\n");
			printf(" cat-lite README   Print the file README to standard output.\n");
			printf(" cat-lite f - g    Print f's contents, then standard input,\n");
			printf("                   then g's contents.\n");
			printf(" cat-lite          Copy standard input to standard output.\n");
			return EXIT_SUCCESS;
		}
		
		//printf("%s", argv[i]);
		//printf(" ");
	}
	if(argc < 2)
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
	//printf("\n");
	return EXIT_SUCCESS;
}