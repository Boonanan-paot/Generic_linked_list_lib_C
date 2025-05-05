#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "list.h"
#include <time.h>

void test_list_empty(void)
{
	//Case 1: Empty list
    Node *head = NULL;
   	int value1 = 42;
	CU_ASSERT_TRUE(list_empty(head));

	//Case 2: Non-empty list
	head = insert_front(head, &value1, sizeof(value1));
	CU_ASSERT_FALSE(list_empty(head));
}

void test_insert_front(void)
{
    Node *head = NULL;
    int value1 = 42;

	//Case 1: Insert to empty list
    head = insert_front(head, &value1, sizeof(value1));
    CU_ASSERT_PTR_NOT_NULL(head); //Assert head not NULL
    CU_ASSERT_EQUAL(*(int*)head->value, 42); //Assert correct value
    CU_ASSERT_PTR_NULL(head->next); //Assert no next node in the list

	//Case 2: Insert to non-empty list
    char value2 = 'A';
    head = insert_front(head, &value2, sizeof(value2));
    CU_ASSERT_PTR_NOT_NULL(head); //Assert head is not NULL
    CU_ASSERT_EQUAL(*(char*)head->value, 'A'); //Assert correct value
    CU_ASSERT_PTR_NOT_NULL(head->next); //Assert next node not NULL
    CU_ASSERT_EQUAL(*(int*)head->next->value, 42); //Assert second node correct value

	head = list_clean(&head);
}

void test_insert_back(void)
{
	//Case 1: Insert into empty list
	Node *head = NULL;
	int value1 = 42;
	head = insert_back(head, &value1, sizeof(value1));
	CU_ASSERT_PTR_NOT_NULL(head); //Assert head not NULL
	CU_ASSERT_EQUAL(*(int*)head->value, 42); //Assert node's value
	CU_ASSERT_PTR_NULL(head->next);

	//Case 2: Insert into non empty list
	char value2 = 'A';
	head = insert_back(head, &value2, sizeof(value2));
	CU_ASSERT_PTR_NOT_NULL(head->next); //Assert tail node not NULL
	CU_ASSERT_EQUAL(*(char*)head->next->value, 'A'); //Assert tail node's value

	head = list_clean(&head);
}

void test_delete_front(void)
{
	Node *head = NULL;

	//Case 1 : Empty list head == NULL
	CU_ASSERT_PTR_NULL(delete_front(head)); //Assert empty list return NULL
	int value1 = 42;
	int value2 = 50;
	
	//Case 2 : List has only one node
	head = insert_front(head, &value1, sizeof(value1));
	head = delete_front(head);
	CU_ASSERT_PTR_NULL(head); //Assert head == NULL after deleted
	//Case 3 : List contains more than one node
	head = insert_front(head, &value1, sizeof(value1));
	head = insert_front(head, &value2, sizeof(value2));
	head = delete_front(head); //Delete front node
	CU_ASSERT_PTR_NOT_NULL(head); //Assert new head node
	CU_ASSERT_EQUAL(*(int*)head->value, 42); //Assert new head's value
	CU_ASSERT_PTR_NULL(head->next); //Assert new head pointing to NULL

	head = list_clean(&head); 
}

void test_delete_back(void)
{
	Node *head = NULL;
	//Case 1: Empty list
	CU_ASSERT_PTR_NULL(delete_back(head)); 

	//Case 2: Delete from non-empty list
	int i = 0;
	for (i; i < 3; i++)
	{
		head = insert_back(head, &i, sizeof(i)); 
	}
	head = delete_back(head);
	
	CU_ASSERT_PTR_NOT_NULL(head); //Assert head not NULL
	CU_ASSERT_PTR_NOT_NULL(head->next); //Assert second node not NULL
	CU_ASSERT_PTR_NULL(head->next->next); //Assert second node pointing to NULL

	head = list_clean(&head);
}

void test_list_size(void)
{
	Node *head = NULL;
	int size = 0;
	//Case 1: Empty list
	CU_ASSERT_EQUAL(list_size(head), 0); //Assert empty list

	//Case 2: Non-empty list, expect the right size returned
	for (int i = 0; i < 5; i++)
	{
		head = insert_back(head, &i, sizeof(i));
	}
	size = list_size(head);
	CU_ASSERT_EQUAL(size, 5); //Assert list size 

	head = list_clean(&head);
}

void test_list_contains(void)
{
	Node *head = NULL;
	int value[7] = {10, 344, 42, 45, 324, 0, 24};
	int target1 = 324;
	int target2 = 999;
	//Case 1 : Check empty list -> expect false 
	CU_ASSERT_FALSE(list_contains(head, &target1, compare_eq_int));

	for (int i = 0; i < 7; i++)
	{
		head = insert_back(head, &value[i], sizeof(i));
	}
	//Case 2 : Check existing value in list -> expect true
	CU_ASSERT_TRUE(list_contains(head, &target1, compare_eq_int)); //Assert contains true
	//Case 3 : Check non-existing value in list -> expect false
	CU_ASSERT_FALSE(list_contains(head, &target2, compare_eq_int)); //Assert contains false
	
	head = list_clean(&head);
}

void test_list_replace(void)
{
	Node *head = NULL;
	int value = 42, value2 = 50;
	int new_value = 56;
	head = insert_back(head, &value, sizeof(value));
	head = insert_back(head, &value2, sizeof(value2));
	list_replace(head, &value, &new_value, sizeof(new_value), compare_eq_int);
	
	//CU_ASSERT_EQUAL(*(int*)head->value, 56); //Assert replace 42 with 56
	
	new_value = 100;
	list_replace(head, &value2, &new_value, sizeof(new_value), compare_eq_int);
	//CU_ASSERT_EQUAL(*(int*)head->next->value, 100); //Assert replace 50 with 100

	head = list_clean(&head);
}

void test_list_erase_match(void)
{
	Node *head = NULL;
	char c[] = {'a', 'b', 'c', 'g', 'h', 'd', 'f'};
	
	//Case 1 : Empty list
	char target1 = 'C';
	head = list_erase_match(head, &target1, compare_eq_char);
	CU_ASSERT_PTR_NULL(head); // Assert empty list
	
	for (int i = 0; i < 7; i++)
	{
		head = insert_back(head, &c[i], sizeof(c[i]));
	}	

	//Case 2 : Delete first node
	head = list_erase_match(head, &c[0], compare_eq_char);
	CU_ASSERT_EQUAL(*(char*)head->value, 'b'); //Assert new head

	//Case 3 : Delete middle node
	head = list_erase_match(head, &c[4], compare_eq_char);
	CU_ASSERT_FALSE(list_contains(head, &c[4], compare_eq_char)); //Assert deleted node in the middle

	head = list_clean(&head);
}

void test_list_erase_all_matches(void)
{
	Node *head = NULL;
	char *string[7] = {"Hello", "World", "I", "am", "Batman", "Before", "Dude"};
	char *target1 = "Hello";
	//Case 1: List is empty
	head = list_erase_all_matches(head, target1, compare_eq_string);
	CU_ASSERT_PTR_NULL(head);
	
	for (int i = 0; i < 7; i++)
	{
		head = insert_back(head, string[i], sizeof(string[i]));
	}

	//Case 2: Delete head node
	head = list_erase_all_matches(head, target1, compare_eq_string);
	CU_ASSERT_STRING_EQUAL((char*)head->value, "World");
	CU_ASSERT_FALSE(list_contains(head, target1, compare_eq_string));

	//Case 3: Delete middle node
	char *target2 = "am";
	head = list_erase_all_matches(head, target2, compare_eq_string);
	CU_ASSERT_FALSE(list_contains(head, target2, compare_eq_string));
	
	head = list_clean(&head);
}

void test_list_append(void)
{
	Node *list1 = NULL;
	Node *list2 = NULL;
	
	for (int i = 0; i < 5; i++)
	{
		list1 = insert_back(list1, &i, sizeof(i));
	}
	//Case 1 : list2 is empty
	list1 = list_append(list1, list2);
	CU_ASSERT_EQUAL(list_size(list1), 5); //Assert size of list 1	
	
	list2 = list1;
	list1 = NULL;

	//Case 2 : list1 is empty
	list1 = list_append(list1, list2);
	CU_ASSERT_EQUAL(list_size(list1), 5); // Assert size of list 2

	list1 = list2;
	list2 = NULL;

	for (int i = 97; i < 102; i++)
	{
		list2 = insert_back(list2, &i, sizeof(i));
	}

	//Case 3 : both list not empty
	list1 = list_append(list1, list2);
	CU_ASSERT_EQUAL(list_size(list1), 10); //Assert size of both list

	Node *current = list1;
	int index = 0;
	while(current != NULL)
	{
		if (index < 5)
		{
			CU_ASSERT_EQUAL(*(int*)current->value, index);
		}
		else
		{
			CU_ASSERT_EQUAL(*(char*)current->value, (char)index + 97 - 5);
		}
		current = current->next;
		index++;
	} 
	list1 = list_clean(&list1);
}

void test_list_reverse(void)
{
	Node *head = NULL;
	//Case 1 : Empty list
	head = list_reverse(head);
	CU_ASSERT_PTR_NULL(head); //Assert head null

	//Case 2 : Only one node in list
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	head = insert_back(head, &arr[0], sizeof(arr[0]));
	head = list_reverse(head);
	CU_ASSERT_EQUAL(*(int*)head->value, 0); //Assert returned head value
	CU_ASSERT_PTR_NULL(head->next); //Assert head pointing to NULL

	//Case 3 : reverse non-empty list
	for (int i = 1; i < 10; i++)
	{
		head = insert_back(head, &arr[i], sizeof(arr[i]));
	}
	head = list_reverse(head);
	Node *current = head;
	for (int i = 9; i >= 0; i--)
	{
		CU_ASSERT_EQUAL(*(int*)current->value, arr[i]); //Assert value in reversed list
		current = current->next;
	}
	head = list_clean(&head); 
} 

void test_list_remove_duplicate(void)
{
	//Case 1 : Empty list return NULL
	Node *list = NULL;
	list = list_remove_duplicate(list, compare_eq_int);
	CU_ASSERT_PTR_NULL(list);

	//Case 2 : Only one node in list
	int a = 0;
	list = insert_front(list, &a, sizeof(a));
	list = list_remove_duplicate(list, compare_eq_int);
	CU_ASSERT_EQUAL(*(int*)list->value, a);
	CU_ASSERT_PTR_NULL(list->next);
	//Case 3 : List has more than one node 
	int b = 5;
	for (int i = 0; i < 5; i++)
	{
		list = insert_back(list, &b, sizeof(b));
	}
	list = list_remove_duplicate(list, compare_eq_int);
	CU_ASSERT_EQUAL(*(int*)list->next->value, b);
	CU_ASSERT_PTR_NULL(list->next->next);
	
	list = list_clean(&list);
}	

void test_insert_behind(void)
{
	Node *list = NULL;
	//Case 1 : Empty list should return new head
	int value1 = 0;
	int target1 = 9;
	list = list_insert_behind(list, &target1, &value1, sizeof(value1), compare_eq_int);
	CU_ASSERT_EQUAL(*(int*)list->value, value1);
	CU_ASSERT_PTR_NULL(list->next);
	//Case 2 : Insert at tail
	int value2 = 5;
	list = list_insert_behind(list, &value1, &value2, sizeof(value2), compare_eq_int);
	CU_ASSERT_EQUAL(*(int*)list->next->value, value2);
	CU_ASSERT_PTR_NULL(list->next->next);
	//Case 3 : Insert at middle
	int value3 = 18;
	list = list_insert_behind(list, &value1, &value3, sizeof(value3), compare_eq_int);
	CU_ASSERT_EQUAL(*(int*)list->next->value, value3);
	CU_ASSERT_EQUAL(*(int*)list->next->next->value, value2);
	
	list = list_clean(&list);
}

void test_list_clean(void)
{
	Node *list = NULL;
	for (int i = 0; i < 10; i++)
	{
		list = insert_back(list, &i, sizeof(i));
	}
	list_clean(&list);
	CU_ASSERT_PTR_NULL(list);
}

void test_list_merge(void)
{
	Node *list1 = NULL;
    Node *list2 = NULL;

    int values1[] = {1, 3, 5};
    int values2[] = {2, 4, 6};

    for (int i = 0; i < 3; i++)
    {
        list1 = insert_back(list1, &values1[i], sizeof(int));
        list2 = insert_back(list2, &values2[i], sizeof(int));
    }

    Node *merged_list = list_merge(list1, list2, compare_int);

    int expected_values[] = {1, 2, 3, 4, 5, 6};
    Node *current = merged_list;
    for (int i = 0; i < 6; i++)
    {
        CU_ASSERT_PTR_NOT_NULL(current);
        CU_ASSERT_EQUAL(*(int*)current->value, expected_values[i]);
        current = current->next;
    }
    CU_ASSERT_PTR_NULL(current);

    list_clean(&merged_list);
}

void test_list_swap(void)
{
    Node *list1 = NULL;
    Node *list2 = NULL;

    int value1 = 1, value2 = 2;
    list1 = insert_back(list1, &value1, sizeof(int));
    list1 = insert_back(list1, &value2, sizeof(int));

    int value3 = 3, value4 = 4;
    list2 = insert_back(list2, &value3, sizeof(int));
    list2 = insert_back(list2, &value4, sizeof(int));

    list_swap(&list1, &list2);

    // Verify list1 now contains the values of list2
    CU_ASSERT_EQUAL(*(int*)list1->value, 3);
    CU_ASSERT_EQUAL(*(int*)list1->next->value, 4);

    // Verify list2 now contains the values of list1
    CU_ASSERT_EQUAL(*(int*)list2->value, 1);
    CU_ASSERT_EQUAL(*(int*)list2->next->value, 2);

    list_clean(&list1);
    list_clean(&list2);
}

void test_list_sort(void)
{
	Node *list = NULL;
	srand(time(0));
	for (int i = 0; i < 5; i++)
	{
		int rd = rand();
		list = insert_back(list, &rd, sizeof(int));
	}
	list_sort(list, compare_int, sizeof(int));
	
	Node *current = list;
    int prev_value = *(int*)current->value;
    current = current->next;

    while (current != NULL)
    {
        int current_value = *(int*)current->value;
        CU_ASSERT_TRUE(prev_value <= current_value); 
        prev_value = current_value;
        current = current->next;
    } 
	list_clean(&list);
}

void test_list_sort_string(void)
{
    Node *list = NULL;

    // Insert strings into the list
    char *values[] = {"banana", "apple", "cherry", "date", "fig"};
    for (int i = 0; i < 5; i++)
    {
        list = insert_back(list, values[i], strlen(values[i]) + 1); // Allocate memory for each string
    }

    // Sort the list
    list_sort(list, compare_string, sizeof(char*));

    // Verify the list is sorted
    char *expected_values[] = {"apple", "banana", "cherry", "date", "fig"};
    Node *current = list;
    for (int i = 0; i < 5; i++)
    {
        CU_ASSERT_PTR_NOT_NULL(current);
        CU_ASSERT_STRING_EQUAL((char*)current->value, expected_values[i]);
        current = current->next;
    }

    // Clean up
    list_clean(&list);
    CU_ASSERT_PTR_NULL(list);
}

void test_list_add(void)
{
	Node *list1 = NULL;
	Node *list2 = NULL;

	int value1[] = {1, 2, 3};
	int value2[] = {4, 5, 6};

	for (int i = 0; i < 3; i++)
	{
		list1 = insert_back(list1, &value1[i], sizeof(int));
		list2 = insert_back(list2, &value2[i], sizeof(int));
	}
	list_add(list1, list2, add_int);

	int expected[] = {5, 7, 9};
	Node *current = list1;
	for (int i = 0; i < 3; i++)
	{
		CU_ASSERT_EQUAL(*(int*)current->value, expected[i]);
		current = current->next;
	}
	list_clean(&list1);
	list_clean(&list2);
}

void test_list_delete(void)
{
	Node *list = NULL;
	//Case 1: empty list 
	list = list_delete(list, 0);
	CU_ASSERT_PTR_NULL(list);

	//Case 2: delete head node
	int a = 0;
	list = insert_front(list, &a, sizeof(a));
	list = list_delete(list, 1);
	CU_ASSERT_PTR_NULL(list);
	
	//Case 3: Delete middle node
	for (int i = 0; i < 5; i++)
	{
		list = insert_back(list, &i, sizeof(i));
	}
	
	list = list_delete(list, 3);
	CU_ASSERT_EQUAL(list_size(list), 4);

	//Case 4: delete tail node >> size 5 delete node 5
	//Must not has Segmentation fault 
	list = list_delete(list, 4);
	Node *current = list;
	int b[] = { 0, 1, 3};
	CU_ASSERT_EQUAL(list_size(list), 3);
	for (int i = 0; i < 3; i++)
	{
		CU_ASSERT_EQUAL(*(int*)current->value, b[i]);
		current = current->next;
	}
	list_clean(&list);	
}

int main(void)
{
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    
    CU_pSuite suite = CU_add_suite("Linked List Test", NULL, NULL);
    if (suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

	CU_add_test(suite, "Test insert_front", test_insert_front);
	CU_add_test(suite, "Test list_empty", test_list_empty);
	CU_add_test(suite, "Test insert_back", test_insert_back);
	CU_add_test(suite, "Test delete_front", test_delete_front);
	CU_add_test(suite, "Test delete_back", test_delete_back);
	CU_add_test(suite, "Test list_size", test_list_size);
	CU_add_test(suite, "Test list_contains", test_list_contains);
	CU_add_test(suite, "Test list_replace", test_list_replace);
	CU_add_test(suite, "Test list_erase_match", test_list_erase_match);
	CU_add_test(suite, "Test list_erase_all_matches", test_list_erase_all_matches);
	CU_add_test(suite, "Test list_append", test_list_append);
	CU_add_test(suite, "Test list_reverse", test_list_reverse);
	CU_add_test(suite, "Test list_remove_duplicate", test_list_remove_duplicate);
	CU_add_test(suite, "Test insert_behind", test_insert_behind);
	CU_add_test(suite, "Test list_clean", test_list_clean);
	CU_add_test(suite, "Test list_merge", test_list_merge);
	CU_add_test(suite, "Test list_swap", test_list_swap);
	CU_add_test(suite, "Test list_sort", test_list_sort);	
	CU_add_test(suite, "Test list_sort string", test_list_sort_string);
	CU_add_test(suite, "Test list_add", test_list_add);	
	CU_add_test(suite, "Test list_delete", test_list_delete);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
