#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * @enum e_bool
 *
 * A boolean type that can have two values: false and true.
 */
typedef enum e_bool { false, true } bool;
/**
 * @enum e_status
 *
 * This enumeration defines status codes used for indicating the result
 * of operations in the system. These status codes are returned from
 * functions to signal the outcome or errors that occurred.
 */
typedef enum e_status {success, Memory_Problem, Invalid_input,no_PhyChar,planet_exist,fail,Phychar_exist,
    file_read_fail,planet_not_exist,jerry_not_exist, failure,no_element,element_exist,failure_reading} status;

/**
 * @typedef Element
 *
 * A void pointer to represent any type of data. It is used to store elements of various types in the generic ADT.
 */
typedef void * Element;

/**
 * @typedef CopyFunction
 *
 * A function pointer type that copies an element.
 *
 * @param element The element to be copied.
 * @return A pointer to the newly copied element.
 */
typedef Element(*CopyFunction) (Element);
/**
 * @typedef FreeFunction
 *
 * A function pointer type that frees an element.
 *
 * @param element The element to be freed.
 * @return The status of the operation.
 */
typedef status(*FreeFunction) (Element);
/**
 * @typedef PrintFunction
 *
 * A function pointer type that prints an element.
 *
 * @param element The element to be printed.
 * @return The status of the print operation.
 */
typedef status(*PrintFunction) (Element);
/**
 * @typedef TransformIntoNumberFunction
 *
 * A function pointer type that transforms an element into a number.
 *
 * @param element The element to be transformed.
 * @return The numeric representation of the element.
 */
typedef int(*TransformIntoNumberFunction) (Element);
/**
 * @typedef EqualFunction
 *
 * A function pointer type that compares two elements for equality.
 *
 * @param element1 The first element.
 * @param element2 The second element.
 * @return true if the elements are equal, false otherwise.
 */
typedef bool(*EqualFunction) (Element, Element);

#endif /* DEFS_H_ */
