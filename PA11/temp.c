#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include"answer11.h" 

HuffNode * HuffNode_create(int value) 
{ 
	HuffNode* HNode = malloc(sizeof(HuffNode)); 
	HNode -> value = value; 
	HNode -> left = NULL; 
	HNode -> right = NULL; 
	return(HNode); 
} 

void HuffNode_destroy(HuffNode* tree) 
{ 
	if(tree == NULL) { 
		return; 
	} 
	HuffNode* LHF = tree -> left; 
	HuffNode* RHF = tree -> right; 
	HuffNode_destroy(LHF); 
	HuffNode_destroy(RHF); 
	free(tree); 
}

Stack* Stack_create() 
{ 
	Stack* stack = malloc(sizeof(Stack)); 
	stack -> head = NULL; 
	return(stack); 
} 

int Stack_isEmpty(Stack* stack) 
{ 
	if(stack == NULL) 
	{ 
		return(1); 
	} 
	return(0); 
} 

void Stack_destroy(Stack* stack) 
{ 
	if(Stack_isEmpty(stack)) 
	{ 
		return; 
	} 
	if(stack -> head == NULL) { 
		free(stack); return; 
	} 
	StackNode* Head = stack -> head; 
	while(Head != NULL) { 
		StackNode* SNode = Head -> next; 
		HuffNode_destroy(Head -> tree); 
		free(Head); 
		Head = SNode; 
	} 
	free(stack); 
	return; 
} 
HuffNode * Stack_popFront(Stack * stack) 
{ 
	if(stack == NULL) 
	{ 
		printf("\n\nERROR! Cannot Pop an Empty Stack\n\n"); 
		return(NULL); 
	} 
	HuffNode* Tree = stack -> head -> tree; 
	StackNode* temp = stack -> head -> next; 
	free(stack -> head); 
	stack -> head = temp; 
	return(Tree); 
} 
Stack* Stack_push(Stack* stack,HuffNode* tree) 
{ 
	StackNode* temp = malloc(sizeof(StackNode)); 
	temp -> tree = tree; 
	// Assigining the tree 
	if(stack == NULL) { 
		stack = Stack_create(); 
	} 
	StackNode* temp_main = stack -> head; 
	// This makes 'temp_main' point to the stack's head. 
	stack -> head = temp; // Makes the stack's head point to the 'temp' 
	temp -> next = temp_main; // And point 'temp -> next' to the 'stack -> head'. 
	return(stack); 
} 
void Stack_pushFront(Stack* stack,HuffNode* tree) 
{ 
	stack = Stack_push(stack,tree); 
} 
void Stack_popPopCombinePush(Stack * stack) 
{ 
	HuffNode* right = Stack_popFront(stack); 
	HuffNode* left = Stack_popFront(stack); 
	HuffNode* new = malloc(sizeof(HuffNode)); 
	new -> value = 0; // Don't Care Not Required. 
	new -> left = left; // Sending in the last popped node into the left node of the Huffman Tree 
	new -> right = right; // Sending in the first popped node into the right node of the Huffman Tree 
	Stack_pushFront(stack,new); // Pushing the Newly made tree. 
}
HuffNode* HuffTree_readTextHeader(FILE* fp) 
{ 
	if(fp == NULL) 
	{ 
		printf("\nInput File Pointer cannot be NULL\n\n"); 
		return(NULL); 
	} 
	Stack* st = Stack_create(); 
	int flag = 0; 
	while(flag != 1) { 
		char ch = fgetc(fp); 
		if(ch == '1') 
		{ 
			char val = fgetc(fp); 
			if(!isascii(val)) { 
				printf("\n\n Cannot add ASCII please check the Header of your Compressed File\n\n"); 
				flag = 1; 
				break; 
			} 
			HuffNode* HFN = HuffNode_create(val); 
			Stack_pushFront(st,HFN); 
		} 
		else 
		{ 
			if(st -> head -> next == NULL) // Means the Stack has only one Node 
				{ flag = 1; } 
			else 
				{ Stack_popPopCombinePush(st); } } } 
			HuffNode* FinalTree = st -> head -> tree; 
			free(st -> head); free(st); 
			return(FinalTree); 
}
int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte)
{
	int ret = 1;
	if(*whichbit == 0)
	{
		fread(curbyte,sizeof(unsigned char),1,fptr);
	}
	if ( ret != 1)
	{
		// read fail
		return -1;
	}
	// shift the bit to the correct location
	unsigned char temp = (* curbyte ) >> (6 - (* whichbit ) ) ;
	temp = temp & 0X01 ; // get only 1 bit , ignore the other bits
// increase by 1
	* whichbit = ((* whichbit ) + 1) % 7;
	* bit = temp ;
	return 1;
}


/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	if(fp == NULL) 
	{ 
		//printf("\nInput File Pointer cannot be NULL\n\n"); 
		return(NULL); 
	} 
	Stack* stack = Stack_create(); 
	int done = 0;
	unsigned char whichbit = 0;
	unsigned char curbyte = 0;
	unsigned char onebit = 0;
	//ListNode * head = NULL ;
	// decreasing to ensure the list is a stack
	while ( done == 0)
	{
		readBit ( fp , & onebit , & whichbit , & curbyte ) ;
		if ( onebit == 1)
		{
			// a leaf node , get 7 move bits
			int bitcount ;
			unsigned char value = 0;
			for ( bitcount = 0; bitcount < 6; bitcount ++)
			{
				value <<= 1; // shift left by one
				readBit ( fp , & onebit , & whichbit , &curbyte ) ;
				value |= onebit ;
			}
		// push a tree node into the list
		HuffNode* hn = HuffNode_create(value); 
		Stack_pushFront(stack,hn); 
		}
		else
		{
			if ( stack -> head  == NULL )
			{
				return NULL;
			}
			if (( stack -> head -> next ) == NULL )
			{
				// the tree has been completely built
				done = 1;
			}
			else
			{
				Stack_popPopCombinePush(stack);
			}
		}
	}
	HuffNode* final = stack -> head -> tree; 
	free(stack -> head); 
	free(stack); 
	return(final);
}



int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte)
{
	int ret = 1;
	if(*whichbit == 0)
	{
		fread(curbyte,sizeof(unsigned char),1,fptr);
	}
	if ( ret != 1)
	{
		// read fail
		return -1;
	}
	// shift the bit to the correct location
	unsigned char temp = (* curbyte ) >> (6 - (* whichbit ) ) ;
	temp = temp & 0X01 ; // get only 1 bit , ignore the other bits
// increase by 1
	* whichbit = ((* whichbit ) + 1) % 7;
	* bit = temp ;
	return 1;
}


/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	if(fp == NULL) 
	{ 
		//printf("\nInput File Pointer cannot be NULL\n\n"); 
		return(NULL); 
	} 
	Stack* stack = Stack_create(); 
	int done = 0;
	unsigned char whichbit = 0;
	unsigned char curbyte = 0;
	unsigned char onebit = 0;
	//ListNode * head = NULL ;
	// decreasing to ensure the list is a stack
	while ( done == 0)
	{
		readBit ( fp , & onebit , & whichbit , & curbyte ) ;
		if ( onebit == 1)
		{
			// a leaf node , get 7 move bits
			int bitcount ;
			unsigned char value = 0;
			for ( bitcount = 0; bitcount < 6; bitcount ++)
			{
				value <<= 1; // shift left by one
				readBit ( fp , & onebit , & whichbit , &curbyte ) ;
				value |= onebit ;
			}
		// push a tree node into the list
		HuffNode* hn = HuffNode_create(value); 
		Stack_pushFront(stack,hn); 
		}
		else
		{
			if ( stack -> head  == NULL )
			{
				return NULL;
			}
			if (( stack -> head -> next ) == NULL )
			{
				// the tree has been completely built
				done = 1;
			}
			else
			{
				Stack_popPopCombinePush(stack);
			}
		}
	}
	HuffNode* final = stack -> head -> tree; 
	free(stack -> head); 
	free(stack); 
	return(final);
}


