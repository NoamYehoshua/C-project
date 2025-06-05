#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
/**
 * @file MultiValueHashTable.c
 * @brief Implementation of a Multi-Value Hash Table using linked lists.
 *
 * This module implements a Multi-Value Hash Table, where each key is associated with
 * a linked list of values. Unlike a standard hash table, the keys in this implementation
 * are not unique, allowing the storage of multiple values for the same key.
 *
 * The Multi-Value Hash Table uses an array of linked lists, and each node in the linked
 * list represents a key-value pair. The key is stored as-is, and the value is a linked
 * list containing all the values inserted for that key. This design supports efficient
 * management of non-unique keys while maintaining fast lookup and insertion operations.
 */


/**
 * @struct MultiHashTable_s
 * @brief Represents a Multi-Value Hash Table.
 *
 * This structure encapsulates the data and functionality required for a Multi-Value
 * Hash Table. Each key in the hash table is associated with a linked list of values,
 * allowing for the storage of multiple values for the same key.
 *
 * Fields:
 * - `HashTable`: The underlying hash table used for storing key-value pairs.
 * - `transIntoNumber`: Function to transform keys into hash indices.
 * - `copyKey`: Function to copy keys.
 * - `freeKey`: Function to free memory allocated for keys.
 * - `printKey`: Function to print keys.
 * - `copyValue`: Function to copy values.
 * - `freeValue`: Function to free memory allocated for values.
 * - `printValue`: Function to print values.
 * - `equalKey`: Function to compare keys for equality.
 * - `equalVal`: Function to compare values for equality.
 */
struct MultiHashTable_s {
    hashTable HashTable;
    TransformIntoNumberFunction transIntoNumber;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    EqualFunction equalVal;
};

/**
 * @brief Copies a linked list value without modification.
 *
 * This function serves as a placeholder for copying linked list elements
 * when used in the Multi-Value Hash Table. It simply returns the element
 * as-is without performing any deep copy.
 *
 * @param element The element to copy.
 * @return The same element provided as input, or NULL if the input is NULL.
 */
static Element copyLinkListVal(Element element){
    // check if the pointer the function gets equal to null
    if (element == NULL) {
        return NULL;
    }
    // return element, shallow copy
    return element;
}

/**
 * @brief Creates a Multi-Value Hash Table.
 *
 * Initializes a new Multi-Value Hash Table with specified functions for copying, freeing,
 * printing, and comparing keys and values, as well as a hash function.
 *
 * @param copyKey Function to copy keys.
 * @param freeKey Function to free keys.
 * @param printKey Function to print keys.
 * @param copyValue Function to copy values.
 * @param freeValue Function to free values.
 * @param printValue Function to print values.
 * @param equalKey Function to compare keys.
 * @param equalVal Function to compare values.
 * @param transformIntoNumber Hash function to transform keys into hash indices.
 * @param MultiHashNumber Number of buckets in the hash table.
 * @return A pointer to the created Multi-Value Hash Table, or NULL if creation failed.
 */
multiHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
    FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction equalVal, TransformIntoNumberFunction transformIntoNumber, int MultiHashNumber) {
    // check if the pointers the function gets equal to null
    if (copyKey == NULL|| freeKey == NULL|| printKey == NULL|| equalKey == NULL|| transformIntoNumber == NULL||
        copyValue == NULL|| freeValue == NULL|| printValue == NULL|| equalVal==NULL) {
        return NULL;
        }
    // Allocate space for multiHashTable
    multiHashTable MultiHashTable = (multiHashTable) malloc(sizeof(struct MultiHashTable_s));
    // Check if the allocate success.
    if (MultiHashTable == NULL) {
        return NULL;
    }
    // create HashTable by createHashTable function, and send function for key (the function foe key the user send) and the function for value - function of linked list.
    MultiHashTable->HashTable = createHashTable(copyKey, freeKey, printKey, (CopyFunction) copyLinkListVal, (FreeFunction)destroyList, (PrintFunction) displayList, equalKey, transformIntoNumber, MultiHashNumber);
    // check if the creation success
    if (MultiHashTable->HashTable == NULL) {
        // if creation not success, free the space that allocate for multiHashTable
        free(MultiHashTable);
        return NULL;
    }
    // Initialize multiHashTable fields as defined in the struct, with the function the user send
    MultiHashTable->transIntoNumber = transformIntoNumber;
    MultiHashTable->copyKey = copyKey;
    MultiHashTable->freeKey = freeKey;
    MultiHashTable->printKey = printKey;
    MultiHashTable->copyValue = copyValue;
    MultiHashTable->freeValue = freeValue;
    MultiHashTable->printValue = printValue;
    MultiHashTable->equalKey = equalKey;
    MultiHashTable->equalVal = equalVal;
    return MultiHashTable;
}

/**
 * @brief Destroys a Multi-Value Hash Table.
 *
 * Frees all resources associated with the Multi-Value Hash Table, including the hash
 * table and all linked lists of values.
 *
 * @param MultiHashTable Pointer to the Multi-Value Hash Table to destroy.
 * @return `success` if the table was successfully destroyed, otherwise `Invalid_input`.
 */
status destroyMultiValueHashTable(multiHashTable MultiHashTable) {
    // check if the pointer the function gets equal to null
    if (MultiHashTable == NULL) {
        return Invalid_input;
    }
    // free the MultiHashTable->HashTable and all the data that store in MultiHashTable->HashTable by destroyHashTable function
    destroyHashTable(MultiHashTable->HashTable);
    // free the space that allocate for multiHashTable
    free(MultiHashTable);
    return success;
}

/**
 * @brief Adds a key-value pair to the Multi-Value Hash Table.
 *
 * Inserts a value into the linked list associated with the specified key. If the key
 * does not exist in the table, a new linked list is created for it.
 *
 * @param MultiHashTable Pointer to the Multi-Value Hash Table.
 * @param key The key to add.
 * @param value The value to add for the key.
 * @return `success` if the operation succeeded, `Memory_Problem` for memory issues or
 *         `Invalid_input` for invalid parameters.
 */
status addToMultiValueHashTable(multiHashTable MultiHashTable, Element key, Element value) {
    // check if the pointers the function gets equal to null
    if (MultiHashTable == NULL||key == NULL || value == NULL) {
        return Invalid_input;
    }
    // search if have Element in the MultiHashTable with key that equal to the key the user send to the function
    Element ValInKeyVal = lookupInHashTable(MultiHashTable->HashTable,key);
    // if dont have
    if (ValInKeyVal == NULL) {
        // create new linked list that store all the values of the same key
        LinkedList valuesLinkedList = createLinkedList(MultiHashTable->copyValue,MultiHashTable->freeValue,MultiHashTable->printValue,MultiHashTable->equalVal);
        if (valuesLinkedList == NULL) {
            return failure;
        }
        // add the value that the user send to the linked list
        status result = appendNode(valuesLinkedList,value);
        if (result == Memory_Problem) {
            // if failed, free the space that allocate for valuesLinkedList
            destroyList(valuesLinkedList);
            return Memory_Problem;
        }
        else if (result == Invalid_input) {
            // if failed, free the space that allocate for valuesLinkedList
            destroyList(valuesLinkedList);
            return Invalid_input;
        }
        // add to the hash table element with the key that the user send and value -linked list with the value the user send
        status addResult = addToHashTable(MultiHashTable->HashTable,key,(Element) valuesLinkedList);
        if (addResult == Memory_Problem) {
            // if failed, free the space that allocate for valuesLinkedList
            destroyList(valuesLinkedList);
            return Memory_Problem;
        }
        else if (addResult == Invalid_input) {
            // if failed, free the space that allocate for valuesLinkedList
            destroyList(valuesLinkedList);
        }
        return success;
    }
    // if ValInKeyVal not NULL, the key in the multi hash table and the key have linked list with values
    LinkedList link_to_add = ValInKeyVal;
    // add the value to the linked list
    status appedResult = appendNode(link_to_add,value);
    if (appedResult == Memory_Problem) {
        return Memory_Problem;
    }
    else if (appedResult == Invalid_input) {
        return Invalid_input;
    }
    return success;
}

/**
 * @brief Retrieves the list of values associated with a key.
 *
 * Searches the hash table for the specified key and returns the linked list of values
 * associated with it.
 *
 * @param MultiHashTable Pointer to the Multi-Value Hash Table.
 * @param key The key to search for.
 * @return A pointer to the linked list of values, or NULL if the key does not exist.
 */
Element lookupInMultiValueHashTable(multiHashTable MultiHashTable, Element key) {
    // check if the pointers the function gets equal to null
    if (MultiHashTable == NULL||key == NULL) {
        return NULL;
    }
    // search if have Element in the MultiHashTable with key that equal to the key the user send to the function
    Element ValInKeyVal = lookupInHashTable(MultiHashTable->HashTable,key);
    if (ValInKeyVal == NULL) {
        return NULL;
    }
    // return the linked list with the values of the key in the multi hash table
    LinkedList valuesLinkedList = ValInKeyVal;
    return (Element) valuesLinkedList;
}

/**
 * @brief Removes a specific value from the linked list of a key.
 *
 * Deletes the specified value from the linked list associated with the given key. If
 * the linked list of values becomes empty, the key is also removed from the hash table.
 *
 * @param MultiHashTable Pointer to the Multi-Value Hash Table.
 * @param key The key whose value is to be removed.
 * @param compareVal The value to remove.
 * @return `success` if the operation succeeded, `no_element` if the key or value does
 *         not exist, or `Invalid_input` for invalid parameters.
 */
status removeFromMultiValueHashTable(multiHashTable MultiHashTable,Element key,Element compareVal){
    // check if the pointers the function gets equal to null
    if (MultiHashTable == NULL||key == NULL || compareVal == NULL){
        return Invalid_input;
    }
    // search if have Element in the MultiHashTable with key that equal to the key the user send to the function
    Element ValInKeyVal = lookupInHashTable(MultiHashTable->HashTable,key);
    if (ValInKeyVal == NULL) {
        return no_element;
    }
    // casting to LinkedList
    LinkedList valuesLinkedList = ValInKeyVal;
    // search if the value in the linked list of values of the key the user send
    Element ValueEqual = searchByKeyInList(valuesLinkedList,compareVal);
    if (ValueEqual == NULL) {
        return no_element;
    }
    // delete the value from the linked list
    status deleteResult = deleteNode(valuesLinkedList,compareVal);
    if (deleteResult == Invalid_input) {
        return Invalid_input;
    }
    // if the linked list empty (length equal to zero), not have more values fo the key, then we remove the key from the hash table by removeFromHashTable function
    if (getLengthList(valuesLinkedList)==0) {
        status removeFromHash = removeFromHashTable(MultiHashTable->HashTable,key);
        if (removeFromHash == Invalid_input) {
            return Invalid_input;
        }
        return success;
    }
    return success;
}

/**
 * @brief Displays all values associated with a key.
 *
 * Prints the key and all its associated values using the user-defined print functions.
 *
 * @param MultiHashTable Pointer to the Multi-Value Hash Table.
 * @param key The key whose values are to be displayed.
 * @return `success` if the operation succeeded, `no_element` if the key does not exist,
 *         or `Invalid_input` for invalid parameters.
 */
status displayMultiValueHashElementsByKey(multiHashTable MultiHashTable,Element key) {
    // check if the pointers the function gets equal to null
    if (MultiHashTable == NULL||key == NULL) {
        return Invalid_input;
    }
    // search if have Element in the MultiHashTable with key that equal to the key the user send to the function
    Element ValInKeyVal = lookupInHashTable(MultiHashTable->HashTable,key);
    if (ValInKeyVal == NULL) {
        return no_element;
    }
    // print the key by the printKey fuction that the user send in MultiHashTable creation function
    MultiHashTable->printKey(key);
    LinkedList valuesLinkedList = ValInKeyVal;
    // print the linked list of values of the key by displayList function
    status printResult = displayList(valuesLinkedList);
    if (printResult==Invalid_input) {
        return Invalid_input;
    }
    return success;
}