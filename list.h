#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**
* Generic Linked List Library
* @file list.h 
*/

/**
* Node struct holding a void pointer and a pointer to the next node
*/
typedef struct node
{
	void *value; 
	struct node *next;
} Node;

/**
* Compare functions indicate if one data is less than another
* @param void pointer to the first data
* @param void pointer to the second data
* @return boolean value if the first data is less than the second data
*/
bool compare_int(void *data1, void *data2)
{
	return *(int*)data1 <= *(int*)data2;
}

bool compare_long(void *data1, void *data2)
{
	return *(long*)data1 <= *(long*)data2;
}

bool compare_char(void *data1, void *data2)
{
	return *(char*)data1 <= *(char*)data2;
}

bool compare_string(void *data1, void *data2)
{
	return strcmp((char*)data1, (char*)data2) <= 0;
}

bool compare_float(void *data1, void *data2)
{
	return *(float*)data1 <= *(float*)data2;
}

bool compare_double(void *data1, void *data2)
{
	return *(double*)data1 <= *(double*)data2;
}

/**
* Compare function indicate if one data is equal to another
* @param void pointer to the first data
* @param void pointer to the second data
* @return boolean value if the first data is equal the second data
*/
bool compare_eq_int(void *data1, void *data2)
{
	return *(int*)data1 == *(int*)data2;
}

bool compare_eq_long(void *data1, void *data2)
{
	return *(long*)data1 == *(long*)data2;
}

bool compare_eq_char(void *data1, void *data2)
{
	return *(char*)data1 == *(char*)data2;
}

bool compare_eq_string(void *data1, void *data2)
{
	return strcmp((char*)data1, (char*)data2) == 0;
}

bool compare_eq_float(void *data1, void *data2)
{
	return *(float*)data1 == *(float*)data2;
}

bool compare_eq_double(void *data1, void *data2)
{
	return *(double*)data1 == *(double*)data2;
}

/**
* Add functions casting void pointers and add their value together
* @param void pointer to the first data
* @param void pointer to the second data
* add_char function will store two character input as char* and pointer casted pointer of first value to it
* add_string function will store two combine string and point pointer of the first data to that string
*/
void add_int(void *data1, void *data2)
{
	*(int*)data1 += *(int*)data2;
}

void add_long(void *data1, void *data2)
{
	*(long*)data1 += *(long*)data2;
}

void add_char(void *data1, void *data2)
{
	char c1 = *(char*)data1;
	char c2 = *(char*)data2;
	
	char *c = malloc(sizeof(char) * 3);
	if (c == NULL)
	{
		fprintf(stderr, "Memory allocation failed in add_char\n");
		exit(EXIT_FAILURE);
	}
	c[0] = c1;
	c[1] = c2;
	c[2] = '\0';

	*(char**)data1 = c;
}

void add_string(void *data1, void *data2)
{
	char *str1 = (char*)data1;
	char *str2 = (char*)data2;

	int newsize= strlen(str1) + strlen(str2) + 1;
	
	str1 = realloc(str1, newsize);
	if (str1 == NULL)
	{
		fprintf(stderr, "Memory allocation failed in add_string\n");
		exit(EXIT_FAILURE);
	}
	strcat(str1, str2);
	*(char**)data1 = str1;
}

void add_float(void *data1, void *data2)
{
	*(float*)data1 += *(float*)data2;
}

void add_double(void *data1, void *data2)
{
	*(double*)data1 += *(double*)data2;
}

/**
* Print functions will cast void pointer and print its value
* These functions are used in print_list function
*/
void print_int(void *data)
{
	printf("Value: %d\n", *(int*)data);	
}

void print_long(void *data)
{
	printf("Value: %ld\n", *(long*)data);	
}

void print_char(void *data)
{
	printf("Value: %c\n", *(char*)data);	
}

void print_string(void *data)
{
	printf("Value: %s\n", (char*)data);	
}

void print_float(void *data)
{
	printf("Value: %f\n", *(float*)data);	
}

void print_double(void *data)
{
	printf("Value: %f\n", *(double*)data);	
}
/**
* print_list function will print the value of every node in the list
* @param pointer to the head of the list
* @param print functions for casting void pointer
*/
void print_list(Node *head, void (*print_data)(void *data))
{
	Node *current;
	current = head;
    int i = 0;
	while (current != NULL)
	{
		printf("Node: %d ", i);
		print_data(current->value);
		printf("\n");
		i++;
		current = current->next;
	}
}

/**
* list_empty fucntion will check if the list is empty
* @param pointer to the head of the list
* @return boolean value if the list is empty or not
*/
bool list_empty(Node *head)
{
	if(head == NULL) return true;
	else return false;
}

/**
* insert_front function will insert new node at the fron of the list
* @param pointer to the head of the list
* @param pointer to the new node's value
* @param memory size of new node's value
* @return pointer to the new head of the list
*/
Node *insert_front(Node *head, void *value, size_t value_size)
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->value = malloc(value_size);
	memcpy(new_node->value, value, value_size);
	new_node->next = head;
	return new_node;
}

/**
* insert_back function will add new node at the end of the list
* @param pointer to the head of the list
* @param pointer to new node's value
* @param memory size of new node's value
* @return pointer to the head of the list
*/
Node *insert_back(Node *head, void *value, size_t value_size)
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->value = malloc(value_size);
	new_node->next = NULL;
	memcpy(new_node->value, value, value_size);
	if (head != NULL)
	{
		Node *current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
		return head;
	}
	return new_node;
}

/**
* delete_front will delete the head node and set the second node as new head
* @param pointer to the head node of the list
* @return pointer to the new head (second node) of the the list
*/
Node *delete_front(Node *head)
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return NULL;
	
	Node *new_head = head;
	new_head = head->next;
	free(head->value);
	free(head);
	return new_head;
}

/**
* delete_back will delete tail node and set the new tail node pointing to NULL
* @param pointer to the head of the list
* @return pointer to node at the head of the list with new tail node
*/
Node *delete_back(Node *head)
{
	if (head == NULL) return NULL;
	if (head->next == NULL)
	{
		free(head->value);
		free(head);
		return NULL;
	}

	Node *current = head;
	Node *previous = NULL;
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
	}
	previous->next = NULL;
	free(current->value);
	free(current);
	return head;
}

/**
* list_size get the number of node in the list
* @param pointer to the head of the list
* @return integer number of node in the list
*/
int list_size(Node *head)
{
	int i = 0;
	Node *current = head;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return i;
}

/**
* list_contains check if there is specific value existing in the list
* @param pointer to the head node of the list
* @param pointer to the value to find
* @param compare equal function for pointer casting and compare values
* @return boolean value if the value is in the list or not
*/
bool list_contains(Node *head, void *target_value, bool (*compare_eq)(void*, void*))
{
	if (head == NULL) return false;
	else if (compare_eq(head->value, target_value)) return true;
	else
	{
		return list_contains(head->next, target_value, compare_eq);
	}
}

/**
* list_count count how many times the specific value apprear in the list
* @param pointer to the head node of the list
* @param pointer to the value to be counted
* @param compare function for pointer casting and value comparison 
* @return integer value represent the number of frequency target value appear in the list
*/
int list_count(Node *head, void *target_value, bool (*compare_eq)(void*, void*))
{
	if (head == NULL) return 0;
	else if (compare_eq(head->value, target_value)) return 1 + list_count(head->next, target_value, compare_eq);
	else
	{
		return list_count(head->next, target_value, compare_eq);
	}
}

/**
* list_replace fucntion that replace the value  of the node holding specified value
* @param pointer to the head node of the list
* @param pointer to the value to be replaced
* @param compare equal function for pointer casting and value comparison 
*/
void list_replace(Node *head, void *value, void *new_value, size_t new_value_size, bool (*compare_eq)(void*, void*))
{
	if (head == NULL) return;
	else if (compare_eq(head->value, value)) 
	{
		free(head->value);
		head->value = malloc(new_value_size);
		memcpy(head->value, new_value, new_value_size);
		return;
	}
	else
	{
		list_replace(head->next, value, new_value, new_value_size, compare_eq);
	}
}

/**
* list_erase_match function for deleting node with specified value
* @param pointer to the head node of the list
* @param pointer to the desired value
* @param compare equal function for pointer casting and value comparison
* @return pointer to the head node of the list
*/
Node *list_erase_match(Node *head, void *value, bool (*compare_eq)(void*, void*))
{
	if (head == NULL) return NULL;

	if (compare_eq(head->value, value))
	{
		Node *temp = head->next;
		free(head->value);
		free(head);
		return temp;
	}
	
	Node *current = head->next;
	Node *previous = head;

	while (current->next != NULL)
	{
		if (compare_eq(current->value, value))
		{
			previous->next = current->next;
			free(current->value);
			free(current);
			return head;
		}
		previous = current;
		current = current->next;
	}

	return head;
}

/**
* list_erase_all_matches function delete all nodes which holding the same value as specified value
* @param pointer to the head node of the list
* @param pointer to the desired value
* @param compare equal fucntion for pointer casting and value comparison
*/
Node *list_erase_all_matches(Node *head, void *value, bool (*compare_eq)(void*, void*))
{
	if (head == NULL) return NULL;
	Node *current = head;
	Node *temp = NULL;
	Node *new_head = NULL;

	while (compare_eq(current->value, value))
	{
		temp = current;
		current = current->next;
		free(temp->value);
		free(temp);
		if (current == NULL) return NULL;
	}
	new_head = current;

	while (current != NULL && current->next != NULL)
	{
		if (compare_eq(current->next->value, value)) 
		{
			temp = current->next;
			current->next = current->next->next;
			free(temp->value);
			free(temp);
		}
		else
		{
			current = current->next;
		}
	}
	return new_head;
}

/**
* list_append function append two list together by setting last node of the first list 
  point to the head of the second list
* @param pointer to the head node of the first list
* @param pointer to the head node of the second list
* @return pointer to the head node of new appended list
*/
Node *list_append(Node *head1, Node *head2)
{
	if (head1 == NULL) return head2;
	if (head2 == NULL) return head1;
	
	Node *current = head1;
	while (current->next != NULL)
	{
		current = current->next;
	}	
	current->next = head2;
	return head1; 
}

/**
* list_reverse function will reverse the linked list order by manipulating node pointer
* @param pointer to the head node of the list
* @return pointer to the new head node of reversed list
*/
Node *list_reverse(Node *head)
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	Node *current = head;
	Node *next_node = head->next;

	current->next = NULL;
	while (next_node != NULL)
	{
		Node *temp = next_node->next;
		next_node->next = current;
		current = next_node;
		next_node = temp;
	}
	return current;
}

/**
* list_sort function will sort linked list in ascending order
* To sort decending order edit compare function or change if statement in this function 
* @param pointer to the head node of the list
* @param compare function for pointer casting and value comparision
* @param memory size of value in the list for memcpy() function 
*/
void list_sort(Node *head, bool(*compare)(void*, void*), size_t value_size)
{
	if (head == NULL) return;
	if (head->next == NULL) return;
	bool swap = true;
	while (swap)
	{
		Node *current = head;
		Node *previous = NULL;
		swap = false;
		while (current != NULL && current->next != NULL)
		{
			previous = current;
			current = current->next;
			if (compare(current->value, previous->value))
			{
				void *temp = malloc(value_size);
				memcpy(temp, previous->value, value_size);
				memcpy(previous->value, current->value, value_size);
				memcpy(current->value, temp, value_size);
				swap = true;
				free(temp);
			}
		}
	}
}

//Bug: Function somehow break linked list
//Fixed : Miscompare current1->value , current2->value (should be current2->next->value)
//Fixed : if statement should check value in the next node

/**
* list_remove_duplicate function will delete all duplicated value which appear more than once
* @param pointer to the head of the list
* @param compare equal function for pointer casting and value comparison
* @return pointer to the head node of the list
*/
Node *list_remove_duplicate(Node *head, bool (compare_eq)(void*, void*))
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	Node *current1 = NULL;
	Node *current2 = NULL;
	Node *duplicate = NULL;
	current1 = head;

	while (current1 != NULL && current1->next != NULL)
	{
		current2 = current1;
		while (current2->next != NULL)
		{
			if (compare_eq(current1->value, current2->next->value))
			{
				duplicate = current2->next;
				current2->next = current2->next->next;
				free(duplicate->value);
				free(duplicate);
			}
			else
			{
				current2 = current2->next;
			}
		}
		current1 = current1->next;
	}
	return head;
}

/**
* list_insert_behind function will insert new node into the list after the node holding specified value
* @param pointer to the head node of the list
* @param pointer to the specified value
* @param pointer to the new node's value
* @param memory size of new node's value
* @param compare function for pointer casting and value comparison
* @return pointer to the head node of the list
*/
Node *list_insert_behind(Node *head, void *target_value, void *new_node_value, size_t value_size, bool (*compare)(void*, void*))
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}	
	new_node->value = malloc(value_size);
	new_node->next = NULL;
	memcpy(new_node->value, new_node_value, value_size);

	if (head == NULL) return new_node;
	if (head->next == NULL)
	{
		head->next = new_node;
		return head;
	}	
	Node *current = head;
	while (current->next != NULL)
	{
		if (compare(current->value, target_value))
		{
			new_node->next = current->next;
			current->next = new_node;
			return head;
		}
		else
		{
			current = current->next;
		}
	}
	return head;
}

// NOTE: Because generic linkedlist has no way to prevent user giving node->value as stack or heap allocated
//Update : Make every node heap allocated by malloc every node's value
//         This increase more memory usage but more versitility as a trade off
//Further improvement ???: Add flag in node struct, identify if node is heap or stack allocated
//                         Seems more memory effecient but need to fix functions as well

/**
* list_clean fucntion free memory of every node's value and the node itself
* @param pointer to pointer to the head node of the list
* @return pointer to the node which will be set to NULL after freeing all nodes 
*/
Node *list_clean(Node **head)
{
	if (head == NULL || *head == NULL) return NULL;
	
	Node *current = *head;
	while (current != NULL)
	{
		Node *prev = current;
		current = current->next;
		free(prev->value);
		free(prev);
	}
	*head = NULL;
}

//Work with integer only!
//Can be written for generic datatype! But later
//TODO: Implement pointer casting function to make this function work with generic datatype!
//Update: compare functions were done!! However, this function should be able to work
//        with number and char.
//      : What about working with string ??????
//Update: This funtion also works with string and char. Strings will be combined into one string and stored in
//        the node in the first list
//        Charecters will be combined into a string stored in the node of the first list 

/**
* list_add function will add the value at the Ith node of both lists into the first list 
  if one both list does not share the same length, the function will stop at the shorter length 
* @param pointer to the node of the first list
* @param pointer to the node of the second list
* @param add function for pointer casting and combine value 
*/
void list_add(Node *list1, Node *list2, void (*add)(void*, void*))
{
	if (list1 == NULL || list2 == NULL) return;
	Node *current1 = list1;
	Node *current2 = list2;

	while (current1 != NULL && current2 != NULL)
	{
		add(current1->value, current2->value);
		current1 = current1->next;
		current2 = current2->next;
	}

}

/**
* list_cpy function will allocate memory and copy nodes and content from given list
* Content in the list should be the same datatype 
* @param pointer to the head node of given list
* @param memory size of content in the list
* @return pointer to to head node of new copy list
*/
Node *list_cpy(Node *head, size_t value_size)
{
	if (head == NULL) return NULL;
	Node *new_list = malloc(sizeof(Node));
	if (new_list == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_list->value = malloc(value_size);
	if (new_list->value == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(new_list->value, head->value, value_size);

	new_list->next = list_cpy(head->next, value_size);

	return new_list;
}

//This function return new pointer to new merged list
//This function manipulates pointer to restructure new list
//This function doesn't create new node

/**
* list_merge function will merge two sorted list (in ascending order) together. This function assume that 
  both lists are already sorted
* @param pointer to the head node of the first list
* @param pointer to the head node of the second list
* @param compare function for pointer casting and value comparison
*/
Node *list_merge(Node *list1, Node *list2, bool (*compare)(void*, void*))
{
	if (list1 == NULL) return list2;
	if (list2 == NULL) return list1;

	Node *l1current;
	Node *l2current;
	Node *new_head;
	Node *new_current;

	l1current = list1;
	l2current = list2;
	if (compare(l1current->value, l2current->value))
	{
		new_head = l1current;
		l1current = l1current->next;
	}
	else
	{
		new_head = l2current;
		l2current = l2current->next;
	}
	
	new_current = new_head;
	while (l1current != NULL && l2current != NULL)
	{
		if (compare(l1current->value, l2current->value))
		{
			new_current->next = l1current;
			new_current = l1current;
			l1current = l1current->next;
		}
		else
		{
			new_current->next = l2current;
			new_current = l2current;
			l2current = l2current->next;
		}
	}
	
	if (l1current == NULL) new_current->next = l2current;
	if (l2current == NULL) new_current->next = l1current;

	return new_head;
}

/**
* list_swap function will swap pointer of two lists
* @param pointer to pointer to the head node of the first list
* @param pointer to pointer to the head node of the second list
*/
void list_swap(Node **list1, Node **list2)
{
	Node *temp;
	temp = *list1;
	*list1 = *list2;
	*list2 = temp;
	return;
}

/**
* list_delete function delete node at Nth
* N is the order of node to be deleted
* Node order should start from 1. Hence N must not less than 1
* @param pointer to the head node of the list
* @param position of node to be deleted
* @return pointer to the head node of the list
*/
Node *list_delete(Node *head, int n)
{
	if (head == NULL) return NULL;
	if (head->next == NULL &&  n == 1) return NULL; //delete first node  

	if (n > list_size(head))
	{
		printf("Position out of bound\n");
		return head;
	}

	if (n < 1)
	{
		printf("Position start from one\n");
		return head;
	}
	
	Node *current = head;
	Node *prev = NULL;
	for (int i = 0; i < n - 1; i++)
	{
		prev = current;
		current = current->next;
	}

	prev->next = current->next;
	free(current->value);
	free(current);
	return head;
}
