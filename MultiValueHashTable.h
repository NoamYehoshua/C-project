#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H
#include "Defs.h"
/**
 * @file MultiValueHashTable.h
 * @brief Generic Abstract Data Type (ADT) for a Multi-Value Data Structure.
 *
 * This header defines the interface for a Multi-Value Table, which maps keys to multiple values.
 * Unlike a traditional hash table, the keys in this structure are not unique, allowing multiple
 * values to be associated with the same key.
 *
 * Key Features:
 * - Each key can store multiple values.
 * - The structure supports generic keys and values through user-provided functions for copying,
 *   freeing, printing, and comparison.
 * - It allows dynamic management of keys and their associated values while maintaining
 *   efficient operations.
 */


typedef struct MultiHashTable_s *multiHashTable;

/**
 * @brief Creates a new Multi-Value Table.
 *
 * Initializes a Multi-Value Table, allowing multiple values to be stored under the same key.
 * The user must provide functions for handling keys and values, ensuring flexibility for
 * different data types.
 *
 * @param copyKey Function to copy a key.
 * @param freeKey Function to free memory allocated for a key.
 * @param printKey Function to print a key.
 * @param copyValue Function to copy a value.
 * @param freeValue Function to free memory allocated for a value.
 * @param printValue Function to print a value.
 * @param equalKey Function to compare two keys.
 * @param equalVal Function to compare two values.
 * @param transformIntoNumber Function to transform a key into a number for indexing.
 * @param MultiHashNumber The number of slots in the table (hash range).
 * @return A pointer to the newly created Multi-Value Table, or NULL on failure.
 */
multiHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
    FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction equalVal, TransformIntoNumberFunction transformIntoNumber, int MultiHashNumber);

/**
 * @brief Destroys a Multi-Value Table.
 *
 * Frees all resources associated with the given Multi-Value Table, including all keys and values stored within.
 *
 * @param MultiHashTable The table to destroy.
 * @return `success` on successful destruction, or `Invalid_input` if the table is NULL.
 */
status destroyMultiValueHashTable(multiHashTable MultiHashTable);

/**
 * @brief Adds a key and value from the user to the Multi-Value Table.
 *
 * @param MultiHashTable The table to modify.
 * @param key The key to add.
 * @param value The value to associate with the key.
 * @return `success` on successful addition, or an appropriate error code on failure.
 */
status addToMultiValueHashTable(multiHashTable MultiHashTable, Element key, Element value);

/**
 * @brief Retrieves the list of values associated with a key.
 *
 * Searches the table for the given key and returns all the values associated with it (list of value's).
 *
 * @param MultiHashTable The table to search.
 * @param key The key to look up.
 * @return A pointer to the list of values, or NULL if the key does not exist.
 */
Element lookupInMultiValueHashTable(multiHashTable MultiHashTable, Element key);

/**
 * @brief Removes a specific value associated with a key.
 *
 * Deletes the specified value that associated with the given key.
 * If the value was the only value that associated with the given key, the key is also removed from the ADT.
 *
 * @param MultiHashTable The table to modify.
 * @param key The key whose value should be removed.
 * @param compareVal The value to remove.
 * @return `success` on successful removal, `no_element` if the key or value does not exist, or
 *         an appropriate error code on failure.
 */
status removeFromMultiValueHashTable(multiHashTable MultiHashTable,Element key,Element compareVal); //,EqualFunction equal);

/**
 * @brief Displays all values associated with a key.
 *
 * Prints the key and all its associated values using the user-provided print functions.
 *
 * @param MultiHashTable The table to query.
 * @param key The key whose values should be displayed.
 * @return `success` on successful display, or an appropriate error code on failure.
 */
status displayMultiValueHashElementsByKey(multiHashTable MultiHashTable,Element key);


#endif //MULTIVALUEHASHTABLE_H

