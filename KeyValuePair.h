#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H
#include "Defs.h"
/**
 * @file KeyValuePair.h
 * @brief Generic ADT for a key-value pair.
 *
 * This module defines a generic Key-Value Pair structure and provides
 * functions for creating, manipulating, and destroying key-value pairs.
 * It uses user-provided functions for copying, freeing, printing, and comparing
 * both the keys and values stored in the pair. The user is responsible for
 * managing memory of the copied elements returned by functions like `getKey`
 * and `getValue`, if the copy function he sent perform deep copies.
 */

/* Forward declaration for the KeyValuePair structure */
typedef struct KeyValuePair_s * KeyValuePair;

/**
 * @brief Creates a new KeyValuePair.
 *
 * This function creates a new key-value pair and assigns the specified functions for key and value operations.
 *
 * @param key The key for the key-value pair.
 * @param value The value for the key-value pair.
 * @param copyKey Function to copy the key element.
 * @param freeKey Function to free the key element.
 * @param printKey Function to print the key element.
 * @param copyValue Function to copy the value element.
 * @param freeValue Function to free the value element.
 * @param printValue Function to print the value element.
 * @param equalKey Function to compare keys for equality.
 *
 * @return A new `KeyValuePair` or NULL if memory allocation fails or any of the provided functions are NULL.
 *
 * @note The user must be responsible for cleaning up the allocated memory of the returned `Element` in functions like
 * `getKey` and `getValue` if a deep copy is performed.
 */
KeyValuePair createKeyValuePair(Element key,Element value,CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey);

/**
 * @brief Destroys a KeyValuePair.
 *
 * This function frees the memory allocated for both the key and the value of the key-value pair, as well as the
 * memory used by the `KeyValuePair` structure itself.
 *
 * @param kvPair The KeyValuePair to destroy.
 *
 * @return `success` if successful, `Invalid_input` if the input is NULL.
 *
 */
status destroyKeyValuePair(KeyValuePair kvPair);

/**
 * @brief Displays the value of the KeyValuePair.
 *
 * This function prints the value of the key-value pair using the `printValue` function.
 *
 * @param kvPair The KeyValuePair to display.
 *
 * @return `success` if successful, `Invalid_input` if the input is NULL.
 */
status displayValue(KeyValuePair kvPair);

/**
 * @brief Displays the key of the KeyValuePair.
 *
 * This function prints the key of the key-value pair using the `printKey` function.
 *
 * @param kvPair The KeyValuePair to display.
 *
 * @return `success` if successful, `Invalid_input` if the input is NULL.
 */
status displayKey(KeyValuePair kvPair);

/**
 * @brief Retrieves a copy of the value from the KeyValuePair.
 *
 * This function returns a deep copy of the value stored in the key-value pair.
 *
 * @param kvPair The KeyValuePair from which to retrieve the value.
 *
 * @return A copy of the value element, or NULL if the input is NULL.
 *
 * @note The user must clean up the memory for the returned value if a deep copy was made
 * (depend on the copy value function the user send in the creation).
 */
Element getValue(KeyValuePair kvPair);

/**
 * @brief Retrieves a copy of the key from the KeyValuePair.
 *
 * This function returns a deep copy of the key stored in the key-value pair.
 *
 * @param kvPair The KeyValuePair from which to retrieve the key.
 *
 * @return A copy of the key element, or NULL if the input is NULL.
 *
 * @note The user must clean up the memory for the returned key if a deep copy was made
 * (depend on the copy value function the user send in the creation).
 */
Element getKey(KeyValuePair kvPair);

/**
 * @brief Checks if the key of the KeyValuePair is equal to a given key.
 *
 * This function compares the key of the key-value pair with a provided key using the `equalKey` function.
 *
 * @param kvPair The KeyValuePair to compare.
 * @param key The key to compare against.
 *
 * @return `true` if the keys are equal, `false` otherwise, or if any input is NULL.
 */
bool isEqualKey(KeyValuePair kvPair, Element key);


#endif //KEYVALUEPAIR_H
