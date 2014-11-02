/**
 * Do not modify this file
 */
#ifndef PA08_H
#define PA08_H
#include <string.h>
#include <libgen.h>
 #include <stdio.h>
#include <stdlib.h>
/**
 * A ListNode structure for a linked list of strings.
 */
typedef struct ListNode_st
{
    char * str;
    struct ListNode_st * next;
} List;

/**
 * Create a new list-node with the passed string. 
 * str should be copied (with strdup).
 */
List * List_createNode(const char * str)
{
	List *nd = NULL;
	nd = malloc(sizeof(List));
	nd -> str = strdup(str);
	nd -> next = NULL;
	return nd;
}

/**
 * Free all memory associated with the linked list, including memory for
 * contained strings. Must safely handle NULL lists.
 */
void List_destroy(List * list)
{
	while(list != NULL){
		List *p = list -> next;
		free(list -> str);
		free(list);
		list = p;
	}
}
/**
 * Length of a linked list. 
 * The length of "NULL" is 0.
 */
int List_length(List * list)
{
	int len = 0;
	while(list != NULL){
		list = list -> next;
		len++;
	}
	return len;
}

/**
 * Merge two sorted lists to produce a final sorted list.
 * 
 * 'lhs' and 'rhs' are two sorted linked-list. Read 'left-hand-side' and 'right-
 * hand-side'. Note that either (or both) could be NULL, signifying the empty
 * list.
 * 'compar' is a function that is used to compare two nodes. This parameter is
 * similar to the parameter in qsort(...), except that it only compares two
 * strings. You can pass 'strcmp' to this function if you want to sort lists in
 * ascending order.
 *
 * When implementing this function, do not call List_createNode(...) or
 * malloc(...) Instead, think about how to build a new list by:
 * (1) Create a new (empty -- i.e., NULL) list where we build the result. You 
 *     will need to track the first and last node of this list.
 * (2) In a while-loop:
 * (2.a) Use compar to identify whether the front node of lhs or rhs is smaller.
 *       Remember that lhs or rhs could be NULL. 
 * (2.b) Move the front node of 'lhs/rhs' to the end of the result list. 
 *
 * You will need to consider what happens when 'lhs' or 'rhs' becomes NULL.
 *
 * Well-written code should be 20-30 lines long, including comments and spacing.
 * If your code is longer than this, then you may save time by rethinking your
 * approach.
 */
List * List_merge(List * lhs, 
		  List * rhs, 
		  int (*compar)(const char *, const char*))
{
	int comp = 0;
	List *final_rhs = NULL;
	List *final_lhs = NULL;
	if(lhs != NULL || rhs != NULL){
		comp = compar(lhs -> str, rhs -> str);
		if(comp < 0){
			final_rhs = lhs;
			final_lhs = lhs;
		}
		else
		{
			final_rhs = rhs;
			final_lhs = rhs;
		}
	}
	while(lhs != NULL && rhs != NULL){
		comp = compar(lhs -> str, rhs -> str);
		if(comp < 0){
			final_rhs -> next = lhs;
			lhs = lhs -> next;
			final_rhs = final_rhs -> next;
			final_rhs -> next = NULL;
		}
		else{
			final_rhs -> next = rhs;
			rhs = rhs -> next;
			final_rhs = final_rhs -> next;
			final_rhs -> next = NULL;
		}
	}
	if(lhs != NULL){
		final_rhs -> next = lhs;
	}
	if(rhs != NULL){
		final_rhs -> next = rhs;
	}
	return final_lhs;
}

/** 
 * Sorts the list's elements using the merge-sort algorithm.
 * Merge-sort is a recursive algorithm. See the README for hints.
 * 
 * The brief instructions are as follows:
 *
 * (1) Base case: 
 * Lists of length 0 or 1 are already (defacto) sorted. In this case, return
 * 'list'.
 *
 * (2) Recursive case: 
 * (2.a) Split the linked-list into two approx. equal sized lists.
 * (2.b) Call List_sort(...) on each of these smaller lists.
 * (2.c) Call List_merge(...) to merge the now sorted smaller lists into a 
 *       single larger sorted list, which you return.
 *
 * Well-written code should be 20-30 lines long, including comments and spacing.
 * If your code is longer than this, then you may save time by rethinking your
 * approach.
 */
List * List_sort(List * list, int (*compar)(const char *, const char*))
{
	List *rhs;
	List *lhs = list;
	int mov = 0;
	int len = List_length(list);
	if(len == 0 || len == 1){
		return list;
	}
	while(mov < len/2){
		//rhs = list;
		list = list -> next;
		mov++;
	}
	list->next = NULL;
	rhs = list;
	//list = list -> next;
	List_sort(lhs,compar);
	List_sort(rhs,compar);
	List_merge(lhs,rhs,compar);
}

#endif

