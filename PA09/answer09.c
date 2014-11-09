#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef PA09_H
#define PA09_H

/* A BusinessNode contains the name, address, and average rating of a Business.
 * It also contains pointers to the left and right children of the node.
 */

typedef struct bnode {
  char * name;
  char * stars;
  char * address;

  struct bnode * left;
  struct bnode * right;
} BusinessNode;

/*
 * Construct one BusinessNode. You need to allocate memory for this node first.
 *
 * The caller needs to make sure to use strdup(...) for the arguments, do not
 * use strdup(...) inside of this function.
 *
 * stars: the stars of this business
 * name: name of this business
 * address: address of this business
 */
BusinessNode *create_node(char * stars, char * name, char * address){
	BusinessNode *node;
	node = malloc(sizeof(BusinessNode));
	node -> name = name;
	node -> stars = stars;
	node -> address = address;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}


/* Insert a node into a BST. Primarily used in load_tree_from_file(). Return a
 * pointer to the root of the BST.
 */
BusinessNode *
tree_insert(BusinessNode * node, BusinessNode * root){
	if(root == NULL){
		return node;
	}
	int comp = strcmp(node -> name, root -> name);
	if(comp <= 0){
		root -> left = tree_insert(node,root->left);
	}
	else
	{
		root -> right = tree_insert(node,root->right);	
	}
	return root;

}
/*
 * Function to explode strings
 */
char * * explode(const char * str, const char * delims, int * arrLen)
{
	int N = 0;
	int pos = 0;
	while(str[pos] != '\0')
	{
		if(strchr(delims,str[pos]) != NULL)
		{
			N++;
		}
		pos++;
	}
	char * * strArr = malloc((N+1) * sizeof(char *)); 
	pos = 0;
	int arrInd = 0; // this is the next position where we'll create a string
	int last = 0; // 1 + the last index we saw a delimiter. Init to 0.
	int diff = 0;
	while(str[pos] != '\0')
	{
		if(strchr(delims,str[pos]) != NULL)
		{
			diff = pos - last;
			if(diff != 0){
				strArr[arrInd] = malloc((diff) * sizeof(char *));
				memcpy(strArr[arrInd], &str[last] , (diff)*sizeof(char));
				strArr[arrInd][diff] = '\0';
			}
			else
			{
				strArr[arrInd] = malloc((1) * sizeof(char *));
				strArr[arrInd][diff] = '\0';

			}
			last = pos + 1;
			arrInd++;
		}
		pos++;
	}
	diff = strlen(str) - last;
	if(diff != 0)
	{
		strArr[arrInd] = malloc((diff) * sizeof(char *));
		memcpy(strArr[arrInd], &str[last] , (diff)*sizeof(char));
		strArr[arrInd][diff] = '\0';
	}	
	else
	{
		strArr[arrInd] = malloc((1) * sizeof(char *));
		strArr[arrInd][diff] = '\0';
	}
	
	*arrLen = N+1;
	
	return (char **)strArr;
}

/* Parse a .tsv file line by line, create a BusinessNode for each entry, and
 * enter that node into a new BST. Return a pointer to the root of the BST.
 *
 * The explode(...) function from PA03 may be useful for breaking up a lines 
 * into seperate fields. 
 */
BusinessNode *
load_tree_from_file(char * filename){
	FILE * fptr = NULL;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        return NULL;
    }
    BusinessNode * root = NULL;
    char ** strexplode = NULL;
    char * str = malloc(sizeof(char)*2000);
    int arrLen = 0;
    while(fgets(str, 2000, fptr) != NULL)
	{
		strexplode = explode(str, "\t", &arrLen);
    	if(arrLen == 3)
    	{
        	BusinessNode * node = create_node(strexplode[0], strexplode[1], strexplode[2]);
        	root = tree_insert(node, root);
    	}
    	free(strexplode);
	}
	free(str);
	fclose(fptr);
	return(root);

}

/* Search a BusinessNode BST for the node with the name 'name'. Returns
 * pointer to the node with a match.
 *
 * If there is no match, return NULL.
 */
BusinessNode *
tree_search_name(char * name, BusinessNode * root){
	if(root != NULL){
		int comp = strcmp(name, root -> name);
		if(comp == 0){
			return root;
		}
		else 
			if(comp <= 0){
				root = tree_search_name(name,root->left);
			}
			else{
				root = tree_search_name(name,root->right);
			}
		return root;
	}
	return NULL;
}

/* Print out a single node: name, address, and stars
 * The format can be similar to this:
 *
 * Country Cafe
 * ============
 * Stars:
 *    3.5
 * Address:
 *    1030 Emerald Ter, Sun Prairie, WI 53590
 *
 * This function is not graded, but it could come in very handful while
 * debugging this assignment.
 */
void
print_node(BusinessNode * node);

/* Print the entire tree, starting from the root. Like the print_node(...)
 * function, this is not graded.
 */
void
print_tree(BusinessNode * tree);

/* Deallocate all of the memory used by a BusinessNode BST, without memory
 * leaks.
 */
void
destroy_tree(BusinessNode * root){
	if(root != NULL)
	{
		destroy_tree(root -> left);
		destroy_tree(root -> right);
		free(root -> stars);
		free(root -> address);
		free(root -> name);
		free(root);
	}
}

#endif
