/**
 * Do not modify this file.
 */
#ifndef PA07_H
#define PA07_H

#include <stdint.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#define ECE264_IMAGE_MAGIC_NUMBER 0x21343632

// Tell gcc not to pad structs with extra bytes.
// Padding is sometimes included for performance reasons.
#pragma pack(1)

typedef struct ImageHeader_st {
    uint32_t magic_number; // Should be ECE264_IMAGE_MAGIC_NUMBER
    uint32_t width;        // [width x height], cannot be zero
    uint32_t height;
    uint32_t comment_len;  // A comment embedded in the file
} ImageHeader;

typedef struct Image_st {
    int width;
    int height;
    char * comment;
    uint8_t * data;
} Image;

/**
 * Loads a bmp (windows bitmap) image, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Note: This function is written for you and appears in image-bmp.c
 */
//Image * Image_loadbmp(const char * filename);

/**
 * Saves an Image structure to a file. Returns TRUE if success, or
 * FALSE if there is any error.
 *
 * Note: This function is written for you and appears in image-bmp.c
 */
//int Image_savebmp(const char * filename, Image * image);

/* Code to cleanup all pointers and free the memory if the image file is not valid*/

Image * cleanUp(FILE *fptr, Image * image)
{
	if(fptr != NULL){
		fclose(fptr);
	}
	if(image != NULL){
		if(image -> comment != NULL){
			free(image -> comment);
		}
		if(image -> data != NULL){
			free(image -> data);
		}
		free(image);
	}
	return NULL;
}

/*Code to check the validity of the headers */

int checkheader(ImageHeader * header){
	if((header -> magic_number) != ECE264_IMAGE_MAGIC_NUMBER){
		return 0;
	}
	if((header -> height) == 0){
		return 0;
	}
	if((header -> width) == 0){
		return 0;
	}
	if(((header -> comment_len) - 1) == 0){
		return 0;
	}
	return 1;

}
/**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */

Image * Image_load(const char * filename)
{
	FILE * fptr = NULL;
	Image *image = NULL;
	ImageHeader header;
	
	//Code to check validity of file 
	fptr = fopen(filename, "rb");
	if(fptr == NULL){
		return cleanUp(fptr,image);
	}
	
	//Code to check the validity of the header
	if(fread(&(header),sizeof(ImageHeader),1,fptr) != 1)
	{
		return cleanUp(fptr,image);
	}
	
	if(checkheader(&header) == 0){
		return cleanUp(fptr,image);
	}

	//Code to check the validity of the image 
	image = malloc(sizeof(Image));
	if(image == NULL){
		return cleanUp(fptr,image);
	}
	
	image -> height = header.height;
	image -> width = header.width;
	image -> comment = NULL;
	image -> data = NULL;
	image -> comment = malloc(sizeof(char) * header.comment_len);
	//checking the comments
	if(image -> comment == NULL){
		return cleanUp(fptr,image);
	}
	if(fread((image -> comment), sizeof(char),header.comment_len,fptr) != (header.comment_len)){
		return cleanUp(fptr,image);
	}
	if(image -> comment[header.comment_len - 1] != '\0'){
		return cleanUp(fptr,image);
	}
	image -> data = malloc(sizeof(uint8_t) * header.width * header.height);
	
	if(image -> data == NULL){
		return cleanUp(fptr,image);
	}
	int nbytes = sizeof(uint8_t) * header.width * header.height;

	if(fread(image -> data, sizeof(uint8_t), nbytes, fptr) != (nbytes)){
		return cleanUp(fptr,image);
	}

	//Checking if we reached the end of the file
	uint8_t byte;
	if(fread((&byte),sizeof(uint8_t),1,fptr) != 0)
	{
		return cleanUp(fptr,image);
	}

	fclose(fptr);
	return image;

	//header = malloc
}
/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image)
{
	FILE * fptr = NULL ;
	fptr = fopen ( filename , "w") ;
	ImageHeader header;
	header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
	header.width = image -> width;
	header.height = image -> height;
	header.comment_len = strlen(image -> comment) + 1;
	if ( fptr == NULL )
	{
		return 0;
	}
	//Writing the header
	if(fwrite(&header,sizeof(ImageHeader),1,fptr) != 1)
	{
		fclose(fptr);
		return 0;
	}

	//Writing the comment
	if(fwrite(image -> comment, sizeof(char), header.comment_len, fptr) != (header.comment_len)){
		fclose(fptr);
		return 0;
	}

	//Writing the image pixels
	int nbytes = image -> width * image -> height;

	if(fwrite(image -> data, sizeof(uint8_t), nbytes, fptr) != (nbytes)){
		fclose(fptr);
		return 0;
	}

	fclose(fptr);
	return 1;
	// write the header first
}

/**
 * Free memory for an image structure
 *
 * Image_load(...) (above) allocates memory for an image structure. 
 * This function must clean up any allocated resources. If image is 
 * NULL, then it does nothing. (There should be no error message.) If 
 * you do not write this function correctly, then valgrind will 
 * report an error. 
 */
void Image_free(Image * image)
{
	//Freeing everything
	free(image ->  comment);
	free(image ->  data);
	free(image);
}

/**
 * Performs linear normalization, see README
 */
void linearNormalization(int width, int height, uint8_t * intensity)
{
	int max, min;
	int iter = 0;
	max = intensity[0];
	min = intensity[0];

	//CHecking linearization
	
	for(iter = 0; iter < width * height; iter++){
		if(intensity[iter] > max){
			max = intensity[iter];
		}
		if(intensity[iter] < min){
			min = intensity[iter];
		}
	}
	for(iter = 0; iter < width * height; iter++){
		 intensity[iter] = (intensity[iter] - min) * 255.0 / (max - min);
	}
}

#endif

