#include "KeyValuePair.h"

/**
 * @struct KeyValuePair_s
 * @brief A struct representing a generic key-value pair.
 *
 * This struct is designed to hold a key-value pair, where both the key and value are of generic types (`Element`).
 * It also stores function pointers for copying, freeing, printing, and comparing both keys and values.
 * The key and value types are not predefined and can be any type that the user defines. This makes it a flexible
 * data structure for mapping any elements together.
 */
struct KeyValuePair_s {
    Element key;               // The key associated with the KetValuePair.
    Element value;             // The value associated with the KetValuePair.
    CopyFunction copyKey;      // Function pointer for copying a key.
    CopyFunction copyValue;    // Function pointer for copying a value.
    FreeFunction freeKey;      // Function pointer for freeing a key.
    FreeFunction freeValue;    // Function pointer for freeing a value.
    PrintFunction printKey;    // Function pointer for printing a key.
    PrintFunction printValue;  // Function pointer for printing a value.
    EqualFunction equalKey;    // Function pointer for comparing a key.
};

/**
 * @brief Creates a new KeyValuePair.
 *
 * This function allocates memory for a new `KeyValuePair` structure, copies the provided key and value using the
 * specified copy functions, and assigns the given function pointers to the appropriate fields in the struct.
 * If memory allocation for the key or value fails, the function frees any allocated memory before returning NULL.
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
 * @return A pointer to a newly created `KeyValuePair`, or NULL if any of the input functions are NULL or if memory
 * allocation fails.
 */
KeyValuePair createKeyValuePair(Element key,Element value,CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey) {
    // check if the pointers the function gets equal to null
    if (key == NULL || value == NULL || copyKey == NULL || freeKey == NULL || printKey == NULL || equalKey == NULL|| copyValue == NULL || freeValue == NULL || printValue == NULL) {
        return NULL;
    }
    // Allocate space for KeyValuePair
    KeyValuePair keyValPair = (KeyValuePair) malloc(sizeof(struct KeyValuePair_s));
    // Check if the allocate success.
    if (keyValPair == NULL) {
        return NULL;
    }
    // Initialize the key by copy the key we get from the user with the copyKey function he sends
    keyValPair->key = copyKey(key);
    // check if the copy success
    if (keyValPair->key == NULL) {
        free(keyValPair);
        return NULL;
    }
    // Initialize the value by copy the value we get from the user with the copyValue function he sends
    keyValPair->value = copyValue(value);
    // check if the copy success
    if (keyValPair->value == NULL) {
        freeKey(keyValPair->key);
        free(keyValPair);
        return NULL;
    }
    // Initialize KeyValuePair fields as defined in the struct, with the function the user send
    keyValPair->copyKey = copyKey;
    keyValPair->copyValue = copyValue;
    keyValPair->freeKey = freeKey;
    keyValPair->freeValue = freeValue;
    keyValPair->printKey = printKey;
    keyValPair->printValue = printValue;
    keyValPair->equalKey = equalKey;
    return keyValPair;
}

/**
 * @brief Destroys a KeyValuePair.
 *
 * Frees the allocated memory for the key and value using their respective free functions, then frees the memory for
 * the `KeyValuePair` struct itself.
 *
 * @param kvPair The KeyValuePair to destroy.
 *
 * @return `success` if successful, `Invalid_input` if the input is NULL.
 *
 */
status destroyKeyValuePair(KeyValuePair kvPair) {
    // check if the pointer the function gets equal to null
    if (kvPair == NULL) {
        return Invalid_input;
    }
    // free the key  with the freeKey function the user send in the create KeyValuePair function
    kvPair->freeKey(kvPair->key);
    // free the value with the freeValue function the user send in the create KeyValuePair function
    kvPair->freeValue(kvPair->value);
    // free the space we allocate to kvPair in create KeyValuePair function
    free(kvPair);
    return success;
}

/**
 * @brief Displays the value of the KeyValuePair.
 *
 * This function prints the value of the key-value pair using the `printValue` function,
 * which is provided during the creation of the KeyValuePair. If the KeyValuePair is NULL,
 * it returns `Invalid_input`.
 *
 * @param kvPair The KeyValuePair whose value is to be displayed.
 *
 * @return `success` if the value was successfully displayed,
 *         `Invalid_input` if the input KeyValuePair is NULL.
 */
status displayValue(KeyValuePair kvPair) {
    // check if the pointer the function gets equal to null
    if (kvPair == NULL) {
        return Invalid_input;
    }
    // print the KeyValuePair value by the print value function the user send to Create KeyValuePair function
    kvPair->printValue(kvPair->value);
    return success;
}

/**
 * @brief Displays the key of the KeyValuePair.
 *
 * This function prints the key of the key-value pair using the `printKey` function,
 * which is provided during the creation of the KeyValuePair. If the KeyValuePair is NULL,
 * it returns `Invalid_input`.
 *
 * @param kvPair The KeyValuePair whose key is to be displayed.
 *
 * @return `success` if the key was successfully displayed,
 *         `Invalid_input` if the input KeyValuePair is NULL.
 */
status displayKey(KeyValuePair kvPair) {
    // check if the pointer the function gets equal to null
    if (kvPair == NULL) {
        return Invalid_input;
    }
    // print the KeyValuePair key by the print key function the user send to Create KeyValuePair function
    kvPair->printKey(kvPair->key);
    return success;
}

/**
 * @brief Retrieves a copy of the value from the KeyValuePair.
 *
 * This function returns a copy of the value stored in the key-value pair using the
 * `copyValue` function provided during the creation of the KeyValuePair.
 * If the KeyValuePair is NULL, it returns NULL.
 *
 * @param kvPair The KeyValuePair from which to retrieve the value.
 *
 * @return A copy of the value element, or NULL if the input KeyValuePair is NULL.
 *
 * @note The user must clean up the memory for the returned value if a deep copy was made,
 * (depend on the copy value function the user send in the creation).
 */
Element getValue(KeyValuePair kvPair) {
    // check if the pointer the function gets equal to null
    if (kvPair == NULL) {
        return NULL;
    }
    // copy the value by the copy value function the user send in create KeyValuePair
    Element ValueCopy = kvPair->copyValue(kvPair->value);
    // check if the copy success
    if (ValueCopy == NULL) {
        return NULL;
    }
    return ValueCopy;
}

/**
 * @brief Retrieves a copy of the key from the KeyValuePair.
 *
 * This function returns a copy of the key stored in the key-value pair using the
 * `copyKey` function provided during the creation of the KeyValuePair.
 * If the KeyValuePair is NULL, it returns NULL.
 *
 * @param kvPair The KeyValuePair from which to retrieve the key.
 *
 * @return A copy of the key element, or NULL if the input KeyValuePair is NULL.
 *
 * @note The user must clean up the memory for the returned key if a deep copy was made,
 * (depend on the copy value function the user send in the creation).
 */
Element getKey(KeyValuePair kvPair) {
    // check if the pointer the function gets equal to null
    if (kvPair == NULL) {
        return NULL;
    }
    // copy the value by the copy value function the user send in create KeyValuePair
    Element KeyCopy = kvPair->copyKey(kvPair->key);
    // check if the copy success
    if (KeyCopy == NULL) {
        return NULL;
    }
    return KeyCopy;
}
/**
 * @brief Checks if the key of the KeyValuePair is equal to a given key.
 *
 * This function compares the key of the key-value pair with a provided key using the `equalKey` function,
 * which is provided during the creation of the KeyValuePair.
 * If either the `KeyValuePair` or the provided `key` is NULL, the function returns `false`.
 */
bool isEqualKey(KeyValuePair kvPair, Element key) {
    // check if the pointers the function gets equal to null
    if (kvPair == NULL || key == NULL) {
        return false;
    }
    // Check if the kvPair's key equal to the key the user send to the function
    if (kvPair->equalKey(kvPair->key, key) == true) {
        return true;
    }
    return false;
}