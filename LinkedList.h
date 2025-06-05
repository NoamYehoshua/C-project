#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Defs.h"
/**
 * @file LinkedList.h
 * @brief Generic ADT for a linked list.
 *
 * This module provides functions to create, manipulate, and destroy
 * a generic linked list. It uses user-provided functions for copying,
 * freeing, printing, and comparing elements stored in the list.
 */

/* Forward declaration for the LinkedList structure */
typedef struct LinkedList_s * LinkedList;

/**
 * @brief Creates a new linked list.
 *
 * @param copyFunc Function pointer to copy an element.
 * @param freeFunc Function pointer to free an element.
 * @param printFunc Function pointer to print an element.
 * @param equalFunc Function pointer to compare two elements.
 * @return A pointer to the created linked list, or NULL on failure.
 */
LinkedList createLinkedList(CopyFunction copyFunc, FreeFunction freeFunc, PrintFunction printFunc,EqualFunction equalFunc);

/**
 * @brief Destroys the linked list and frees all its elements.
 *
 * @param list Pointer to the linked list to destroy.
 * @return status (success or Invalid_input).
 */
status destroyList(LinkedList list);

/**
 * @brief Appends a new node with the given element to the linked list.
 *
 * @param list Pointer to the linked list.
 * @param element The element to add to the list.
 * @return status (success, Invalid_input or Memory_Problem).
 */
status appendNode(LinkedList list, Element element);

/**
 * @brief Deletes a node from the linked list based on a matching parameter.
 *
 * @param list Pointer to the linked list.
 * @param PrameterToEqual The parameter (or key) to compare using the equal function.
 *        The user must provide an element or part of an element that matches
 *        the criteria defined in the comparison function.
 * @return status (success, Invalid_input or no_element).
 */
status deleteNode(LinkedList list, Element PrameterToEqual);

/**
 * @brief Displays all elements in the linked list using the print function.
 *
 * @param list Pointer to the linked list.
 * @return status (success or Invalid_input).
 */
status displayList(LinkedList list);

/**
 * @brief Returns a copy (using the copy function that the user sent)
 * of the data stored in the node at the specified index.
 *
 * @param list Pointer to the linked list.
 * @param index The index of the desired element. The first index of the linked list is 1.
 * @return Copy of element at the given index (using the copy function that the user sent),
 * or NULL if the index is invalid (smaller than 1 or bigger from the length of the linked list)
 *
 * If the user decided to perform a deep copy, he must clear the allocation returned to him from the function.
 */
Element getDataByIndex(LinkedList list, int index);

/**
 * @brief Retrieves the length of the linked list.
 *
 * @param list Pointer to the linked list.
 * @return The number of nodes in the list or -1 if the list is NULL.
 */
int getLengthList(LinkedList list);

/**
 * @brief Searches for an element in the linked list using a key.
 *
 * @param list Pointer to the linked list.
 * @param key The key (or partial element) used for comparison. The user
 *        must provide a value that matches the criteria defined in the comparison function.
 * @return A pointer to copy of the found element (using the copy function that the user sent),
 * or NULL if no match is found or if the user send invalid output.
 *
 * If the user decided to perform a deep copy, he must clear the allocation returned to him from the function
 */
Element searchByKeyInList(LinkedList list, Element key);

#endif //LINKEDLIST_H
