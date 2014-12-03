#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include"answer11.h" 

// -------------------------------------------------------------------- HuffNode

/**
 * A Huffman coding tree. We must implement two small functions... 
 *
 * (1) HuffNode_create(value);         // create a new HuffNode
 * (2) HuffNode_destroy(tree);         // free all memory safely
 */

 /**
 * Create a new, properly intialized HuffNode
 */

HuffNode * HuffNode_create(int value) 
{ 
	HuffNode* hn = malloc(sizeof(HuffNode)); 
	hn -> value = value; 
	hn -> left = NULL; 
	hn -> right = NULL; 
	return(hn); 
} 

/**
 * Destroy a tree, including all sub-children. Must handle NULL values safely.
 */

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

// ----------------------------------------------------------------------- Stack

/**
 * We need a "Stack" to build the tree structure that is used to decode
 * a Huffman encoding. Stacks are very simple to implement with linked lists.
 * We must implement the following functions (given below). Each of these 
 * functions should only be a few lines of code.
 *
 * (1) Stack_create();              // Allocate a brand new stack.
 * (2) Stack_destroy(stack);        // Clean up memory for the stack.
 * (3) Stack_isEmpty(stack);    // TRUE iff (if and only if) the stack is empty.
 * (4) Stack_pushFront(stack, tree); // Push a tree onto the stack.
 * (6) Stack_popFront(stack);  // Remove a tree from the stack and return it.
 *
 * Altogether, these six functions should be around 40 lines of code.
 */

 /**
 * Returns a pointer to a new empty stack struct
 */
Stack* Stack_create() 
{ 
	Stack* stack = malloc(sizeof(Stack)); 
	stack -> head = NULL; 
	return(stack); 
} 

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */

int Stack_isEmpty(Stack* stack) 
{ 
	if(stack == NULL) 
	{ 
		return(1); 
	} 
	return(0); 
} 

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you must free the entire contained linked-list.
 * Also, you must safely do nothing if stack == NULL. 
 */

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

/**
 * Pop the front (top) 'value' (i.e. Huffman tree) from the stack.
 *
 * More precisely, this function must do three things:
 * (1) Save the value (i.e. Huffman tree) of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 * (3) Return the value (i.e. Huffman tree) saved in (1).
 */
HuffNode * Stack_popFront(Stack * stack) 
{ 
	if(Stack_isEmpty(stack)) 
	{ 
		//printf("\n\nERROR! Cannot Pop an Empty Stack\n\n"); 
		return(NULL); 
	} 
	HuffNode* tree = stack -> head -> tree; 
	StackNode* temp = stack -> head -> next; 
	free(stack
	 -> head); 
	stack -> head = temp; 
	return(tree); 
} 

/**
 * Push a 'value' (i.e. Huffman tree) onto the front (top) of the stack.
 *
 * More precisely, this function must do two things:
 * (1) Create a new StackNode with 'tree' for its tree.
 * (2) Push that new StackNode onto the front of the stack's list.
 */

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

// -------------------------------------------------------- Pop Pop combine Push

/**
 * This function helps simplify building a Huffman Coding Tree from the header
 * information. It takes a stack as input. As a precondition, you can assume 
 * that the stack has at least two nodes. This function pops the front (top) 
 * two nodes, combines them into a single node, and pushes the new node back 
 * onto the stack. See Huffman_Coding.pdf to understand conceptually how this
 * should be done.
 */
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

// ---------------------------------------------------- Reading HuffTree headers

/**
 * Read a Huffman Coding Tree (in text format) from 'fp'.
 */
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

/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */

// This Function is taken from Yung Lu's Book
int readBit(FILE* fptr, unsigned char* bit, unsigned char* bitcount, unsigned char* currentbyte)
{
	int rem = 1;

	if(*bitcount == 0)
	{
		rem = fread(currentbyte, sizeof(unsigned char),1,fptr);
	}


	// If the fread fails
	if(rem != 1)
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
		{ 
			// a leaf node , get 7 move bits

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