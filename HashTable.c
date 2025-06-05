#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
/*
 * This file implements a hash table using linked lists for collision handling.
 * The hash table is implemented with the concept of key-value pairs, where the key is unique for each entry.
 * The keys are hashed using a user-provided hash function that transforms the key into an integer, and the hash index is determined using the modulo operation based on the table size.
 * Each entry in the hash table is stored in a linked list, where each node contains a key-value pair.
 * Functions for adding, removing, looking up, and displaying elements are provided, along with memory management functions for key-value pairs.
 * The table is designed to handle collisions efficiently by chaining key-value pairs in separate lists at each hash index.
 * Each key is compared using a user-defined equality function to ensure uniqueness.
 * The hash table functions rely on user-supplied functions for copying, freeing, and printing keys and values.
 */


/**
 * @struct hashTable_s
 * @brief A generic hash table data structure for efficient key-value storage and retrieval.
 *
 * This struct represents a hash table designed to store generic keys and values. It supports
 * dynamic allocation and management of key-value pairs using user-provided functions for copying,
 * freeing, printing, and comparing keys and values. The hash table uses separate chaining with
 * linked lists to handle collisions.
 *
 * Fields:
 * - `table`: An array of pointers to linked lists, where each linked list stores key-value pairs
 *            that hash to the same index.
 * - `tableSize`: The number of buckets (slots) in the hash table.
 * - `numberOfElements`: The total number of elements (key-value pairs) stored in the table.
 * - `transIntoNumber`: A function pointer to transform a key into a numeric hash value.
 * - `copyKey`: A function pointer to create a copy of a key.
 * - `freeKey`: A function pointer to free the memory allocated for a key.
 * - `printKey`: A function pointer to print a key.
 * - `copyValue`: A function pointer to create a copy of a value.
 * - `freeValue`: A function pointer to free the memory allocated for a value.
 * - `printValue`: A function pointer to print a value.
 * - `equalKey`: A function pointer to compare two keys for equality.
 */
struct hashTable_s {
    LinkedList * table;
    int tableSize;
    int numberOfElements;
    TransformIntoNumberFunction transIntoNumber;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
};

/**
 * @brief Copies a KeyValuePair element.
 *
 * This function creates a shallow copy of the provided KeyValuePair element.
 * If the element is NULL it returns NULL.
 *
 * @param element The element to copy, assumed to be a KeyValuePair.
 *
 * @return A shallow copy of the KeyValuePair element, or NULL if the element is NULL.
 */
static Element copyKeyValuePairs(Element element) {
    // check if the pointer the function gets equal to null
    if (element == NULL) {
        return  NULL;
    }
    // casting to KeyValuePair
    KeyValuePair keyValuePair = (KeyValuePair) element;
    return (Element) keyValuePair;
}

/**
 * @brief Prints a KeyValuePair element.
 *
 * This function displays the key and value of the provided KeyValuePair element using the displayKey and displayValue functions from KeyValuePair.h.
 * If the element is NULL, it returns an Invalid_input.
 *
 * @param element The element to print, assumed to be a KeyValuePair.
 *
 * @return success if the element was printed successfully, Invalid_input if the element is NULL.
 */
static status PrintKeyValPair(Element element) {
    // check if the pointer the function gets equal to null
    if (element == NULL) {
        return Invalid_input;
    }
    // print the key and value by the display function from KeyValuePair.h
    displayKey((KeyValuePair) element);
    displayValue((KeyValuePair) element);
    return success;
}

/**
 * @brief Compares a KeyValuePair element with a key to check if they are equal.
 *
 * This function compares the key in the KeyValuePair element with the provided key using the isEqualKey function from KeyValuePair.h.
 * It returns true if they are equal, false otherwise.
 *
 * @param kvp The KeyValuePair element to compare.
 * @param key The key to compare with.
 *
 * @return true if the key in the KeyValuePair matches the provided key, false otherwise.
 */
static bool equalForInnerList(Element kvp, Element key) {
    // check if the pointer the function gets equal to null
    if (kvp == NULL || key == NULL) {
        return false;
    }
    // use isEqualKey function to equal the KeyValuePair key to a key that send by user
    bool staus = isEqualKey((KeyValuePair) kvp,key);
    if (staus == false) {
        return false;
    }
    return true;
}

/**
 * @brief Destroys a KeyValuePair element from the hash table.
 *
 * This function acts as a wrapper around `destroyKeyValuePair` to ensure that
 * the element is not NULL before attempting to destroy it. It validates the input
 * and calls the appropriate function to free the resources associated with the
 * KeyValuePair element.
 *
 * @param element A pointer to the element to be destroyed. This is expected to
 *        be a KeyValuePair cast to an `Element` type.
 * @return `success` if the element was destroyed successfully.
 *         `Invalid_input` if the input element is NULL or if `destroyKeyValuePair`
 *         returns an invalid status.
 */

static status destroyKeyValuePairhash(Element element) {
    // check if the pointer the function gets equal to null
    if (element == NULL) {
        return Invalid_input;
    }
    // free the KeyValuePair element and the data store in the element by destroyKeyValuePair function
    status freeStatus = destroyKeyValuePair((KeyValuePair) element);
    if (freeStatus ==Invalid_input) {
        return Invalid_input;
    }
    return success;
}
/**
 * @brief Creates a new hash table.
 *
 * This function creates a new hash table with the specified size. The table
 * uses a series of linked lists to handle hash collisions. The user must
 * provide functions for copying, freeing, printing, and comparing keys and values.
 *
 * @param copyKey Function for copying keys.
 * @param freeKey Function for freeing keys.
 * @param printKey Function for printing keys.
 * @param copyValue Function for copying values.
 * @param freeValue Function for freeing values.
 * @param printValue Function for printing values.
 * @param equalKey Function for comparing keys.
 * @param transformIntoNumber Function to transform keys into hash numbers.
 * @param hashNumber The desired size of the hash table.
 *
 * @return A pointer to the newly created hash table, or NULL if an error occurs.
 */
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
    PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    // check if the pointers the function gets equal to null
    if (copyKey == NULL|| freeKey == NULL|| printKey == NULL|| equalKey == NULL|| transformIntoNumber == NULL||
        copyValue == NULL|| freeValue == NULL|| printValue == NULL) {
            return NULL;
        }
    // Allocate space for hashTable
    hashTable HashTable =(hashTable) malloc(sizeof(struct hashTable_s));
    // Check if the allocate success.
    if (HashTable == NULL) {
        return NULL;
    }
    // Initialize hashTable fields as defined in the struct, with the function the user send
    HashTable->tableSize = hashNumber;
    HashTable->numberOfElements = 0;
    HashTable->transIntoNumber = transformIntoNumber;
    HashTable->copyKey = copyKey;
    HashTable->freeKey = freeKey;
    HashTable->printKey = printKey;
    HashTable->copyValue = copyValue;
    HashTable->freeValue = freeValue;
    HashTable->printValue = printValue;
    HashTable->equalKey = equalKey;
    // Allocate space for table - array of pointer to LinkedList with size of tableSize that get from the user
    HashTable->table = (LinkedList*) malloc((HashTable->tableSize)*sizeof(LinkedList));
    // Check if the allocate success.
    if ( HashTable->table == NULL) {
        // if failed, free the space that allocate for hashTable
        free(HashTable);
        return NULL;
    }
    // Initialize LinkedList in each cell in the array
    for (int i = 0; i < HashTable->tableSize; i++) {
        // create in each cell LinkedList by createLinkedList function, and send function for KeyValue Pair that will be the nodes in thr linked list and contain the function the user send to the hash table
        HashTable->table[i] = createLinkedList((CopyFunction)copyKeyValuePairs,destroyKeyValuePairhash,PrintKeyValPair,equalForInnerList);
        // check if the creation success
        if (HashTable->table[i] == NULL) {
            // if creation not success free the space that allocate for table and HashTable
            free(HashTable->table);
            free(HashTable);
            return NULL;
        }
    }
    return HashTable;
}

/**
 * @brief Destroys the hash table and frees associated memory.
 *
 * This function destroys the hash table, freeing the memory used by the
 * hash table itself and the elements inside the linked lists.
 *
 * @param HashTable The hash table to be destroyed.
 *
 * @return success if the table is destroyed successfully, Invalid_input if the table is NULL.
 */
status destroyHashTable(hashTable HashTable) {
    // check if the pointer the function gets equal to null
    if (HashTable==NULL) {
        return Invalid_input;
    }
    // run over all the linked list in table and free all the space that alloc for the linked list and the data in the linked list with destroyList function
    for (int i = 0; i < HashTable->tableSize; i++) {
        destroyList(HashTable->table[i]);
    }
    // free the space that allocate for table and HashTable
    free(HashTable->table);
    free(HashTable);
    return success;
}

/**
 * @brief Adds a key-value pair to the hash table.
 *
 * This function adds a new key-value pair to the hash table. If the key already exists,
 * the function does nothing. The key and value are copied into the table using the user
 * provided copy functions.
 *
 * @param HashTable The hash table to which the key-value pair will be added.
 * @param key The key to be added.
 * @param value The value to be added.
 *
 * @return success if the key-value pair is added successfully,
 *         element_exist if the key already exists in the table,
 *         Memory_Problem if there is an issue allocating memory,
 *         Invalid_input if any parameter is NULL.
 */
status addToHashTable(hashTable HashTable, Element key,Element value) {
    // check if the pointer the function gets equal to null
    if (HashTable==NULL || key==NULL || value==NULL) {
        return Invalid_input;
    }
    // converter the key to int by the function transIntoNumber
    int key_num = HashTable->transIntoNumber(key);
    // find the index by module the key_num with the size of the HashTable
    int index = key_num % (HashTable->tableSize);
    // check if  have element with the same key in the linked list at the index in HashTable
    Element result = searchByKeyInList(HashTable->table[index],key);
    if (result==NULL) {
        // create new keyValPair if not have element with the same key in the linked list
        KeyValuePair new_key_value_pair = createKeyValuePair(key,value, HashTable->copyKey, HashTable->freeKey,HashTable->printKey,HashTable->copyValue, HashTable->freeValue,HashTable->printValue,HashTable->equalKey);
        if (new_key_value_pair==NULL) {
            return Memory_Problem;
        }
        // add the key val pair to the linked list in the cell at the location of the index in the HashTable
        status appendResult = appendNode(HashTable->table[index],new_key_value_pair);
        if (appendResult == success) {
            return success;
        }
        else if (appendResult == Memory_Problem) {
            return Memory_Problem;
        }
        else {
            return Invalid_input;
        }
    }
    // if result not equal to NULL, have element with the same key
    return element_exist;
}

/**
 * @brief Looks up the value associated with a key in the hash table.
 *
 * This function calculates the hash index for the provided key and searches for it
 * in the corresponding linked list. If the key is found, it returns a copy of the value
 * associated with that key. If the key is not found or any parameter is NULL, it returns NULL.
 *
 * @param HashTable The hash table to search in.
 * @param key The key to look up.
 *
 * @return A copy of the value associated with the key if found, NULL if the key is not found or any parameter is NULL.
 *
 * @note The user must clean up the memory for the returned value if a deep copy was made
 * (depend on the copy value function the user send in the creation).
 */
Element lookupInHashTable(hashTable HashTable, Element key) {
    // check if the pointer the function gets equal to null
    if (HashTable==NULL || key==NULL) {
        return NULL;
    }
    // converter the key to int by the function transIntoNumber
    int key_num = HashTable->transIntoNumber(key);
    // find the index by module the key_num with the size of the HashTable
    int index = key_num % (HashTable->tableSize);
    // check if have element with the same key in the linked list at the index cell in HashTable
    Element element = searchByKeyInList(HashTable->table[index],key);
    if (element==NULL) {
        return NULL;
        }
    // casting to KeyValuePair
    element = (KeyValuePair) element;
    return (Element) getValue(element);

}

/**
 * @brief Removes a key-value pair from the hash table.
 *
 * This function removes the key-value pair associated with the specified key from the hash table.
 * If the key is not found, the function returns an error indicating that no element was found.
 *
 * @param HashTable The hash table from which the key-value pair will be removed.
 * @param key The key to be removed.
 *
 * @return success if the key-value pair is removed successfully,
 *         Invalid_input if any parameter is NULL,
 *         no_element if the key does not exist in the table.
 */
status removeFromHashTable(hashTable HashTable, Element key) {
    // check if the pointers the function gets equal to null
    if (HashTable==NULL || key==NULL) {
        return Invalid_input;
    }
    // converter the key to int by the function transIntoNumber
    int key_num = HashTable->transIntoNumber(key);
    // find the index by module the key_num with the size of the HashTable
    int index = key_num % (HashTable->tableSize);
    // delete the node with the key that send by the user
    status result = deleteNode(HashTable->table[index],key);
    if (result==no_element) {
        return no_element;
    }
    else if (result==Invalid_input) {
        return Invalid_input;
    }
    return success;
}

/**
 * @brief Displays all elements in the hash table.
 *
 * This function iterates through all the linked lists in the hash table and displays
 * each key-value pair by calling the appropriate display functions.
 *
 * @param HashTable The hash table whose elements will be displayed.
 *
 * @return success if the elements are displayed successfully, Invalid_input if the hash table is NULL.
 */
status displayHashElements(hashTable HashTable) {
    // check if the pointer the function gets equal to null
    if (HashTable==NULL) {
        return Invalid_input;
    }
    // Iterate through all the cells in the hashtable and print all the linked lists that are stored in the cells of the table
    for (int i = 0; i < HashTable->tableSize; i++) {
        displayList(HashTable->table[i]);
    }
    return success;
}