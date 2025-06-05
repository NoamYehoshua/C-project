#include "LinkedList.h"
/**
 * @struct node_s
 *
 * A structure representing a node in a double linked list.
 * It contains pointers to the next and previous nodes, as well as the data it holds.
 * The data it hold is the elements that receive from the user at append node.
 */
struct node_s {
    struct node_s *next;  // Pointer to the next node in the list.
    struct node_s *prev;  // Pointer to the previous node in the list
    Element data;         // The data associated with the node - elements the user store in the linked list.
};

// Type definition for a pointer to a node.
typedef struct node_s * Node;

/**
 * @struct LinkedList_s
 *
 * A structure representing a double linked list.
 * It contains pointers to the head and tail nodes, the number of elements in the list,
 * and function pointers for copying, freeing, printing and comparing elements that send by the user.
 */
struct LinkedList_s {
    Node head;                       // Pointer to the first node in the list.
    Node tail;                       // Pointer to the last node in the list.
    int count_elements;              // The number of elements in the list.
    CopyFunction copyElement;        // Function pointer for copying an element.
    FreeFunction freeElement;        // Function pointer for freeing an element.
    PrintFunction printElement;      // Function pointer for printing an element.
    EqualFunction equal;             // Function pointer for comparing an element.
};

/**
 * Creates a new linked list.
 *
 * @param copyFunc Function for copying an element.
 * @param freeFunc Function for freeing an element.
 * @param printFunc Function for printing an element.
 * @param equalFunc Function for comparing elements.
 * @return A pointer to the created linked list, or NULL if memory allocation fails or any function pointer is NULL.
 */
LinkedList createLinkedList(CopyFunction copyFunc, FreeFunction freeFunc, PrintFunction printFunc,EqualFunction equalFunc) {
    // check if the pointers the function gets equal to null
    if (copyFunc == NULL || freeFunc == NULL || printFunc == NULL || equalFunc == NULL) {
        return NULL;
    }
    // Allocate space for LinkedList
    LinkedList list = (LinkedList) malloc(sizeof(struct LinkedList_s));
    // Check if the allocate success.
    if (list == NULL) {
        return NULL;
    }
    // Initialize LinkedList fields as defined in the struct, with the function the user send
    list->head = NULL;
    list->tail = NULL;
    list->count_elements = 0;
    list->copyElement = copyFunc;
    list->freeElement = freeFunc;
    list->printElement = printFunc;
    list->equal = equalFunc;
    return list;
}

/**
 * Destroys the linked list and frees all allocated memory.
 *
 * @param list The linked list to destroy.
 * @return success if the list was destroyed, or Invalid_input if the list is NULL.
 */
status destroyList(LinkedList list) {
    // check if the pointer the function gets equal to null
    if (list == NULL) {
        return Invalid_input;
    }
    // Hold the first node in the linked list in curr
    Node curr = list->head;
    // iterate on all the node in the linked list until curr equal to null (we end to iterate on the list)
    while (curr != NULL) {
        // save with temp the next node
        Node tmp = curr->next;
        // free the node data with the free function the user send in the create linked list function
        list->freeElement(curr->data);
        // free the space we allocate to curr in create node
        free(curr);
        // change curr to the next node
        curr = tmp;
    }
    // free the space we allocate to list in create linked list
    free(list);
    return success;
}


/**
 * Creates a new node with the specified data, element from the user, and adds it to the linked list.
 *
 * @param data The data (element from the user) to store in the new node.
 * @param list The linked list to which the new node will be added.
 * @return A pointer to the created node, or NULL if memory allocation fails or the data is NULL.
 */
static Node createNode(Element data,LinkedList list) {
    // check if the pointers the function gets equal to null
    if (data == NULL|| list==NULL) {
        return NULL;
    }
    // Allocate space for node
    Node node = (Node) malloc(sizeof(struct node_s));
    // Check if the allocate success.
    if (node == NULL) {
        return NULL;
    }
    // copy the element that the user want to save in the linked list with the copy function the user send in create link list function
    node->data = list->copyElement(data);
    // check if the copy success;
    if (node->data == NULL) {
        // free the space we allocate to node if allocate fail
        free(node);
        return NULL;
    }
    return node;
}

/**
 * Appends a new node with the given element to the linked list.
 *
 * @param list The linked list to append the node to.
 * @param element The element to store in the new node.
 * @return success if the node was successfully appended,Invalid_input if one of the parameters is NULL
 * or Memory_Problem if memory allocation fails.
 */
status appendNode(LinkedList list, Element element) {
    // check if the pointers the function gets equal to null
    if (list == NULL|| element == NULL) {
        return Invalid_input;
    }
    // Hold the first node in the linked list in curr
    Node curr = list->head;
    // if curr is equal to NULL, the linked list empty
    if (curr == NULL) {
        // create node
        list->head = createNode(element, list);
        // Check if the allocate success.
        if (list->head == NULL) {
            return Memory_Problem;
        }
        // Initialize the next and prev fields of head and tail and Initialize element count to 1
        list->head->next = NULL;
        list->head->prev = NULL;
        list->count_elements=1;
        list->tail = list->head;
        list->tail->next = NULL;
        list->tail->prev = NULL;
        return success;
    }
    else {
        // create node
        list->tail->next = createNode(element, list);
        // Check if the allocate success.
        if (list->tail->next == NULL) {
            return Memory_Problem;
        }
        // Initialize the next and prev fields of tail and increase element count by 1
        list->tail->next->next = NULL;
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->count_elements = list->count_elements + 1;
        return success;
    }
}

/**
 * Deletes a node from the linked list that matches the specified element.
 *
 * @param list The linked list from which to delete the node.
 * @param ParameterToEqual The element to compare for deletion.
 * The user must provide an element or part of an element that matches
 * the criteria defined in the comparison function.
 * @return success if the node was deleted,Invalid_input if one of the parameters is NULL
 * or no_element if the element was not found in the list.
 */
status deleteNode(LinkedList list, Element PrameterToEqual) {
    // check if the pointers the function gets equal to null
    if (list == NULL || PrameterToEqual == NULL) {
        return Invalid_input;
    }
    // Hold the first node in the linked list in curr
    Node curr = list->head;
    // iterate on all the node in the linked list until curr equal to null (we end to iterate on the list)
    while (curr != NULL) {
        // Check if the current node (or node's parameter to equal) equal to the PrameterToEqual
        if (list->equal(curr->data, PrameterToEqual)) {
            // change the prev and next files if the node is equal according to its position in the linked list
            if (curr== list->head) {
                if (curr->next!=NULL) {
                    curr->next->prev = NULL;
                    list->head = curr->next;
                }
            }
            else if (curr== list->tail) {
                curr->prev->next = NULL;
                list->tail = curr->prev;
            }
            else{
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            // free the node data with the free function the user send in the create linked list function
            list->freeElement(curr->data);
            // free the space we allocate to curr in create node
            free(curr);
            // Decreases by 1 the size of count elements
            list->count_elements = list->count_elements - 1;
            // if the list is empty, update head and tail to NULL
            if (list->count_elements == 0) {
                list->head = NULL;
                list->tail = NULL;
            }
            return success;
        }
        // update curr to the next node if he doesn't equal to the PrameterToEqual
        curr = curr->next;
    }
    return no_element;

}

/**
 * Displays the data of all nodes in the linked list.
 *
 * @param list The linked list to display.
 * @return success if the list was displayed, or Invalid_input if the list is NULL.
 */
status displayList(LinkedList list) {
    // check if the pointer the function gets equal to null
    if (list == NULL) {
        return Invalid_input;
    }
    // Hold the first node in the linked list in curr
    Node curr = list->head;
    // iterate on all the node in the linked list until curr equal to null (we end to iterate on the list)
    while (curr != NULL) {
        // print the current node's data by the print function the user send to Create linked list function
        list->printElement(curr->data);
        // update curr to the next node
        curr = curr->next;
    }
    return success;
}

/**
 * Retrieves the data from the node at the specified index in the list.
 *
 * @param list The linked list from which to retrieve the data.
 * @param index The index of the node to retrieve (1-based).
 * @return A copy of the data at the specified index by the copy function the user send
 * or NULL if the index is out of bounds or the list is NULL.
 */
Element getDataByIndex(LinkedList list, int index) {
    // check if the pointer the function gets equal to null and the valid of index value
    if (list == NULL|| index < 1 || index > list->count_elements) {
        return NULL;
    }
    // Hold the first node in the linked list in curr
    Node curr = list->head;
    // iterate on all the node in the linked list until get to the index that gets in the function
    for (int i = 1; i < index; i++) {
        curr = curr->next;
    }
    // copy the data of the index by the copy function the user send in create linked list
    Element copyData = list->copyElement(curr->data);
    // check if the copy success
    if (copyData == NULL) {
        return NULL;
    }
    return copyData;
}

/**
 * Returns the number of elements in the linked list.
 *
 * @param list The linked list.
 * @return The number of elements in the list, or -1 if the list is NULL.
 */
int getLengthList(LinkedList list) {
    // check if the pointer the function gets equal to null
    if (list == NULL) {
        return -1;
    }
    return list->count_elements;
}

/**
 * Searches for a node with the specified key in the linked list.
 *
 * @param list The linked list to search.
 * @param key The key to search for.
 * The user must provide an element or part of an element that matches
 * the criteria defined in the comparison function.
 * @return A copy of the data of the matching nodeby the copy function the user send or NULL if no match is found.
 */
Element searchByKeyInList(LinkedList list, Element key) {
    // check if the pointers the function gets equal to null
    if (list == NULL || key == NULL) {
        return NULL;
    }
    // Hold the first node in the linked list in curr
    Node curr = list->head;
    // iterate on all the node in the linked list until curr equal to null (we end to iterate on the list)
    while (curr != NULL) {
        // Check if the current node (or node's parameter to equal) equal to the key
        if (list->equal(curr->data, key)) {
            // copy the data of the index by the copy function the user send in create linked list
            Element copyData = list->copyElement(curr->data);
            // check if the copy success
            if (copyData == NULL) {
                return NULL;
            }
            return copyData;
        }
        // update curr to the next node if he doesn't equal to the key
        curr = curr->next;
    }
    return NULL;
}