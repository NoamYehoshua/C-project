/* Jerry.c - Implementation file for the Jerry module
 *
 * This file contains the implementation of various functions related to "Jerry" objects.
 * These functions include creating, modifying, printing, and destroying Jerry objects,
 * as well as managing the physical characteristics, origin, and associated planets.
 * The file also defines helper functions to add, remove, and check physical characteristics.
 * Functions return status values indicating success or failure for memory management and input validation.
 */

#include "Defs.h"
#include "Jerry.h"
#include <stdlib.h>
#include <string.h>


/**
 * @brief Creates a new Jerry object and stores it in the provided pointer.
 *
 * @param ID Unique ID for the Jerry.
 * @param happiness Happiness level of the Jerry.
 * @param plan Pointer to the planet associated with the Jerry's origin.
 * @param origin_name Name of the origin associated with the Jerry.
 * @param jerr Pointer to the Jerry object to be created and returned.
 *
 * @return status success if created, Memory_Problem if memory allocation fails, Invalid_input if invalid parameters.
 */
status JerryCreate(char * ID, int happiness, planet * plan, char * origin_name, jerry ** jerr) {
    // check if the pointers the function gets equal to null
    if (ID == NULL || plan == NULL|| jerr == NULL ||origin_name == NULL) {
        return Invalid_input;
    }
    // Allocate space for jerry and saves the address assigned in the pointer I received from the user
    (*jerr) = (jerry *) malloc(sizeof(jerry));
    // Check if the allocate success.
    if ((*jerr) == NULL) {
        return Memory_Problem;
    }
    // Check the length of the ID for the allocate
    int ID_len = strlen(ID);
    // Allocate space for jerry ID
    (*jerr) -> ID = (char *) malloc(sizeof (char) * (ID_len + 1));
    // Check if the allocate success.
    if ((*jerr) -> ID == NULL) {
        // Free jerry if the allocate of ID fail
        free((*jerr));
        return Memory_Problem;
    }
    // Initialize jerry ID
    strcpy((*jerr) -> ID , ID);
    // Create origin for jerry
    origin * orig = NULL;
    status create_origin = OriginCreate(plan, origin_name, &orig);
    // if origin create success
    if (create_origin == success) {
        // Initialize jerry origin
        (*jerr) -> origin = orig;
    }
    // if the function return Memory Problem we free the memory we allocate for current jerry and return Memory_Problem
    else if (create_origin == Memory_Problem) {
        free((*jerr) -> ID);
        free((*jerr));
        return Memory_Problem;
    }
    // if the function Invalid input Problem we free the memory we allocate for current jerry and return Invalid_input
    else {
        free((*jerr) -> ID);
        free((*jerr));
        return Invalid_input;
    }
    // Initialize jerry fields as defined in the struct
    (*jerr) -> happiness = happiness;
    (*jerr) -> PhysicalChar = NULL;
    (*jerr) ->number_PhyChar = 0;
    return success;
}

/**
 * @brief Creates a new Planet object and stores it in the provided pointer.
 *
 * @param name Name of the planet.
 * @param x X-coordinate of the planet.
 * @param y Y-coordinate of the planet.
 * @param z Z-coordinate of the planet.
 * @param plan Pointer to the planet send from the user to store and return.
 *
 * @return status success if created, Memory_Problem if memory allocation fails, Invalid_input if invalid parameters.
 */
status PlanetCreate(char * name, double x, double y, double z, planet ** plan) {
    // check if the pointers the function gets equal to null
    if (name == NULL||plan==NULL) {
        return Invalid_input;
    }
    // Allocate space for planet and saves the address assigned in the pointer I received from the user
    *(plan) = (planet *) malloc(sizeof(planet));
    // Check if the allocate success.
    if (*plan == NULL) {
        return Memory_Problem;
    }
    // Check the length of the name for allocate space
    int name_len = strlen(name);
    // Allocate space for planet name
    (*plan) -> name = (char *) malloc(sizeof (char) * (name_len + 1));
    // Check if the allocate success.
    if ((*plan) -> name == NULL) {
        // Free planet if the allocate of name fail
        free(*plan);
        return Memory_Problem;
    }
    // Initialize planet fields as defined in the struct
    strcpy((*plan) -> name , name);
    (*plan) -> x = x;
    (*plan) -> y = y;
    (*plan) -> z = z;
    return success;
}

/**
 * @brief Creates a new Physical Characteristic object and stores it in the provided pointer.
 *
 * @param name Name of the physical characteristic.
 * @param value Value of the physical characteristic.
 * @param phyChar Pointer to the physical characteristic send from the user to store and return.
 *
 * @return status success if created, Memory_Problem if memory allocation fails, Invalid_input if invalid parameters.
 */
status PhysicalCharCreate(char * name, double value, PhyChar ** phChar) {
    // check if the pointers the function gets equal to null
    if (name == NULL||phChar == NULL) {
        return Invalid_input;
    }
    // Allocate space for PhyChar and saves the address assigned in the pointer I received from the user
    (*phChar) = (PhyChar *) malloc(sizeof(PhyChar));
    // Check if the allocate success.
    if ((*phChar) == NULL) {
        return Memory_Problem;
    }
    // Check the length of the name for allocate space
    int name_len = strlen(name);
    // Allocate space for PhyChar name
    (*phChar) -> name = (char *) malloc(sizeof(char)*(name_len + 1));
    // Check if the allocate success.
    if ((*phChar) -> name == NULL) {
        // Free phChar if the allocate of name fail
        free((*phChar));
        return Memory_Problem;
    }
    // Initialize phChar fields as defined in the struct
    strcpy((*phChar) -> name, name);
    (*phChar) -> value = value;
    return success;
}

/**
 * @brief Creates a new Origin object and stores it in the provided pointer.
 *
 * @param plan Pointer to the planet representing the origin.
 * @param name Name of the origin.
 * @param orig Pointer to the origin send from the user to store and return.
 *
 * @return status success if created, Memory_Problem if memory allocation fails, Invalid_input if invalid parameters.
 */
status OriginCreate(planet * plan, char * name,origin ** orig) {
    // check if the pointers the function gets equal to null
    if (plan == NULL||name==NULL||orig==NULL) {
        return Invalid_input;
    }
    // Allocate space for origin and saves the address assigned in the pointer I received from the user
    (*orig) = (origin *) malloc(sizeof(origin));
    if ((*orig) == NULL) {
        return Memory_Problem;
    }
    // Initialize origin planet field
    (*orig)->planet = plan;
    // Check the length of the name for allocate space
    int name_len = strlen(name);
    // Allocate space for origin name
    (*orig) -> name = (char *) malloc(sizeof (char) * (name_len + 1));
    // Check if the allocate success.
    if ((*orig) -> name == NULL) {
        // Free origin if the allocate of name fail
        free((*orig));
        return Memory_Problem;
    }
    // Initialize origin name field
    strcpy((*orig) -> name , name);
    return success;
}

/**
 * @brief Checks if a physical characteristic with the given name exists in the Jerry's list.
 *
 * @param jerr Pointer to the Jerry.
 * @param name Name of the physical characteristic to check.
 * @param phyChar Pointer to the found physical characteristic for the user.
 *
 * @return status success if found, Invalid_input or no_PhyChar if not found.
 */
status PhysicalCharCheck(jerry * jerr, char * name,PhyChar ** phChar){
    // check if the pointers the function gets equal to null
    if (name == NULL || jerr == NULL||phChar == NULL) {
        return Invalid_input;
    }
    // check if not have physical characteristic for jerry
    if (jerr -> number_PhyChar == 0) {
        return no_PhyChar;
    }
    // check if the name we got equal to the name of one of the physical characteristic in the physical characteristic array of jerry
    for (int i=0 ; i < (jerr -> number_PhyChar); i++) {
        if (strcmp(name,(jerr -> PhysicalChar [i])->name) == 0) {
            *(phChar) = (jerr -> PhysicalChar [i]);
            return success;
        }
    }
    return no_PhyChar;
}

/**
 * @brief Adds a physical characteristic to the Jerry's list.
 *
 * @param jerr Pointer to the Jerry.
 * @param phyChar Pointer to the physical characteristic to add.
 *
 * @return status success if added, Phychar_exist if already exists, Memory_Problem if allocation fails.
 */
status PhysicalCharAdd(jerry * jerr, PhyChar * phChar) {
    // check if the pointers the function gets equal to null
    if (phChar == NULL || jerr == NULL) {
        return Invalid_input;
    }
    // create pointer for the PhysicalCharCheck function
    PhyChar *checkPhychar = NULL;
    // check if the physical characteristic exits in jerry before
    status statusResult = PhysicalCharCheck(jerr,phChar->name,&(checkPhychar));
    if (statusResult==success) {
        // if the physical characteristic exist in jerry we free the phChar that send to the function
        free(phChar->name);
        free(phChar);
        return Phychar_exist;
    }
    else if(statusResult==Invalid_input){
        return Invalid_input;
    }
    // if the physical characteristic (phChar) not exist in jerry
    else {
        // if not have physical characteristic for jerry
        if (jerr -> number_PhyChar == 0) {
            // Allocate space for the array of the physical characteristics of jerry
            jerr -> PhysicalChar = (PhyChar **) malloc(sizeof (PhyChar *));
            // Check if the allocate success.
            if (jerr -> PhysicalChar == NULL) {
                // Free phChar if the allocate fail
                free(phChar->name);
                free(phChar);
                return Memory_Problem;
            }
            // add one to the size of the array and add the physical characteristic (phChar) to the array in the last place
            jerr -> number_PhyChar = 1;
            jerr -> PhysicalChar[0] = phChar;
            return success;
        }
        //  have physical characteristic for jerry
        else {
            //  realloc tmp physical characteristics array and increase the existing space with another physical characteristics
            PhyChar **temp = (PhyChar **) realloc((jerr -> PhysicalChar), (jerr -> number_PhyChar + 1) * sizeof (PhyChar *));
            // Check if the allocate success.
            if (temp == NULL) {
                // Free phChar if the allocate fail
                free(phChar->name);
                free(phChar);
                return Memory_Problem;
            }
            // save PhysicalChar (jerry physical characteristics array) as temp
            jerr -> PhysicalChar = temp;
            // add one to the size of the array and add the physical characteristic (phChar) to the array in the last place
            jerr -> number_PhyChar = (jerr -> number_PhyChar)+ 1;
            jerr -> PhysicalChar[(jerr -> number_PhyChar)-1] = phChar;
            return success;
        }
    }
}

/**
 * @brief Removes a physical characteristic from the Jerry's list.
 *
 * @param jerr Pointer to the Jerry.
 * @param PhyName Name of the physical characteristic to remove.
 *
 * @return status success if removed, no_PhyChar if not found, Memory_Problem if allocation fails.
 */
status PhysicalCharRemove(jerry * jerr, char * PhyName) {
    // check if the pointers the function gets equal to null
    if (jerr == NULL || PhyName == NULL) {
        return Invalid_input;
    }
    // if not have physical characteristic for jerry
    if (jerr -> number_PhyChar == 0) {
        return no_PhyChar;
    }
    // create pointer for the PhysicalCharCheck function
    PhyChar *check_phy = NULL;
    // check if the physical characteristic exits in jerry before
    status result = PhysicalCharCheck(jerr,PhyName,&check_phy);
    if (result == no_PhyChar) {
        return no_PhyChar;
    }
    else if (result == success) {
        // physical characteristic exits in jerry before
        // free thr physical characteristic that we get from PhysicalCharCheck function by the pointer we send
        free(check_phy->name);
        free(check_phy);
        bool found = false;
        int i=0;
        // search the physical characteristic that free in the array by her adrees
        while (found == false) {
            if (jerr ->PhysicalChar[i] == check_phy){
                // move all the physical characteristic that exist after the physical characteristic we free one place left in the array
                for (int j = i+1 ; j < jerr -> number_PhyChar; j++) {
                    jerr ->PhysicalChar[j-1] = jerr ->PhysicalChar[j];
                }
                found = true;
                //Reduce the size of an array by one.
                jerr -> number_PhyChar = (jerr -> number_PhyChar) - 1;
            }
            else {
                i++;
            }
        }
        // if after the reduce, the number of physical characteristic in the array is zero, we free the array and initialize PhysicalChar array to null
        if (jerr -> number_PhyChar == 0) {
            free(jerr -> PhysicalChar);
            jerr -> PhysicalChar = NULL;
            return success;
        }
        else {
            // realloc tmp physical characteristics array and reduce the existing space by one physical characteristics
            PhyChar ** tmp = (PhyChar **) realloc(jerr -> PhysicalChar,(jerr -> number_PhyChar)*sizeof(PhyChar *));
            if (tmp == NULL) {
                return Memory_Problem;
            }
            // save PhysicalChar (jerry physical characteristics array) as temp
            jerr -> PhysicalChar = tmp;
            return success;
        }
    }
    else {
        return Invalid_input;
    }
}

/**
 * @brief Prints the details of a Jerry object.
 *
 * @param jerr Pointer to the Jerry to print.
 *
 * @return status success if printed, Invalid_input if input is invalid.
 */
status JerryPrint(jerry * jerr) {
    // check if the pointer the function gets equal to null
    if (jerr == NULL) {
        return Invalid_input;
    }
    // print Jerry's ID, Happiness, orgin and planet by format.
    printf("Jerry , ID - %s : \n",jerr ->ID);
    printf("Happiness level : %d \n",jerr ->happiness);
    printf("Origin : %s \n",(jerr ->origin)->name);
    PlanetPrint((jerr ->origin)->planet);
    // if jerry have physical characteristics, print the physical characteristics by format.
    if (jerr -> number_PhyChar != 0) {
        printf("Jerry's physical Characteristics available : \n");
        for (int i = 0; i< (jerr -> number_PhyChar); i++) {
            if (jerr -> number_PhyChar ==1) {
                printf("\t%s : %.2f \n",(*(jerr -> PhysicalChar))->name,(*(jerr -> PhysicalChar))->value);
                return success;
            }
            else {
                if (i==0) {
                    printf("\t%s : %.2f , ",(jerr -> PhysicalChar)[i]->name,(jerr -> PhysicalChar)[i]->value);
                }
                else if (i==(jerr -> number_PhyChar)-1){
                    printf("%s : %.2f \n",(jerr -> PhysicalChar)[i]->name,(jerr -> PhysicalChar)[i]->value);
                    return success;
                    }
                else {
                        printf("%s : %.2f , ",(jerr -> PhysicalChar)[i]->name,(jerr -> PhysicalChar)[i]->value);
                    }
                }
            }
        }
    return success;
}

/**
 * @brief Prints the details of a Planet object.
 *
 * @param plan Pointer to the planet to print.
 *
 * @return status success if printed, Invalid_input if input is invalid.
 */
status PlanetPrint(planet * plan) {
    // check if the pointer the function gets equal to null
    if (plan == NULL) {
        return Invalid_input;
    }
    // print planet's name and x,y,z coordinates by format.
    printf("Planet : %s (%.2f,%.2f,%.2f) \n", plan->name,plan->x,plan->y,plan->z);
    return success;
}

/**
 * @brief Destroys a Jerry object and frees all associated memory.
 *
 * @param jerr Pointer to the Jerry to destroy.
 *
 * @return status success if destroyed, Invalid_input if input is invalid.
 */
status JerryDestroy(jerry * jerr) {
    // check if the pointer the function gets equal to null
    if (jerr == NULL) {
        return Invalid_input;
    }
    // if jerry have physical characteristics free all the physical characteristics in 'PhysicalChar' (physical characteristics array) by PhysicalCharDestroy and then free 'PhysicalChar'
    if (jerr -> number_PhyChar != 0) {
        for (int i = 0 ; i< (jerr -> number_PhyChar); i++) {
            PhysicalCharDestroy(jerr ->PhysicalChar[i]);
        }
        free(jerr -> PhysicalChar);
    }
    // free jerry ID, free jerry origin by OriginDestroy function and finally free jerry
    free(jerr -> ID);
    OriginDestroy(jerr ->origin);
    free(jerr);
    return success;
 }

/**
 * @brief Destroys a planet and frees associated memory.
 *
 * @param plan Pointer to the planet to destroy.
 *
 * @return status success if destroyed, Invalid_input if input is invalid.
 */
status PlanetDestroy(planet * plan) {
    // check if the pointer the function gets equal to null
    if (plan == NULL) {
        return Invalid_input;
    }
    // free planet name and planet
    free(plan->name);
    free(plan);
    return success;
}

/**
 * @brief Destroys an origin and frees associated memory.
 *
 * @param orig Pointer to the origin to destroy.
 *
 * @return status success if destroyed, Invalid_input if input is invalid.
 */
status OriginDestroy(origin * orig) {
    // check if the pointer the function gets equal to null
    if (orig == NULL) {
        return Invalid_input;
    }
    // free origin name and origin
    free(orig->name);
    free(orig);
    return success;
}

/**
 * @brief Destroys a physical characteristic and frees associated memory.
 *
 * @param phyChar Pointer to the physical characteristic to destroy.
 *
 * @return status success if destroyed, Invalid_input if input is invalid.
 */
status PhysicalCharDestroy(PhyChar * phChar) {
    // check if the pointer the function gets equal to null
    if (phChar == NULL) {
        return Invalid_input;
    }
    // free phChar (physical characteristics) name and phChar
    free(phChar -> name);
    free(phChar);
    return success;
}
