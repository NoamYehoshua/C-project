/*   Jerry.h - Header file for the Jerry module
 *
 * This module defines structures and functions related to "Jerry" objects, which represent
 * space creatures with various characteristics. The module includes the definition of several
 * structs such as `StructPlanet`, `StructOrigin`, `StructPhysicalCharacteristics`, and `StructJerry`.
 * These structs are used to represent the planet, origin, physical characteristics, and unique properties
 * of a "Jerry" creature, respectively. In addition, the file contains function declarations for creating,
 * modifying, printing, and destroying Jerry objects, planets, and physical characteristics.
 */

#include <stdio.h>
#ifndef JERRY_H
#define JERRY_H
#include "Defs.h"

/**
 * @struct StructPlanet
 * @brief Represents a planet with a unique name and spatial coordinates.
 *
 * This structure defines a planet object with the following properties:
 *    name - A unique name represented as a string (char *).
 *    x,y,z- tree coordinates in space, represented as double values (double).
 *
 * Note:
 * The name of the planet is unique, and the planet's coordinates remain constant across all dimensions.
 */
typedef struct StructPlanet {
    char *name;
    double x;
    double y;
    double z;
} planet;

/**
 * @struct StructOrigin
 * @brief Represents the origin of a space creature, including its planet and dimension name.
 *
 * This structure defines an origin object with the following properties:
 *    planet - A pointer to a planet structure representing the planet of origin.
 *    name - A string (char *) representing the name of the dimension the creature comes from.
 */

typedef struct StructOrigin {
    planet * planet;
    char *name;
} origin;
/**
 * @struct StructPhysicalCharacteristics
 * @brief Represents a physical characteristic of a space creature.
 *
 * This structure defines a physical characteristic with the following properties:
 *    name  - A unique string (char *) representing the name of the characteristic.
 *    value - A double representing the numerical value of the characteristic.
 *
 * Note:
 * - The name of the characteristic is unique for a given jerry.
 */

typedef struct StructPhysicalCharacteristics{
    char *name;
    double value;

} PhyChar;

/**
 * @struct StructJerry
 * @brief Represents a specific Jerry with unique properties and attributes.
 *
 * This structure defines a Jerry with the following properties:
 *    happiness - An integer representing the happiness level of the Jerry (range: 1 to 100).
 *    ID - A unique identifier (char *) for the Jerry.
 *    origin - A pointer to an `origin` struct representing the Jerry's origin (planet and dimension).
 *    PhysicalChar - A dynamic array of pointers to `PhyChar` structures representing the physical characteristics of the Jerry.
 *    number_PhyChar - An integer representing the number of physical characteristics in the `PhysicalChar` array.
 *
 * Note:
 * - The ID is unique for each Jerry.
 * - The `PhysicalChar` array can grow dynamically to accommodate additional physical characteristics.
 */
typedef struct StructJerry {
    int happiness;
    char *ID;
    origin *origin;
    PhyChar **PhysicalChar;
    int number_PhyChar;
} jerry;


/**
 * @brief Creates a new Planet object and stores it in the provided pointer.
 *
 * This function initializes a new Planet object with the given parameters and
 * stores the created Planet in the provided pointer.
 *
 * @param name - A unique name for the Planet (char *).
 * @param x - The x-coordinate of the Planet in space (double).
 * @param y - The y-coordinate of the Planet in space (double).
 * @param z - The z-coordinate of the Planet in space (double).
 * @param plan - A double pointer to a Planet (planet **) that the user create and where the created Planet will be stored upon success.
 *
 * @return status   Indicates the success or failure of the operation: `success`,`Memory_Problem` or `Invalid_input` if invalid parameters were provided.
 */

status PlanetCreate(char * name, double x, double y, double z, planet ** plan);

/**
 * @brief Prints the details of a Planet object.
 *
 * This function prints the details of the Planet object, including the planet's name and its spatial coordinates
 * (x, y, z) in a format according to the defined fields of the Planet object.
 *
 * @param plan A pointer to the Planet object (planet *) whose details are to be printed.
 *
 * @return status Returns `success` if the Planet's details were printed successfully or status if printing failed - `Invalid_input`.
 *
 */
status PlanetPrint(planet * plan);



/**
 * @brief Destroys a planet and frees associated memory.
 *
 * This function releases all memory associated with a given planet. It frees the name of the planet,
 * and then frees the memory used for the planet object itself.
 *
 * @param plan A pointer to the planet (planet *) that is to be destroyed and whose memory is to be freed.
 *
 * @return status Returns `success` if the planet was successfully destroyed and memory was freed or status if printing failed - `Invalid_input`.
 */

status PlanetDestroy(planet * plan);


/**
 * @brief Creates a new Origin object and stores it in the provided pointer.
 *
 * This function initializes a new Origin object with the given parameters and stores the created object
 * in the provided pointer. It returns a status indicating whether the operation was successful or not.
 *
 * @param plan - A pointer to the planet (planet *) that represents the planet of origin.
 * @param name - The name of the dimension from which the origin is derived (char *).
 * @param orig  - A double pointer to an Origin (origin **) that the user create and where the created Origin will be stored upon success.
 *
 * @return status  Indicates the success or failure of the operation: `success`, `Memory_Problem` or `Invalid_input` if invalid parameters were provided.
 *
 */

status OriginCreate(planet * plan, char * name,origin ** orig);


/**
 * @brief Destroys an origin and frees associated memory.
 *
 * This function releases memory associated with a given origin. It frees the name of the origin,
 * and then frees the memory used for the origin object itself.
 *
 * @param orig A pointer to the origin (origin *) that is to be destroyed and whose memory is to be freed.
 *
 * @return status Returns `success` if the origin was successfully destroyed and memory was freed or status if printing failed - `Invalid_input`.
 *
 */
status OriginDestroy(origin * orig);


/**
 * @brief Creates a new Physical Characteristic object and stores it in the provided pointer.
 *
 * This function initializes a new Physical Characteristic (PhyChar) object with the given parameters
 * and stores the created object in the provided pointer. It returns a status indicating whether the
 * operation was successful or not.
 *
 * @param name - A name for the Physical Characteristic (char *).
 * @param value - The value of the Physical Characteristic (double).
 * @param phyChar - A double pointer to a Physical Characteristic (PhyChar **) that the user create and where the created
 *                  Physical Characteristic will be stored upon success.
 *
 * @return status  Indicates the success or failure of the operation: `success`, `Memory_Problem` or `Invalid_input`.

 */

status PhysicalCharCreate(char * name, double value, PhyChar ** phyChar);


/**
 * @brief Destroys a physical characteristic and frees associated memory.
 *
 * This function releases all memory associated with a given physical characteristic. It frees the name of the
 * physical characteristic and then frees the memory used for the physical characteristic itself.
 *
 * @param phyChar A pointer to the physical characteristic (PhyChar *) that is to be destroyed and whose memory is to be freed.
 *
 * @return status Returns `success` if the physical characteristic was successfully destroyed and memory was freed or status if printing failed - `Invalid_input`.
 *
 */
status PhysicalCharDestroy(PhyChar * phyChar);


/**
 * @brief Creates a new Jerry object and stores it in the provided pointer.
 *
 * This function initializes a new Jerry object with the given parameters and
 * stores the created Jerry in the provided pointer. It returns a status indicating
 * whether the operation was successful or not.
 *
 * @param ID - A unique identifier for the Jerry (char *).
 * @param happiness - An integer representing the Jerry's happiness level (1 to 100).
 * @param plan Pointer to the planet associated with the Jerry's origin.
 * @param origin_name Name of the origin associated with the Jerry.
 * @param jerr - A double pointer to a Jerry (jerry **) that the user create and where the created Jerry will be stored upon success.
 *
 * @return status   Indicates the success or failure of the operation: `success`, `Memory_Problem` or `Invalid_input`.
 */

status JerryCreate(char * ID, int happiness,  planet * plan, char * origin_name, jerry ** jerr);



/**
 * @brief Checks if a physical characteristic with the given name exists in the Jerry's list of physical characteristics.
 *
 * Searches for a physical characteristic by name. Returns true and provides a pointer to the matching characteristic
 * if found, otherwise returns false.
 *
 * @param jerr - A pointer to the Jerry object (jerry *) whose physical characteristics are to be checked.
 * @param name - The name of the physical characteristic to search for (char *).
 * @param phyChar  - A double pointer to a PhyChar (PhyChar **) where the pointer to the found physical characteristic
 *                   in the list of physical characteristics will be stored if found.
 *
 * @return status Returns `success` if found, otherwise `Invalid_input` or `no_PhyChar`.
 */

status PhysicalCharCheck(jerry * jerr, char * name,PhyChar ** phyChar);

/**
 * @brief Adds a physical characteristic to the Jerry's list of physical characteristics.
 *
 * This function attempts to add the provided physical characteristic to the list of characteristics
 * associated with the given Jerry object. If the characteristic is successfully added, the function returns `success`.
 *
 * @param jerr - A pointer to the Jerry object (jerry *) to which the physical characteristic is to be added.
 * @param phyChar - A pointer to the physical characteristic (PhyChar *) that is to be added to the Jerry's list.
 *
 * @return status Returns `success` if found, otherwise `Invalid_input` or `PhyChar_exist`
 *
 */

status PhysicalCharAdd(jerry * jerr, PhyChar * phyChar);

/**
 * @brief Removes a physical characteristic with the given name from the Jerry's list of physical characteristics.
 *
 * This function searches the list of physical characteristics in the Jerry object for a characteristic with the specified name.
 * If found, it removes the characteristic from the list. If the characteristic cannot be removed, appropriate error statuses are returned.
 *
 * @param jerr - A pointer to the Jerry object (jerry *) from which the physical characteristic is to be removed.
 * @param PhyName - The name of the physical characteristic to remove (char *).
 *
 * @return status  Returns `success` or an error status such as `no_PhyChar`, `Invalid_input`, or `Memory_Problem` if the operation fails.
 */

status PhysicalCharRemove(jerry * jerr, char * PhyName);
/**
 * @brief Prints the details of a Jerry object.
 *
 * This function prints the details of the Jerry object, including the Jerry's ID, happiness level,
 * origin planet's name, and the list of physical characteristics associated with the Jerry.
 *
 * @param jerr A pointer to the Jerry object (jerry *) whose details are to be printed.
 *
 * @return status Returns `success` if the Jerry's details were printed successfully or return `Invalid_input`.
 */
status JerryPrint(jerry * jerr);


/**
 * @brief Destroys a Jerry object and frees all associated memory.
 *
 * This function releases all memory associated with a given Jerry object. It frees the name of the Jerry,
 * destroys the origin of the Jerry using the `OriginDestroy` function, iterates through the array of physical characteristics,
 * destroys each physical characteristic using the `PhysicalCharDestroy` function, frees the memory for each physical characteristic,
 * and then frees the array of physical characteristics. Finally, it frees the memory allocated for the Jerry object itself.
 *
 * @param jerr A pointer to the Jerry object (jerry *) that is to be destroyed and whose memory is to be freed.
 *
 * @return status Returns `success` if the Jerry was successfully destroyed and memory was freed,or `Invalid_input`.
 */

status JerryDestroy(jerry * jerr);


#endif