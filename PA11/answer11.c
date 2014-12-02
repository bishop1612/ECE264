#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include"answer11.h" 

HuffNode * HuffNode_create(int value) 
{ 
	HuffNode* hn = malloc(sizeof(HuffNode)); 
	hn -> value = value; 
	hn -> left = NULL; 
	hn -> right = NULL; 
	return(hn); 
} 

void HuffNode_destroy(HuffNode* tree) 
{ 
	if(tree == NULL) { 
		return; 
	} 
	HuffNode* left = tree -> left; 
	HuffNode* right = tree -> right; 
	HuffNode_destroy(left); 
	HuffNode_destroy(right); 
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
		free(stack); 
		return; 
	} 

	StackNode* temp = stack -> head; 
	while(temp != NULL) { 
		StackNode* nxt = temp -> next; 
		HuffNode_destroy(temp -> tree); 
		free(temp); 
		temp = nxt; 
	} 
	free(stack); 
	return; 
} 
HuffNode * Stack_popFront(Stack * stack) 
{ 
	if(Stack_isEmpty(stack)) 
	{ 
		//printf("\n\nERROR! Cannot Pop an Empty Stack\n\n"); 
		return(NULL); 
	} 
	HuffNode* tree = stack -> head -> tree; 
	StackNode* temp = stack -> head -> next; 
	free(stack -> head); 
	stack -> head = temp; 
	return(tree); 
} 
Stack* Stack_push(Stack* stack,HuffNode* tree) 
{ 
	StackNode* tmp = malloc(sizeof(StackNode)); 
	tmp -> tree = tree; 
	// Assigining the tree 
	if(stack == NULL) { 
		stack = Stack_create(); 
	} 
	StackNode* final = stack -> head; 
	// This makes 'temp_main' point to the stack's head. 
	stack -> head = tmp; // Makes the stack's head point to the 'temp' 
	tmp -> next = final; // And point 'temp -> next' to the 'stack -> head'. 
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
	HuffNode* temp = malloc(sizeof(HuffNode)); 
	temp -> value = 0; // Don't Care Not Required. 
	temp -> left = left; // Sending in the last popped node into the left node of the Huffman Tree 
	temp -> right = right; // Sending in the first popped node into the right node of the Huffman Tree 
	Stack_pushFront(stack,temp); // Pushing the Newly made tree. 
}
HuffNode* HuffTree_readTextHeader(FILE* fp) 
{ 
	if(fp == NULL) 
	{ 
		//printf("\nInput File Pointer cannot be NULL\n\n"); 
		return(NULL); 
	} 
	Stack* new = Stack_create(); 
	int check = 0; 
	while(check != 1) { 
		char ch = fgetc(fp); 
		if(ch == '1') 
		{ 
			char val = fgetc(fp); 
			if(!isascii(val)) { 
				printf("\n\n Cannot add ASCII please check the Header of your Compressed File\n\n"); 
				check = 1; 
				break; 
			} 
			HuffNode* hf = HuffNode_create(val); 
			Stack_pushFront(new,hf); 
		} 
		else 
		{ 
			if(new -> head -> next == NULL) // Means the Stack has only one Node 
				{ check = 1; } 
			else 
				{ Stack_popPopCombinePush(new); } } } 
			HuffNode* final = new -> head -> tree; 
			free(new -> head); free(new); 
			return(final); 
}

// This Function is taken from Yung Lu's Book
int readBit(FILE* fptr, unsigned char* bit, unsigned char* bitcount, unsigned char* currentbyte)
{
	int ret = 1;

	if(*bitcount == 0)
	{
		ret = fread(currentbyte, sizeof(unsigned char),1,fptr);
	}


	// If the fread fails
	if(ret != 1)
	{
		return(-1);
	}

	// Shift the Bit to the correct Location
	unsigned char temp = (* currentbyte) >> (7 - (*bitcount));
	temp = temp & 0X01; // Get only 1 bit and ignore the other bits

	*bitcount = ((*bitcount) + 1) % 8;

	*bit = temp;

	return(1);
}

// Idea Taken from the Prof. Lu Book.
HuffNode* HuffTree_readBinaryHeader(FILE* fp)
{
	if(fp == NULL)
	{
		return(NULL);
	}

	Stack* st = Stack_create();

	int status = 1;
	unsigned char bitcount = 0;
	unsigned char currentbyte = 0;
	unsigned char onebit = 0;

	// decreasing to ensure the list is a stack

	while(status == 1)
	{
		readBit(fp,&onebit,&bitcount,&currentbyte);

		if(onebit == 1)
		{ // a leaf node , get 7 move bits

			int count;
			unsigned char val = 0;

			for(count = 0; count < 8; count++)
			{
				val <<= 1; // shift left by one
				readBit(fp,&onebit,&bitcount,&currentbyte);

				val |= onebit;
			} // push a tree node into the list

			HuffNode* hn = HuffNode_create(val);
			Stack_pushFront(st,hn);
		}
		else
		{
			if(st -> head == NULL )
			{
				return NULL;
			}

			if((st -> head -> next) == NULL )
			{

				// the tree has been completely built
				status = 0;
			}
			else
			{
				Stack_popPopCombinePush(st);
			}

		}
	}

	HuffNode* FinalTree = st -> head -> tree;
	free(st -> head);
	free(st);

	return(FinalTree);
}