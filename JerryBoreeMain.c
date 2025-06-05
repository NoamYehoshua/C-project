#include <stdio.h>
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include "Jerry.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include <math.h>
#include <ctype.h>


/**
 * @brief Frees memory allocated for an array of planets and their individual elements.
 *
 * This function iterates through the array of planets, destroys each planet using the
 * `PlanetDestroy` function, and then frees the array itself. If the array is empty,
 * only the array is freed.
 *
 * @param planets Pointer to the array of planets.
 * @param planets_size The size of the array (number of planets).
 *
 * @return `success` if the operation completes successfully.
 *         `Invalid_input` if the input pointer is NULL.
 *
 */
status DestroyPlanets(planet*** planets,int planets_size) {
    // check if the pointer the function gets equal to null
    if(planets ==NULL ) {
        return Invalid_input;
    }
    // if no planets in planets array, we free the array
    if (planets_size==0) {
        free(*planets);
    }
    // have planets in planets array, we free each planet in the array by PlanetDestroy function and then free the array
    else {
        for (int i=0;i<planets_size;i++) {
            PlanetDestroy((*planets)[i]);
        }
        free(*planets);
    }
    return success;
}

/**
 * @brief Cleans up and frees all allocated resources in the system.
 *
 * This function deallocates memory and destroys data structures including:
 * - The multi-hash table for physical characteristics.
 * - The hash table for Jerry objects.
 * - The linked list of Jerry objects.
 * - The array of planets.
 *
 * @param JerriesList Pointer to the linked list of Jerry objects.
 * @param planets Pointer to the array of planets.
 * @param JerriesHash Pointer to the hash table of Jerry objects.
 * @param PhycharMultiHash Pointer to the multi-hash table for physical characteristics.
 * @param planets_size The size of the array of planets.
 *
 * @return `success` if all resources are successfully cleaned up.
 *         `Invalid_input` if any of the input pointers are NULL or invalid.
 *
 * @note
 * - The function ensures proper destruction by calling the appropriate destruction functions
 *   (`destroyHashTable`, `destroyMultiValueHashTable`, `destroyList`, and `DestroyPlanets`).
 * - If the user has used getter functions on the data structures, and these data structures
 *   were initialized with deep copy functions, it is the user's responsibility to free any
 *   copied data retrieved by those getters. The `CleanUp` function cleans only the data stored
 *   inside the data structures themselves and not external copies.
 */
status CleanUp(LinkedList * JerriesList,planet*** planets,hashTable* JerriesHash, multiHashTable* PhycharMultiHash,int planets_size) {
    // check if the pointers the function gets equal to null
    if (JerriesList==NULL || JerriesHash==NULL || PhycharMultiHash==NULL) {
        return Invalid_input;
    }
    // free PhycharMultiHash multi hashtable, and all the data store in the multi hashtable by destroyMultiValueHashTable function
    status DestroyMulti = destroyMultiValueHashTable(*PhycharMultiHash);
    if (DestroyMulti==Invalid_input) {
        return Invalid_input;
    }
    // free JerriesHash hashtable, and all the data store in the hashtable by destroyHashTable function
    status DestroyHash = destroyHashTable(*JerriesHash);
    if (DestroyHash==Invalid_input) {
        return Invalid_input;
    }
    // check that JerriesList exist
    if (getLengthList(*JerriesList)==-1) {
        return Invalid_input;
    }
    // free JerriesList Linked List, and all the data store in the Linked List by destroyList function
    status DestroyList = destroyList(*JerriesList);
    if (DestroyList==Invalid_input) {
        return Invalid_input;
    }
    // free planets array, and all the data store in the array by DestroyPlanets function
    status DestroyPlanet = DestroyPlanets(planets,planets_size);
    if (DestroyPlanet==Invalid_input) {
        return Invalid_input;
    }
    return success;

}

/**
 * @brief Performs a shallow copy of the given element.
 * This function returns the same pointer without duplicating the data.
 * @param element Pointer to the element to be copied.
 * @return Pointer to the same element if it is not NULL; otherwise, NULL.
 */

Element ShallowCopy(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return NULL;
    }
    // return the element without change, shallow copy
    return element;
}
/**
 * @brief Frees the memory allocated for a Jerry object in a linked list.
 * This function destroys the given Jerry object using the `JerryDestroy` function.
 * @param element Pointer to the Jerry object to be freed.
 * @return `success` if the Jerry object was successfully destroyed;
 *         `Invalid_input` if the element is NULL or destruction fails.
 */
status FreeJerryInLink(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return Invalid_input;
    }
    // free jerry element and all the data store in jerry by JerryDestroy function
    status destroyJerry = JerryDestroy((jerry *)element);
    if (destroyJerry==Invalid_input) {
        return Invalid_input;
    }
    return success;
}
/**
 * @brief Prints the details of a Jerry object.
 * Uses the `JerryPrint` function to display the object's details.
 * @param element Pointer to the Jerry object to be printed.
 * @return `success` if the object is successfully printed;
 *         `Invalid_input` if the element is NULL or printing fails.
 */
status PrintJerry(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return Invalid_input;
    }
    // print jerry by JerryPrint function
    status printJerr = JerryPrint((jerry *)element);
    if (printJerr==Invalid_input) {
        return Invalid_input;
    }
    return success;
}

/**
 * @brief Compares a Jerry object with a key by ID.
 * This function checks if the ID of the given Jerry object matches the provided key.
 * @param jerr Pointer to the Jerry object.
 * @param key Key to compare with the Jerry's ID.
 *
 * @return `true` if the ID matches the key; `false` otherwise or if either parameter is NULL.
 */
bool EqualJerryInLink(Element jerr,Element key) {
    // check if the pointers the function gets equal to null
    if (jerr==NULL||key==NULL) {
        return false;
    }
    // check if jerry's ID equal to the key the user send
    if(strcmp( ((jerry *)jerr)->ID,key)==0){
        return true;
    }
    return false;
}
/**
 * @brief Creates a deep copy of a string key.
 * Allocates memory and copies the content of the given string.
 * @param element Pointer to the string to be copied.
 *
 * @return Pointer to the newly allocated copy of the string;
 *         NULL if allocation fails or the input is NULL.
 */
Element CopyKeyString(Element element) {
    // check if the pointers the function gets equal to null
    if (element==NULL) {
        return NULL;
    }
    // allocate space for the new pointer to char. the space size is the str length of element that send.
    char * CharCopy = (char *)malloc((strlen((char*)element)+1)*sizeof(char));
    // check if allocate success
    if (CharCopy==NULL) {
        return NULL;
    }
    // copy the element to CharCopy
    strcpy(CharCopy,(char*)element);
    // return deep copy
    return CharCopy;
}

/**
 * @brief Frees memory allocated for a string key.
 * @param element Pointer to the string key to be freed.
 *
 * @return `success` if the key is successfully freed; `Invalid_input` if the element is NULL.
 */

status FreeKeyString(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return Invalid_input;
    }
    // free the space that allocate to the element
    free(element);
    return success;
}

/**
 * @brief Prints a string key.
 * @param element Pointer to the string key to be printed.
 *
 * @return `success` if the key is successfully printed; `Invalid_input` if the element is NULL.
 */
status PrintKeyString(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return Invalid_input;
    }
    // print the element that is type is pointer to char
    printf("%s\n",(char*)element);
    return success;
}
/**
 * @brief Prints a string key along with a colon for multi-hash table entries.
 * @param element Pointer to the string key to be printed.
 *
 * @return `success` if the key is successfully printed; `Invalid_input` if the element is NULL.
 */

status PrintKeyStringPhyMulti(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return Invalid_input;
    }
    // print the element that is type is pointer to char with colon
    printf("%s : \n",(char*)element);
    return success;
}

/**
 * @brief Compares two string keys for equality.
 *
 * @param keyStr Pointer to the first string key.
 * @param StrToEqual Pointer to the second string key to compare.
 *
 * @return `true` if the keys are equal; `false` otherwise or if either parameter is NULL.
 */
bool EqualKeyString(Element keyStr,Element StrToEqual) {
    // check if the pointers the function gets equal to null
    if (keyStr==NULL||StrToEqual==NULL) {
        return false;
    }
    // check if the two pointer to char equal by strcmp function
    if (strcmp(keyStr,StrToEqual)==0) {
        return true;
    }
    return false;
}

/**
 * @brief A placeholder function for freeing elements.
 *
 * This function does nothing but returns success, used where freeing is not required.
 *
 * @param element Pointer to the element.
 *
 * @return `success` always, unless the element is NULL, in which case `Invalid_input`.
 */
status ShallowFree(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return Invalid_input;
    }
    // return success, shallow free
    return success;
}

/**
 * @brief Transforms a string into an integer based on the sum of its ASCII values.
 *
 * This function computes the sum of ASCII values of all characters in the string.
 *
 * @param element Pointer to the string to be transformed.
 *
 * @return The computed integer value; -1 if the element is NULL.
 */

int transStrToInt(Element element) {
    // check if the pointer the function gets equal to null
    if (element==NULL) {
        return -1;
    }
    // casting to char *
    char* str = (char *) element;
    // Initialize counter for the ASCII values of the char in str.
    int AsciiCounter = 0;
    // count all the ASCII values of the char in str in the AsciiCounter
    for (int i=0; i<strlen(str); i++) {
        AsciiCounter += (int) str[i];
    }
    // return the AsciiCounter
    return AsciiCounter;
}

/**
 * @brief Determines if a given number is a prime number.
 *
 * Checks whether the provided integer `number` is a prime. A prime number
 * is a number greater than 1 that is divisible only by 1 and itself.
 * The function efficiently tests divisors only up to the square root
 * of the number, as larger factors would already have smaller complements.
 *
 * @param number The integer to check.
 *
 * @return `true` if the number is prime; `false` otherwise.
 *
 * @details
 * A non-prime number must have at least one factor smaller than or equal to `sqrt(N)`, as larger factors would have smaller complements.
 * For example, for `N = 36`, factors are `1, 2, 3, 4, 6, 9, 12, 18, 36`.
 * Beyond `sqrt(36) = 6`, factors like `9` and `12` are complementary to those below `6`.
 */

bool CheckPrimeNumber(int number) {
    // if number is smaller or equal to 1 return false
    if (number<=1) {
        return false;
    }
    // if the number equal to 2 return true
    if (number==2) {return true;}
    // We will go through all the numbers from 1 to the root of the number and see if the number is divisible by them. If so then it is not prime.
    for (int i = 2; i <= sqrt(number) ;i++) {
        if (number%i==0) {
            return false;
        }
    }
    return true;
}
/**
 * @brief Finds the next prime number greater than the given number.
 * if the number is smaller than 13 we will return 13.
 * 13 is a prime number and, not small like the prime number 2 or 3,
 * so he can be the default prime number for numbers that smaller than 13.
 *
 * @param number The starting number to search from.
 *
 * @return The next prime number greater than the input number.
 */

int FindBiggerPrimeNumber(int number) {
    // if number smaller the 13, return 13
    if (number<13) {
        return 13;
    }
    int i =number;
    bool isPrime = false;
    // if number bigger than 13, we increase i by 1 and sent i to CheckPrimeNumber function until we find the next prime number that bigger than 'number' and return him
    while (!isPrime) {
        i++;
        isPrime = CheckPrimeNumber(i);
    }
    return i;
}


/**
 * @brief Initializes and populates a hash table for Jerry objects based on their IDs.
 *
 * This function creates a hash table using a prime number as the size,
 * determined by the smallest prime number greater than the number of Jerries
 * If no Jerries exist, the system uses the number of planets to find the next prime.
 * if the number of jerries or planets smaller than 13 the number that return is 13 (default small prime number).
 * It then iterates through the linked list of Jerries and adds them to the hash table.
 *
 * @param Jerries Pointer to the linked list of Jerry objects.
 * @param JerriesHash Pointer to the hash table to be created.
 * @param planetsize The size of the planets array (used for determining hash table size).
 *
 * @return `success` if the hash table is successfully created and populated.
 *         `Memory_Problem` if memory allocation fails during the process.
 *         `Invalid_input` if the input pointers are NULL or if duplicate elements are encountered.
 *
 * @note The following functions are passed to the hash table:
 *       - `CopyKeyString` for deep copying string keys.
 *       - `FreeKeyString` for freeing string keys.
 *       - `PrintKeyString` for printing string keys.
 *       - `ShallowCopy` for copying Jerry objects.
 *       - `ShallowFree` for handling Jerry objects (as no deep free is required).
 *       - `PrintJerry` for printing Jerry objects.
 *       - `EqualKeyString` for comparing string keys.
 *       - `transStrToInt` for hashing string keys into integers.
 */
status CreateJerryHash(LinkedList* Jerries,hashTable* JerriesHash,int planetsize) {
    // check if the pointers the function gets equal to null
    if (Jerries==NULL||JerriesHash==NULL) {
        return Invalid_input;
    }
    int HashSizePrimeNum;
    // if the number of Jerries LinkedList is equal to 0, find the Prime Number by planets size.
    if (getLengthList(*Jerries)==0) {
        HashSizePrimeNum = FindBiggerPrimeNumber(planetsize);
    }
    else {
        // if the number of Jerries LinkedList is bigger than 0, find the Prime Number by Jerries size.
        HashSizePrimeNum = FindBiggerPrimeNumber(getLengthList(*Jerries));
    }
    // create HashTable by createHashTable function, and send the function for key (string) and value (jerry) and transStrToInt function
    (*JerriesHash) = createHashTable(CopyKeyString,FreeKeyString,PrintKeyString,ShallowCopy,ShallowFree,PrintJerry,EqualKeyString,transStrToInt,HashSizePrimeNum);
    // check if the creation success
    if ((*JerriesHash)==NULL) {
        return Memory_Problem;
    }
    jerry * jerryToAdd;
    // add all the jerries in the linked list to the hash table
    for (int i = 1; i <= getLengthList(*Jerries); i++) {
        jerryToAdd =(jerry*) getDataByIndex((*Jerries),i);
        if (jerryToAdd==NULL) {
            return Invalid_input;
        }
        // key is Jerry's ID and value id jerry struct element
        status addHash = addToHashTable((*JerriesHash), (Element) jerryToAdd->ID,(Element) jerryToAdd);
        if (addHash==Memory_Problem) {
            // if the add fail free the HashTable and the data that store in the HashTable by destroyHashTable function
            destroyHashTable((*JerriesHash));
            return Memory_Problem;
        }
        else if (addHash==Invalid_input) {
            return Invalid_input;
        }
        else if (addHash==element_exist) {
            return Invalid_input;
        }
    }
    return success;
}

/**
 * @brief Counts the total number of physical characteristics across all Jerries.
 *
 * Iterates through the linked list of Jerries and sums up their physical characteristics.
 *
 * @param Jerries Pointer to the linked list of Jerries.
 *
 * @return The total count of physical characteristics;
 *         0 if the list is NULL or empty; `Invalid_input` if an error occurs.
 */

int PhyCharCounter(LinkedList* Jerries) {
    // check if the pointers the function gets equal to null
    if (Jerries==NULL) {
        return 0;
    }
    // Initialize counter for count the Physical Characteristic of all the jerries in Jerries LinkedList
    int count = 0;
    jerry * jerryToCount;
    // for each jerry in Jerries sum the number_PhyChar in count
    for (int i = 1; i <= getLengthList(*Jerries); i++) {
        jerryToCount =(jerry*) getDataByIndex((*Jerries),i);
        if (jerryToCount==NULL) {
            return Invalid_input;
        }
        count += jerryToCount->number_PhyChar;
    }
    return count;
}
/**
 * @brief Initializes and populates a multi-hash table for Jerry objects based on their physical characteristics.
 *
 * This function creates a multi-hash table using a prime number as the size,
 * Determined by the smallest prime number greater than the number of physical characteristics.
 * If no characteristics exist, determined by the smallest prime number greater than the number of Jerries is used.
 * If no Jerries exist, determined by the smallest prime number greater than the number of planets is used.
 * if the number of jerries's physical characteristics or jerries or  planets smaller than 13 the number that return is 13 (default small prime number).
 * It then iterates through the linked list of
 * Jerries, adding each physical characteristic to the multi-hash table.
 *
 * @param Jerries Pointer to the linked list of Jerry objects.
 * @param PhycharMultiHash Pointer to the multi-hash table to be created.
 * @param planetsize The size of the planets array (used for determining hash table size).
 *
 * @return `success` if the multi-hash table is successfully created and populated.
 *         `Memory_Problem` if memory allocation fails during the process.
 *         `Invalid_input` if the input pointers are NULL or if invalid elements are encountered.
 *         `failure` if a general failure occurs during insertion.
 *
 * @note The following functions are passed to the multi-hash table:
 *       - `CopyKeyString` for deep copying string keys.
 *       - `FreeKeyString` for freeing string keys.
 *       - `PrintKeyStringPhyMulti` for printing string keys with formatting.
 *       - `ShallowCopy` for copying Jerry objects.
 *       - `ShallowFree` for handling Jerry objects (as no deep free is required).
 *       - `PrintJerry` for printing Jerry objects.
 *       - `EqualKeyString` for comparing string keys.
 *       - `EqualJerryInLink` for comparing Jerry objects.
 *       - `transStrToInt` for hashing string keys into integers.
 */
status CreatePhaCharMultiHash(LinkedList* Jerries,multiHashTable* PhycharMultiHash,int planetsize) {
    // check if the pointers the function gets equal to null
    if (Jerries==NULL||PhycharMultiHash==NULL) {
        return Invalid_input;
    }
    int MultiHashSizePrimeNum;
    int PhyCharCount = PhyCharCounter(Jerries);
    // if the number of physical characteristics of Jerries is equal to 0, try to find the Prime Number by jerries size.
    if (PhyCharCount==0) {
        if (getLengthList(*Jerries)==0) {
            // if the number of Jerries is equal to 0, find the Prime Number by planets size.
            MultiHashSizePrimeNum = FindBiggerPrimeNumber(planetsize);
        }
        else {
            // find the Prime Number by the number of Jerries
            MultiHashSizePrimeNum = FindBiggerPrimeNumber(getLengthList(*Jerries));
        }
    }
    else {
        // find the Prime Number by the number of physical characteristics of Jerries
        MultiHashSizePrimeNum = FindBiggerPrimeNumber(PhyCharCount);
    }
    // create multi hashtable and send the function for - key: physical characteristics name (char *) value: jerry struct element
    *PhycharMultiHash = createMultiValueHashTable(CopyKeyString,FreeKeyString,PrintKeyStringPhyMulti,ShallowCopy,ShallowFree,PrintJerry,EqualKeyString,EqualJerryInLink,transStrToInt,MultiHashSizePrimeNum);
    // check if creation success
    if ((*PhycharMultiHash)==NULL) {
        return failure;
    }
    jerry * jerryToAdd;
    PhyChar * PhyCharToAdd;
    // for each jerry in Jerries Linked list
    for (int i = 1; i <= getLengthList(*Jerries); i++) {
        jerryToAdd =(jerry*) getDataByIndex((*Jerries),i);
        if (jerryToAdd==NULL) {
            return Invalid_input;
        }
        // for each physical characteristic of jerry in Jerries Linked list
        for (int j = 0; j < jerryToAdd->number_PhyChar; j++) {
            PhyCharToAdd = jerryToAdd->PhysicalChar[j];
            // add to multi hash table - key physical characteristic name and value (jerry with the physical characteristic)
            status AddToMulti = addToMultiValueHashTable(*PhycharMultiHash,PhyCharToAdd->name,jerryToAdd);
            if (AddToMulti==Memory_Problem) {
                // if add fail, destroy multi hashtable by destroyMultiValueHashTable function
                destroyMultiValueHashTable(*PhycharMultiHash);
                return Memory_Problem;
            }
            if (AddToMulti==Invalid_input) {
                return Invalid_input;
            }
            if (AddToMulti==failure) {
                destroyMultiValueHashTable(*PhycharMultiHash);
                return failure;
            }
        }

    }
    return success;
}


/**
 * @brief Checks if a planet with a specific name exists in the system.
 *
 * Searches for a Planet by name in the `planets` array. If found, sets `check_planet` to the matching Planet
 * and returns success; otherwise, returns `planet_not_exist`.
 *
 * @param name - A pointer to the name string to search for. The string is assumed to be null-terminated.
 * @param check_planet - A pointer to a `planet*` where the corresponding Planet object will be stored
 *                     if found. It will remain unchanged if the planet is not found.
 * @param planets - A pointer to the array of Planet objects.
 * @param planets_size - A pointer to the number of Planet objects in the `planets` array.
 *
 * @return status success if the Planet object is found, planet_not_exist or Invalid_input.
 */
status PlanetCheck(char * name, planet ** check_planet, planet *** planets, int * planets_size) {
    // check if the pointers the function gets equal to null
    if (name == NULL||check_planet==NULL||planets==NULL||planets_size==NULL) {
        return Invalid_input;
    }
    // check for each planet in planets array if the name that got in the function equal to his name.
    for (int i = 0; i< *planets_size; i++) {
        if (strcmp(((*planets)[i]->name),name)==0){
            //  find the planet and save pointer to planet in check_planet that send from the user.
            *check_planet = (*planets)[i];
            return success;
        }
    }
    return planet_not_exist;
}
/**
 * @brief Reads a line and creates a planet object from it.
 *
 * Parses the given string to extract planet details, creates a new planet,
 * and appends it to the planets array, updating its size.
 *
 * @param string The input line containing planet details.
 * @param planets Pointer to the array of planet pointers.
 * @param planets_size Pointer to the size of the planets array.
 *
 * @return `success` if the planet is successfully created and added;
 *         `Memory_Problem` if a memory allocation fails;
 *         `Invalid_input` if any of the inputs is NULL or creation fails.
 */

status readCreatePlanet(char *string, planet*** planets,int * planets_size) {
    // check if the pointers the function gets equal to null
    if (string == NULL||planets==NULL||planets_size==NULL) {
        return Invalid_input;
    }
    char planet_name[301];
    double planet_x, planet_y, planet_z;
    // Reads the line and initializes the variables according to the format and content of the line using the sscanf function
    sscanf(string,"%[^,],%lf,%lf,%lf",planet_name,&planet_x,&planet_y,&planet_z);
    //create planet
    planet *create_planet = NULL;
    status result_create_planet = PlanetCreate(planet_name,planet_x,planet_y,planet_z,&create_planet);
    // Check if the creation success.
    if(result_create_planet == success) {
        // add the planet to the planets array and increase the size of the array (planets_size)
        (*planets)[*planets_size] = create_planet;
        (*planets_size)++;
        return success;
    }
    else if (result_create_planet == Memory_Problem) {
        return Memory_Problem;
    }
    else {
        return Invalid_input;
    }
}

/**
 * @brief Reads a line and creates a Jerry object from it.
 *
 * Parses the given string to extract Jerry details, checks if the referenced
 * planet exists, creates a new Jerry, and appends it to the Jerries linked list.
 *
 * @param string The input line containing Jerry details.
 * @param Jerries Pointer to the linked list of Jerries.
 * @param planets Pointer to the array of planet pointers.
 * @param planets_size Pointer to the size of the planets array.
 *
 * @return `success` if the Jerry is successfully created and added;
 *         `Memory_Problem` if a memory allocation fails;
 *         `Invalid_input` if any of the inputs is NULL or creation fails.
 */

status readCreateJerry(char *string,LinkedList * Jerries,planet*** planets,int * planets_size) {
    // check if the pointers the function gets equal to null
    if (string == NULL||Jerries==NULL||planets==NULL||planets_size==NULL) {
        return Invalid_input;
    }
    // Initialize buffer for reading input from the user
    char jerry_id[301];
    char origin_name[301];
    char jerry_planet[301];
    int happiness;
    // Reads the line and initializes the variables according to the format and content of the line using the sscanf function
    sscanf(string,"%[^,],%[^,],%[^,],%d",jerry_id,origin_name,jerry_planet,&happiness);
    //check and find planet
    planet *check_planet=NULL;
    status planet_find_result = PlanetCheck(jerry_planet,&check_planet,planets,planets_size);
    // Check if the find success
    if(planet_find_result == success) {
        // create jerry
        jerry *create_jerry = NULL;
        status result_create_jerry = JerryCreate(jerry_id,happiness,check_planet,origin_name,&create_jerry);
        // Check if the creation success
        if(result_create_jerry == success) {
            // add the new jerry to the Jerries array and increase the size of the array (size_of_Jerries)
            status NodeAppend = appendNode(*(Jerries),create_jerry);
            if (NodeAppend == success) {
                return success;
            }
            else if (NodeAppend == Memory_Problem) {
                return Memory_Problem;
            }
            else {
                return Invalid_input;
            }
        }
        else if (result_create_jerry == Memory_Problem) {
            return Memory_Problem;
        }
        else {
            return Invalid_input;
        }
    }
    else {
        return Invalid_input;
    }
}

/**
 * @brief Reads a line and creates a physical characteristic for a Jerry.
 *
 * Parses the given string to extract physical characteristic details,
 * creates the characteristic, and adds it to the last Jerry in the Jerries list.
 *
 * @param string The input line containing physical characteristic details.
 * @param Jerries Pointer to the linked list of Jerries.
 *
 * @return `success` if the characteristic is successfully created and added;
 *         `Memory_Problem` if a memory allocation fails;
 *         `Invalid_input` if any of the inputs is NULL or creation fails.
 */

status readCreateJerryPhy(char *string,LinkedList* Jerries) {
    // check if the pointers the function gets equal to null
    if (string == NULL||Jerries==NULL) {
        return Invalid_input;
    }
    double PhysicalChar_val;
    char pyPhysicalChar_name[301];
    // save the string without  '\t'
    char* new_str = string+1;
    // Reads the line and initializes the variables according to the format and content of the line using the sscanf function
    sscanf(new_str,"%[^:]:%lf",pyPhysicalChar_name,&PhysicalChar_val);
    //create physical characteristic
    PhyChar *create_phy = NULL;
    status result_create_phy= PhysicalCharCreate(pyPhysicalChar_name,PhysicalChar_val,&create_phy);
    // Check if the creation success.
    if(result_create_phy == success) {
        // add the physical characteristic to the last jerry in the Jerries array
        status result_add_phy = PhysicalCharAdd(getDataByIndex((*Jerries),getLengthList((*Jerries))),create_phy);
        if(result_add_phy == success) {
            return success;
        }
        // Check if the add success.
        else if(result_add_phy == Memory_Problem) {
            return Memory_Problem;
        }
        else if (result_add_phy == Invalid_input) {
            return Invalid_input;
        }
    }
    else if (result_create_phy == Memory_Problem) {
        return Memory_Problem;
    }
    else {
        return Invalid_input;
    }
}

/**
 * @brief Reads and processes a configuration file to create planets and Jerries.
 *
 * Opens the given configuration file, reads lines to create planet and Jerry objects,
 * and populates the respective data structures. The file format must follow the specified
 * structure with "Planets" and "Jerries" sections.
 *
 * This function utilizes helper functions (`readCreatePlanet`, `readCreateJerry`, and
 * `readCreateJerryPhy`) to parse individual lines, create objects, and manage the data.
 *
 * @param planets Pointer to the array of planet pointers.
 * @param planets_size Pointer to the size of the planets array.
 * @param Jerries Pointer to the linked list of Jerries.
 * @param configurationFile Path to the configuration file.
 *
 * @return `success` if the file is successfully processed;
 *         `Memory_Problem` if a memory allocation fails or the file cannot be closed;
 *         `file_read_fail` if the file cannot be opened;
 *         `Invalid_input` if any of the inputs is NULL or a parsing error occurs.
 */

status ReadConfiguration(planet*** planets,int * planets_size, LinkedList * Jerries,char * configurationFile) {
    // check if the pointers the function gets equal to null
    if (planets==NULL||planets_size==NULL||Jerries==NULL||configurationFile==NULL) {
        return Invalid_input;
    }
    // buffer for the lines that read in the configuration
    char string[301];
    // Initialize pointer to file
    FILE * filePointer=NULL;
    // open the file that his path is configurationFile
    filePointer = fopen(configurationFile,"r");
    if (filePointer==NULL) {
        return file_read_fail;
    }
    // Initialize bool that will help during file reading
    bool End_planets = false;
    // start reading the file until we end to read the last line in the file
    while (fgets(string,301,filePointer)!=NULL) {
        // remove the "\n" from string
        string[strcspn(string, "\n")] = '\0';
        // check if we start to read jerries from the file
        if (string != NULL && strcmp(string, "Jerries") == 0) {
            End_planets = true;
        }
        // reading planets
        else if (End_planets==false) {
            // if string not equal to "Planets"
            if (string != NULL && strcmp(string, "Planets")!=0) {
                // read the line of Planet by readCreatePlanet function
                status readPlanet = readCreatePlanet(string, planets, planets_size);
                if (readPlanet == Memory_Problem) {
                    // close the file
                    fclose(filePointer);
                    return Memory_Problem;
                }
                else if (readPlanet == Invalid_input) {
                    // close the file
                    fclose(filePointer);
                    return Invalid_input;
                }
            }
        }
        // reading jerries
        else {
                // if the line start with '\t' - physical characteristic line
                if (string != NULL && string[0]=='\t') {
                    // read the line of jerry physical characteristic by readCreateJerryPhy function
                    status readPhychar = readCreateJerryPhy(string,Jerries);
                    if (readPhychar == Memory_Problem) {
                        // close the file
                        fclose(filePointer);
                        return Memory_Problem;
                    }
                    else if (readPhychar == Invalid_input) {
                        // close the file
                        fclose(filePointer);
                        return Invalid_input;
                    }
                }
                // read new jerry to create
                else {
                    // read the line of jerry by readCreateJerry function
                    status readJerry = readCreateJerry(string,Jerries,planets,planets_size);
                    if (readJerry == Invalid_input) {
                        // close the file
                        fclose(filePointer);
                        return Invalid_input;
                    }
                    else if (readJerry == Memory_Problem) {
                        // close the file
                        fclose(filePointer);
                        return Memory_Problem;
                    }
                }
        }
    }
    // close the file at the end of while loop - end read the file
    if (fclose(filePointer) != 0) {
        return Memory_Problem;
    }
    return success;
}
/**
 * @brief Adds a new Jerry to the system or identifies an existing one.
 *
 * This function interacts with the user to gather information about a Jerry.
 * It creates a new Jerry if it doesn't already exist in the system or confirms
 * its presence if it does. The data structures (linked list and hash table) are updated accordingly.
 * If the Jerry already exists, no changes are made. If it doesn't exist, the Jerry is added to the system.
 *
 * @param Jerries Pointer to the linked list of Jerries.
 * @param planets Triple pointer to the array of planets.
 * @param planets_size Pointer to the number of planets.
 * @param JerriesHash Pointer to the hash table for Jerries.
 * @return status - Success or relevant error code.
 */
status TakeThisJerryAway(LinkedList* Jerries,planet*** planets,int * planets_size,hashTable* JerriesHash) {
    // check if the pointers the function gets equal to null
    if (Jerries==NULL||JerriesHash==NULL||planets_size==NULL||planets==NULL) {
        return Invalid_input;
    }
    char Jerry_ID[301];
    printf("What is your Jerry's ID ? \n");
    // read ID of jerry from the user
    if(scanf("%s", Jerry_ID)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    // check if have jerry with ID that equal to Jerry_ID in JerriesHash
    Element CheckJerry = lookupInHashTable(*JerriesHash,(Element) Jerry_ID);
    if (CheckJerry==NULL) {
        // read planet name from the user
        char Planet_Name[301];
        printf("What planet is your Jerry from ? \n");
        if(scanf("%s", Planet_Name)!= 1) {
            return failure_reading;
        }
        // clean the buffer before the next use scanf function
        while(getchar() != '\n');
        planet* CheckPlanet=NULL;
        // check if have planet with name that equal to Planet_Name in planets array
        status CheckPlanetExist = PlanetCheck(Planet_Name,&CheckPlanet,planets,planets_size);
        if (CheckPlanetExist==success) {
            // read origin name from the user
            char origin_Name[301];
            printf("What is your Jerry's dimension ? \n");
            if(scanf("%s", origin_Name)!= 1) {
                return failure_reading;
            }
            // clean the buffer before the next use scanf function
            while(getchar() != '\n');
            int JerryHappines;
            // read happines value from the user
            printf("How happy is your Jerry now ? \n");
            if(scanf("%d", &JerryHappines)!= 1) {
                return failure_reading;
            }
            // clean the buffer before the next use scanf function
            while(getchar() != '\n');
            jerry * createJerry = NULL;
            // create jerry with the details that read from the user
            status CreateJerr = JerryCreate(Jerry_ID,JerryHappines,CheckPlanet,origin_Name,&createJerry);
            if (CreateJerr==Invalid_input) {
                return Invalid_input;
            }
            else if (CreateJerr == Memory_Problem) {
                return Memory_Problem;
            }
            // add the new jerry to the Jerries Linked list by appendNode function
            status AppendNode = appendNode(*Jerries,(Element)createJerry);
            if (AppendNode == Invalid_input) {
                return Invalid_input;
            }
            else if (AppendNode == Memory_Problem) {
                return Memory_Problem;
            }
            // add the new jerry to the JerriesHash by addToHashTable (key - Jerry_ID, value - jerry struct instance)
            status AddToHash = addToHashTable(*JerriesHash,(Element) Jerry_ID,(Element) createJerry);
            if (AddToHash == Invalid_input) {
                return Invalid_input;
            }
            else if (AddToHash == Memory_Problem) {
                return Memory_Problem;
            }
            // print the jerry that add
            status PrintStatus = JerryPrint(createJerry);
            if (PrintStatus == Invalid_input) {
                return Invalid_input;
            }
            return success;
        }
        else if (CheckPlanetExist == Invalid_input) {
            return Invalid_input;
        }
        else {
            // if the planet name that read from the user don't exist in planets array
            printf("%s is not a known planet ! \n", Planet_Name);
            return success;
        }
    }
    else {
        // if the jerry ID that read from the user exist in jerries Linked list
        printf("Rick did you forgot ? you already left him here ! \n");
        return success;
    }
}


/**
 * @brief Adds a physical characteristic to an existing Jerry.
 *
 * This function allows the user to define a physical characteristic for a Jerry,
 * including its name and value, and updates the system accordingly. The multi-value
 * hash table is updated with the new characteristic for the specified Jerry.
 *
 * @param JerriesHash Pointer to the hash table for Jerries.
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @return status - Success or relevant error code.
 */
status AddPhCharToJerryInBoree(hashTable* JerriesHash, multiHashTable* PhycharMultiHash) {
    // check if the pointers the function gets equal to null
    if (JerriesHash==NULL||PhycharMultiHash==NULL) {
        return Invalid_input;
    }

    char Jerry_ID[301];
    printf("What is your Jerry's ID ? \n");
    // read ID of jerry from the user
    if(scanf("%s", Jerry_ID)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    // check if have jerry with ID that equal to Jerry_ID in JerriesHash
    Element CheckJerry = lookupInHashTable(*JerriesHash,(Element) Jerry_ID);
    if (CheckJerry==NULL) {
        // if don't have jerry with this ID
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    // read physical characteristic name from the user
    char PhyCharName[301];
    printf("What physical characteristic can you add to Jerry - %s ? \n",Jerry_ID);
    if(scanf("%s", PhyCharName)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    PhyChar* PhyCheck = NULL;
    // check if the jerry have physical characteristic with the same name the user send
    status PhyCharCheck = PhysicalCharCheck(CheckJerry,PhyCharName,&PhyCheck);
    if (PhyCharCheck==Invalid_input) {
        return Invalid_input;
    }
    if (PhyCharCheck == success) {
        // if jerry have physical characteristic with the same name the user send
        printf("The information about his %s already available to the daycare ! \n",PhyCharName);
        return success;
    }
    double PhyVal;
    // read physical characteristic value from the user
    printf("What is the value of his %s ? \n", PhyCharName);
    if(scanf("%lf",&PhyVal)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    PhyChar* PhyAdd = NULL;
    // create physical characteristic with the details that read from thr user
    status CreatePhy = PhysicalCharCreate(PhyCharName,PhyVal,&PhyAdd);
    if (CreatePhy==Invalid_input) {
        return Invalid_input;
    }
    if (CreatePhy == Memory_Problem) {
        return Memory_Problem;
    }
    // add physical characteristic to the jerry the user want
    status PhyCharAdd = PhysicalCharAdd(CheckJerry,PhyAdd);
    if (PhyCharAdd==Invalid_input) {
        return Invalid_input;
    }
    if (PhyCharAdd==Memory_Problem) {
        return Memory_Problem;
    }
    // add the physical characteristic name and the jerry to the multi hashtable PhycharMultiHash by addToMultiValueHashTable function
    status AddToMulti = addToMultiValueHashTable(*PhycharMultiHash,(Element) PhyCharName,(Element) CheckJerry);
    if (AddToMulti==Invalid_input) {
        return Invalid_input;
    }
    if (AddToMulti == Memory_Problem) {
        return Memory_Problem;
    }
    if (AddToMulti == failure) {
        return failure;
    }
    //print all the jerries that have the same physical characteristic that added in the function by the user
    status display = displayMultiValueHashElementsByKey(*PhycharMultiHash,(Element) PhyCharName);
    if (display==Invalid_input) {
        return Invalid_input;
    }
    return success;
}

/**
 * @brief Removes a physical characteristic from an existing Jerry.
 *
 * This function removes a specified physical characteristic from a Jerry and
 * updates the system to reflect the change. The multi-value hash table is updated
 * accordingly. If the characteristic does not exist, no changes are made.
 *
 * @param JerriesHash Pointer to the hash table for Jerries.
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @return status - Success or relevant error code.
 */
status RemovePhayCharFromJerryBoree(hashTable* JerriesHash, multiHashTable* PhycharMultiHash) {
    // check if the pointers the function gets equal to null
    if (JerriesHash==NULL||PhycharMultiHash==NULL) {
        return Invalid_input;
    }
    char Jerry_ID[301];
    printf("What is your Jerry's ID ? \n");
    // read ID of jerry from the user
    if(scanf("%s", Jerry_ID)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    // check if have jerry with ID that equal to Jerry_ID in JerriesHash
    Element CheckJerry = lookupInHashTable(*JerriesHash,(Element) Jerry_ID);
    if (CheckJerry==NULL) {
        // if not have jerry in the JerriesHash with the same ID
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    // read physical characteristic name from the user
    char PhyCharName[301];
    printf("What physical characteristic do you want to remove from Jerry - %s ? \n",Jerry_ID);
    if(scanf("%s", PhyCharName)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    PhyChar* PhyCheck = NULL;
    // check if the jerry from the user have physical characteristic with the same name as 'PhyCharName'
    status PhyCharCheck = PhysicalCharCheck(CheckJerry,PhyCharName,&PhyCheck);
    if (PhyCharCheck==Invalid_input) {
        return Invalid_input;
    }
    if (PhyCharCheck == no_PhyChar) {
        // jerry don't have physical characteristic with the same name as 'PhyCharName'
        printf("The information about his %s not available to the daycare ! \n",PhyCharName);
        return success;
    }
    // remove the physical characteristic with the same name as 'PhyCharName' from jerry by PhysicalCharRemove function
    status PhyCharRemove =PhysicalCharRemove(CheckJerry,PhyCharName);
    if (PhyCharRemove==Invalid_input) {
        return Invalid_input;
    }
    if (PhyCharRemove == Memory_Problem) {
        return Memory_Problem;
    }
    // remove the jerry from PhycharMultiHash, the key 'PhyCharName'
    status removeStatus = removeFromMultiValueHashTable(*PhycharMultiHash,PhyCharName,(Element) (((jerry*)CheckJerry)->ID));
    if (removeStatus==Invalid_input) {
        return Invalid_input;
    }
    if (removeStatus == no_element) {
        return Invalid_input;
    }
    // print jerry after the remove of physical characteristic by JerryPrint function
    JerryPrint(CheckJerry);
    return success;
}

/**
 * @brief Removes a Jerry from the system.
 *
 * This function removes a specified Jerry from all relevant data structures,
 * including hash tables and the linked list of Jerries. If the Jerry is not found,
 * no changes are made to the data structures.
 *
 * @param JerriesHash Pointer to the hash table for Jerries.
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @param JerriesList Pointer to the linked list of Jerries.
 * @param Jerry_ID ID of the Jerry to remove.
 * @return status - Success or relevant error code.
 */
status RemoveJerryFromBoree(hashTable* JerriesHash, multiHashTable* PhycharMultiHash,LinkedList* JerriesList,char *Jerry_ID) {
    // check if the pointers the function gets equal to null
    if (JerriesHash==NULL||PhycharMultiHash==NULL||JerriesList==NULL||Jerry_ID==NULL) {
        return Invalid_input;
    }
    // check if Jerry_ID is ID of jerry that in JerriesHash
    Element CheckJerry = lookupInHashTable(*JerriesHash,Jerry_ID);
    if (CheckJerry==NULL) {
        // don't have jerry with the same id in JerriesHash as Jerry_ID
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    // remove the jerry with the same ID as Jerry_ID from JerriesHash by removeFromHashTable function
    status removeFromHash = removeFromHashTable(*JerriesHash,Jerry_ID);
    if (removeFromHash==Invalid_input) {
        return Invalid_input;
    }
    // remove the jerry with the same ID as Jerry_ID from PhycharMultiHash by removeFromMultiValueHashTable function
    for (int i=0; i<((jerry*)CheckJerry)->number_PhyChar;i++) {
        // iterate all the physical characteristic of jerry and remove jerry from PhycharMultiHash by his physical characteristic by removeFromMultiValueHashTable function
        status removeStatus = removeFromMultiValueHashTable(*PhycharMultiHash,((jerry*)CheckJerry)->PhysicalChar[i]->name,(Element) (((jerry*)CheckJerry)->ID));
        if (removeStatus==Invalid_input) {
            return Invalid_input;
        }
        if (removeStatus == no_element) {
            return Invalid_input;
        }
    }
    // remove jerry from JerriesList Linked List by deleteNode function
    status removeLinkList = deleteNode(*JerriesList,(Element) (((jerry*)CheckJerry)->ID));
    if (removeLinkList==Invalid_input) {
        return Invalid_input;
    }
    if (removeLinkList == no_element) {
        return Invalid_input;
    }
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}

/**
 * @brief Finds the value of a specific physical characteristic of a Jerry.
 *
 * This function retrieves the value of a physical characteristic for a specified
 * Jerry. If the characteristic is not found, it returns NAN.
 *
 * @param jerr Pointer to the Jerry.
 * @param PhyCharName Name of the physical characteristic.
 * @return double - The value of the physical characteristic or -1 if not found.
 */
double GetValOfPhyChar(jerry * jerr,char * PhyCharName) {
    // check if the pointers the function gets equal to null
    if (jerr == NULL||PhyCharName == NULL) {
        return NAN;
    }
    PhyChar * phyChar=NULL;
    // get the physical characteristic
    PhysicalCharCheck(jerr,PhyCharName,&phyChar);
    if (phyChar==NULL) {
        return NAN;
    }
    // return phyChar value
    return (phyChar->value);
}

/**
 * @brief Finds the most similar Jerry based on a specified physical characteristic.
 *
 * This function determines the Jerry whose value for a given physical characteristic
 * is closest to the user's input. The system is updated accordingly based on the result.
 *
 * @param JerriesHash Pointer to the hash table for Jerries.
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @param JerriesList Pointer to the linked list of Jerries.
 * @return status - Success or relevant error code.
 */
status FindMostSimilarJerry(hashTable* JerriesHash, multiHashTable* PhycharMultiHash,LinkedList* JerriesList) {
    // check if the pointers the function gets equal to null
    if (JerriesHash==NULL||PhycharMultiHash==NULL||JerriesList==NULL) {
        return Invalid_input;
    }
    // read physical characteristic name from the user
    char PhyCharName[301];
    printf("What do you remember about your Jerry ? \n");
    if(scanf("%s", PhyCharName)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    // check if have jerries in the multi hash table that they have physical characteristic with same name as 'PhyCharName'
    Element ListOfValPhCheck = lookupInMultiValueHashTable(*PhycharMultiHash,PhyCharName);
    if (ListOfValPhCheck==NULL) {
        // not have jerries that have physical characteristic with same name as 'PhyCharName'
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", PhyCharName);
        return success;
    }
    // read value to find the closet from the user
    double ValueToCheck;
    printf("What do you remember about the value of his %s ? \n",PhyCharName);
    if(scanf("%lf", &ValueToCheck)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    double MinVal=-1;
    int indexMinJerry=-1;
    // iterate of all the jerries that have physical characteristic with same name as 'PhyCharName' and find the jerry with the close physical characteristic value to 'ValueToCheck'
    for (int i=1; i<=getLengthList((LinkedList)ListOfValPhCheck);i++) {
        // get the value of the physical characteristic by GetValOfPhyChar function
        double PhayVal = GetValOfPhyChar(getDataByIndex((LinkedList)ListOfValPhCheck,i),PhyCharName);
        if (PhayVal==NAN) {
            return Invalid_input;
        }
        // Calculating the difference in absolute value
        double AbsDifference;
        if (PhayVal<ValueToCheck) {
            AbsDifference = ValueToCheck - PhayVal;
        }
        else {
            AbsDifference= PhayVal - ValueToCheck;
        }
        // save the minimum difference and the index of the jerry with the minimum difference
        if (MinVal==-1) {
            MinVal = AbsDifference;
            indexMinJerry = i;
        }
        else if(MinVal>AbsDifference) {
            MinVal = AbsDifference;
            indexMinJerry = i;
        }
    }
    jerry* jerr = (jerry *)getDataByIndex((LinkedList)ListOfValPhCheck,indexMinJerry);
    printf("Rick this is the most suitable Jerry we found : \n");
    // print the jerry with the minimum difference by JerryPrint function
    status JerryPri = JerryPrint(jerr);
    if (JerryPri==Invalid_input) {
        return Invalid_input;
    }
    // remove jerry from the system by RemoveJerryFromBoree function
    status RemoveJerr = RemoveJerryFromBoree(JerriesHash,PhycharMultiHash,JerriesList,jerr->ID);
    if (RemoveJerr == Invalid_input) {
        return Invalid_input;
    }
    return success;
}

/**
 * @brief Identifies and provides the saddest Jerry.
 *
 * This function finds the Jerry with the lowest happiness level, removes it from the
 * system, and updates all relevant data structures accordingly.
 *
 * @param JerriesHash Pointer to the hash table for Jerries.
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @param JerriesList Pointer to the linked list of Jerries.
 * @return status - Success or relevant error code.
 */
status GiveSaddestJerry(hashTable* JerriesHash, multiHashTable* PhycharMultiHash,LinkedList* JerriesList) {
    // check if the pointers the function gets equal to null
    if (JerriesHash==NULL||PhycharMultiHash==NULL||JerriesList==NULL) {
        return Invalid_input;
    }
    // check if not have jerries in JerriesList Linked List
    if (getLengthList(*JerriesList)==0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    int minHappines = 101;
    int indexMinJerry=-1;
    // search the jerry with the minimum value of happiness
    for (int i = 1 ; i<=getLengthList(*JerriesList); i++) {
        jerry* jerr = (jerry*)getDataByIndex(*JerriesList,i);
        if ((jerr->happiness)<minHappines) {
            minHappines = jerr->happiness;
            indexMinJerry = i;
        }
    }
    jerry* jerryToGive = (jerry *)getDataByIndex((LinkedList)*JerriesList,indexMinJerry);
    printf("Rick this is the most suitable Jerry we found : \n");
    //print the jerry with the minimum value of happiness by JerryPrint function
    status JerryPri = JerryPrint(jerryToGive);
    if (JerryPri==Invalid_input) {
        return Invalid_input;
    }
    // remove jerry from the system by RemoveJerryFromBoree function
    status RemoveJerr = RemoveJerryFromBoree(JerriesHash,PhycharMultiHash,JerriesList,jerryToGive->ID);
    if (RemoveJerr == Invalid_input) {
        return Invalid_input;
    }
    return success;
}


/**
 * @brief Prints all Jerries with a specific physical characteristic.
 *
 * This function displays all Jerries in the system that have the specified physical
 * characteristic. The multi-value hash table is used to find the relevant Jerries.
 *
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @return status - Success or relevant error code.
 */
status printByPhyChar(multiHashTable* PhycharMultiHash) {
    // check if the pointers the function gets equal to null
    if (PhycharMultiHash==NULL) {
        return Invalid_input;
    }
    // read physical characteristic name from the user
    char PhyCharName[301];
    printf("What physical characteristics ? \n");
    if(scanf("%s", PhyCharName)!= 1) {
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while(getchar() != '\n');
    // check if have jerries in the multi hash table that they have physical characteristic with same name as 'PhyCharName'
    Element ListOfValPhCheck = lookupInMultiValueHashTable(*PhycharMultiHash,PhyCharName);
    if (ListOfValPhCheck==NULL) {
        // not have jerries that have physical characteristic with same name as 'PhyCharName'
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", PhyCharName);
        return success;
    }
    //print all the jerries that have the same physical characteristic name as PhyCharName
    status printStatus = displayMultiValueHashElementsByKey(*PhycharMultiHash,PhyCharName);
    if (printStatus==Invalid_input) {
        return Invalid_input;
    }
    return success;
}
/**
 * @brief Prints all known planets in the system.
 *
 * This function displays all planets currently known in the system, based on the
 * data structures provided.
 *
 * @param planets Triple pointer to the array of planets.
 * @param planets_size Number of planets.
 * @return status - Success or relevant error code.
 */
status PrintAllPlanets(planet*** planets,int planets_size) {
    // check if the pointer the function gets equal to null
    if (planets==NULL) {
        return Invalid_input;
    }
    // print all the planets in planets array by the function PlanetPrint
    for (int i = 0; i < planets_size; i++) {
        status printStatus = PlanetPrint((*planets)[i]);
        if (printStatus==Invalid_input) {
            return Invalid_input;
        }
    }
    return success;
}

/**
 * @brief Displays information about Jerries, planets, or characteristics to Rick.
 *
 * Provides Rick with options to view all Jerries, all Jerries with physical characteristics,
 * or the known planets in the system, based on the data provided.
 *
 * @param PhycharMultiHash Pointer to the multi-value hash table for physical characteristics.
 * @param JerriesList Pointer to the linked list of Jerries.
 * @param planets Triple pointer to the array of planets.
 * @param planets_size Number of planets.
 * @return status - Success or relevant error code.
 */
status PrintInformationToRick(multiHashTable* PhycharMultiHash,LinkedList* JerriesList,planet*** planets,int planets_size) {
    // check if the pointers the function gets equal to null
    if (PhycharMultiHash==NULL||JerriesList==NULL||planets==NULL) {
        return Invalid_input;
    }
    // tmp buffer for reading the input from the user
    char input[10];
    // char for switch if the length of the input is 1
    char ch = '\0';
    //  main while that print for the user the options of the action he can do
    printf("What information do you want to know ? \n");
    printf("1 : All Jerries \n");
    printf("2 : All Jerries by physical characteristics \n");
    printf("3 : All known planets \n");

    // read the first 9 chars in the input from the user
    if (scanf("%9s", input) != 1) {
        // if the reading fail, print error message and clean up the system
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while (getchar() != '\n');
    // check that the input length is valid - length equal to 1
    if (strlen(input) != 1) {
        //  if the user don't choose 1-3 opions in the main
        printf("Rick this option is not known to the daycare ! \n");
        return success;
    }
    // if length is valid we check only the first char in the switch
    ch = input[0];

    // check the value of 'ch' and fits into the appropriate case
    switch( ch ) {
        case '1':
            // check the Length of the JerriesList Linked list
            if (getLengthList(*JerriesList)==0) {
                // if the Length is 0
                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                return success;
            }
            // print all jerries by displayList function
            return displayList(*JerriesList);

        case '2':
            // print all jerries with specific physical characteristic the user want by printByPhyChar function
            return printByPhyChar(PhycharMultiHash);
        case '3':
            // print all planets in planets array by PrintAllPlanets function
            return PrintAllPlanets(planets,planets_size);
        default:
            // if the user input invalid choose (not 1-3 number)
            printf("Rick this option is not known to the daycare ! \n");
            return success;
        }
}
/**
 * @brief Interacts with fake beth adjusting Jerries their happiness based on their current levels.
 *
 * If a Jerry's happiness is less than 20, it decreases by 5 (but not below 0).
 * If a Jerry's happiness is 20 or more, it increases by 15 (but not above 100).
 * The function updates the linked list of Jerries accordingly.
 *
 * @param JerriesList Pointer to the linked list of Jerries.
 * @return status - Success or relevant error code.
 */
status InteractFakeBeth(LinkedList* JerriesList) {
    // check if the pointer the function gets equal to null
    if (JerriesList==NULL) {
        return Invalid_input;
    }
    // for each jerry in JerriesList Linked List, cahnge the happiness according to the activity and the description in the docstring
    for (int i = 1; i <= getLengthList(*JerriesList); i++) {
        jerry * jerr =(jerry *) getDataByIndex(*JerriesList,i);
        if (jerr==NULL) {
            return Invalid_input;
        }
        if (jerr->happiness<20) {
            if(jerr->happiness-5<0) {
                jerr->happiness = 0;
            }
            else {
                jerr->happiness = jerr->happiness-5;
            }
        }
        else {
            if (jerr->happiness+15>100) {
                jerr->happiness = 100;
            }
            else {
                jerr->happiness = jerr->happiness+15;
            }
        }
    }
    printf("The activity is now over ! \n");
    // print all the jerries after the change of the happiness by displayList function
    return displayList(*JerriesList);
}

/**
 * @brief Allows the Jerries to play golf, adjusting their happiness based on their current levels.
 *
 * If a Jerry's happiness is less than 50, it decreases by 10 (but not below 0).
 * If a Jerry's happiness is 50 or more, it increases by 10 (but not above 100).
 * The function updates the linked list of Jerries accordingly.
 *
 * @param JerriesList Pointer to the linked list of Jerries.
 * @return status - Success or relevant error code.
 */
status playGolf(LinkedList* JerriesList) {
    // check if the pointer the function gets equal to null
    if (JerriesList==NULL) {
        return Invalid_input;
    }
    // for each jerry in JerriesList Linked List, cahnge the happiness according to the activity and the description in the docstring
    for (int i = 1; i <= getLengthList(*JerriesList); i++) {
        jerry * jerr =(jerry *) getDataByIndex(*JerriesList,i);
        if (jerr==NULL) {
            return Invalid_input;
        }
        if (jerr->happiness<50) {
            if(jerr->happiness-10<0) {
                jerr->happiness = 0;
            }
            else {
                jerr->happiness = jerr->happiness-10;
            }
        }
        else {
            if (jerr->happiness+10>100) {
                jerr->happiness = 100;
            }
            else {
                jerr->happiness = jerr->happiness+10;
            }
        }
    }
    printf("The activity is now over ! \n");
    // print all the jerries after the change of the happiness by displayList function
    return displayList(*JerriesList);
}


/**
 * @brief Adjusts the picture settings on the TV, increasing the happiness of all Jerries.
 *
 * The happiness of each Jerry is increased by 20, but not beyond 100.
 * The function updates the linked list of Jerries accordingly.
 *
 * @param JerriesList Pointer to the linked list of Jerries.
 * @return status - Success or relevant error code.
 */
status AdjustPictureSettOnTv(LinkedList* JerriesList) {
    // check if the pointer the function gets equal to null
    if (JerriesList==NULL) {
        return Invalid_input;
    }
    // for each jerry in JerriesList Linked List, cahnge the happiness according to the activity and the description in the docstring
    for (int i = 1; i <= getLengthList(*JerriesList); i++) {
        jerry * jerr =(jerry *) getDataByIndex(*JerriesList,i);
        if (jerr==NULL) {
            return Invalid_input;
        }
        if (jerr->happiness+20>100) {
            jerr->happiness = 100;
        }
        else {
            jerr->happiness = jerr->happiness+20;
        }
    }
    printf("The activity is now over ! \n");
    // print all the jerries after the change of the happiness by displayList function
    return displayList(*JerriesList);
}


/**
 * @brief Prompts the user to choose an activity for the Jerries to partake in.
 *
 * Displays a menu for the user to select one of three activities for the Jerries:
 * 1. Interact with fake Beth
 * 2. Play golf
 * 3. Adjust the picture settings on the TV
 *
 * Based on the user's input, the corresponding function is called to modify the Jerries' happiness.
 *
 * @param JerriesList Pointer to the linked list of Jerries.
 * @return status - Success or relevant error code.
 */
status LetJerriesPlay(LinkedList* JerriesList) {
    // check if the pointer the function gets equal to null
    if (JerriesList==NULL) {
        return Invalid_input;
    }
    // check if not have jerries in JerriesList Linked List
    if (getLengthList(*JerriesList)==0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    // tmp buffer for reading the input from the user
    char input[10];
    // char for switch if the length of the input is 1
    char ch = '\0';
    // main while that print for the user the options of the action he can do
    printf("What activity do you want the Jerries to partake in ? \n");
    printf("1 : Interact with fake Beth \n");
    printf("2 : Play golf \n");
    printf("3 : Adjust the picture settings on the TV \n");

    // read the first 9 chars in the input from the user
    if (scanf("%9s", input) != 1) {
        // if the reading fail, print error message and clean up the system
        return failure_reading;
    }
    // clean the buffer before the next use scanf function
    while (getchar() != '\n');
    // check that the input length is valid - length equal to 1
    if (strlen(input) != 1) {
        //  if the user don't choose 1-3 opions in the main
        printf("Rick this option is not known to the daycare ! \n");
        return success;
    }
    // if length is valid we check only the first char in the switch
    ch = input[0];

    // check the value of 'ch' and fits into the appropriate case
    switch( ch ) {
        case '1':
            // Activating the activity 'Interact Fake Beth' and changing the value of happiness to the jerries accordingly
            return InteractFakeBeth(JerriesList);
        case '2':
            // Activating the activity 'Play Golf' and changing the value of happiness to the jerries accordingly
            return playGolf(JerriesList);
        case '3':
            // Activating the activity 'Adjust Picture Sett On Tv' and changing the value of happiness to the jerries accordingly
            return AdjustPictureSettOnTv(JerriesList);
        default:
            //  if the user don't choose 1-3 opions in the main
            printf("Rick this option is not known to the daycare ! \n");
        return success;
    }

}

/**
 * @brief Entry point for the Jerry daycare management system.
 *
 * The `main` function sets up the necessary data structures, reads the configuration file,
 * and provides an interactive menu for managing Jerries and their associated data. It handles
 * initialization, menu-based operations, error handling, and cleanup.
 *
 * The main operations include:
 * 1. Initializing an array of planets based on user input.
 * 2. Reading and parsing a configuration file to populate the daycare system.
 * 3. Creating data structures:
 *    - A linked list to store Jerry objects.
 *    - A hash table for fast access to Jerry objects by their ID.
 *    - A multi-hash table for organizing Jerry objects by their physical characteristics.
 * 4. Providing a user menu to:
 *    - Add or remove Jerries.
 *    - Modify physical characteristics of Jerries.
 *    - Retrieve the saddest Jerry or the most similar Jerry.
 *    - Print information about the daycare.
 *    - Simulate interactions among the Jerries.
 * 5. Cleaning up all resources upon termination.
 *
 * @param argc Number of command-line arguments provided.
 *             Expected to be 3: the program name, the number of planets, and the configuration file path.
 * @param argv Array of command-line arguments.
 *             - argv[1]: Number of planets (as a string, converted to an integer).
 *             - argv[2]: Path to the configuration file.
 *
 * @return 0 on successful termination, or 1 in case of errors such as:
 *         - Invalid number of command-line arguments.
 *         - Memory allocation failures.
 *         - File reading issues.
 *         - Invalid input detected during operation.
 *
 * @note Responsibility for clean the data if the user implement deep copies function for the ADT:
 *       If the user requests a deep copy of data and user gets function, they must
 *       ensure proper cleanup of the returned data after use.
 *
 * @note Hash table sizing:
 *       - Jerry hash table size:
 *         Determined by the smallest prime number greater than the number of Jerries.
 *         If no Jerries exist, the system uses the number of planets to find the next prime.
 *       - Multi-hash table size:
 *         Determined by the smallest prime number greater than the number of physical characteristics.
 *         If no characteristics exist, determined by the smallest prime number greater than the number of Jerries is used.
 *         If no Jerries exist, determined by the smallest prime number greater than the number of planets is used.
 *
 * minimun size of Jerry hash table and Multi-hash table is 13. If the number of jerries's physical characteristics or jerries
 * or planets smaller than 13 the number that return is 13 (default small prime number).
 * Because if the size of the because if the largest number of the data in the ADT will be small,
 * for example 2 or 3 then the prime number in the return will be small, and if during the program
 * the user add a lot of jerries or physical characteristics the table will be too small it will lose its advantage

 *
 * @note Error handling:
 *       Any operation that encounters a memory issue, invalid input, or failure to read input will terminate the system
 *       after properly cleaning up all allocated resources.
 */

int main(int argc, char *argv[]){
    // check if the number of parameters is valid
    if (argc != 3) {
        printf("number of parameters is invalid \n");
        return 1;
    }
    // Initialize the parameters in variance
    int number_of_planets_file = atoi(argv[1]);
    char *configurationFile = argv[2];

    // Create and allocate array of pointers to planets in size of number_of_planets
    planet** planets = NULL;
    planets = (planet **) malloc(number_of_planets_file*sizeof(planet*));
    // Check if the allocate success.
    if (planets==NULL) {
        printf("A memory problem has been detected in the program\n");
        return 1;
    }
    // variance that sum the number of planets that add to the array
    int planets_size = 0;

    // create JerriesList Linked List by createLinkedList function and sent function for Jerry struct instance
    LinkedList JerriesList = createLinkedList(ShallowCopy,FreeJerryInLink,PrintJerry,EqualJerryInLink);
    // check if the creation success
    if (JerriesList==NULL) {
        printf("A memory problem has been detected in the program\n");
        // free the space allocate to planets if fail
        free(planets);
        return 1;
    }
    // read the configuration file to init the system and create jerries and planets
    status read_configuration = ReadConfiguration(&planets,&planets_size,&JerriesList,configurationFile);
    if (read_configuration==Memory_Problem) {
        printf("A memory problem has been detected in the program\n");
        // free the space allocate to planets and JerriesList Linked List if read configuration fail
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }
    else if (read_configuration == Invalid_input){
        printf("Invalid input problem\n");
        // free the space allocate to planets and JerriesList Linked List if read configuration fail
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }
    else if (read_configuration == file_read_fail) {
        printf("File read failure\n");
        // free the space allocate to planets and JerriesList Linked List if read configuration fail
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }

    hashTable JerriesHash =NULL;
    // create and storage the key - Jerries ID and value - Jerries struct instance in JerriesHash by CreateJerryHash function
    status CreateHash = CreateJerryHash(&JerriesList,&JerriesHash,planets_size);
    if (CreateHash==Memory_Problem) {
        printf("A memory problem has been detected in the program\n");
        // free the space allocate to planets and JerriesList Linked List if read configuration fail
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }
    else if (CreateHash == Invalid_input){
        printf("Invalid input problem\n");
        // free the space allocate to planets and JerriesList Linked List and JerriesHash if read configuration fail
        destroyHashTable((JerriesHash));
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }

    multiHashTable PhycharMultiHash = NULL;
    // create and storage the key - physical characteristics Name and value - Jerries struct instance with physical instance in PhycharMultiHash by CreatePhaCharMultiHash function
    status CreateMultiHash = CreatePhaCharMultiHash(&JerriesList,&PhycharMultiHash,planets_size);
    if (CreateMultiHash==Memory_Problem) {
        printf("A memory problem has been detected in the program\n");
        // free the space allocate to planets and JerriesList Linked List and JerriesHash if read configuration fail
        destroyHashTable((JerriesHash));
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }
    else if (CreateMultiHash == Invalid_input) {
        printf("Invalid input problem\n");
        // free the system and all the ADT's and the data they store by CleanUp function
        CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
        return 1;
    }
    else if (CreateMultiHash==failure) {
        printf("Create Multi Hash failure\n");
        // free the space allocate to planets and JerriesList Linked List and JerriesHash if read configuration fail
        destroyHashTable((JerriesHash));
        destroyList(JerriesList);
        DestroyPlanets(&planets,planets_size);
        return 1;
    }
    // if the function ReadConfiguration not fail
    // tmp buffer for reading the input from the user
    char input[10];
    // char for switch if the length of the input is 1
    char ch = '\0';
    // the main while that print for the user the options of the action he can do
    while( ch != '9' ) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");

        // read the first 9 chars in the input from the user
        if (scanf("%9s", input) != 1) {
            // if the reading fail, print error message and clean up the system
            printf("Error reading input\n");
            CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
            return 1;
        }

        // clean the buffer before the next use scanf function
        while (getchar() != '\n');

        // check that the input length is valid - length equal to 1
        if (strlen(input) != 1) {
            //  if the user don't choose 1-9 opions in the main
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
        // if length is valid we check only the first char in the switch
        ch = input[0];

        // check the value of 'ch' and fits into the appropriate case
        switch( ch )
        {
            case '1':
                // call a function that add jerry to the daycare - TakeJerryAway function, and handel possible errors
                status TakeJerryAway = TakeThisJerryAway(&JerriesList,&planets,&planets_size,&JerriesHash);
                if (TakeJerryAway==Memory_Problem) {
                    printf("A memory problem has been detected in the program\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (TakeJerryAway == Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (TakeJerryAway == failure_reading) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
            break;

            case '2':
                // call a function that add physical characteristics to jerry that in the daycare - AddPhCharToJerryInBoree function, and handel possible errors
                status AddPhChar = AddPhCharToJerryInBoree(&JerriesHash,&PhycharMultiHash);
                if (AddPhChar==Memory_Problem) {
                    printf("A memory problem has been detected in the program\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (AddPhChar == Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (AddPhChar == failure) {
                    printf("Add physical characteristic failure\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (AddPhChar == failure_reading) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }

            break;

            case '3':
                // call a function that remove physical characteristics from jerry that in the daycare - RemovePhayCharFromJerryBoree function, and handel possible errors
                status RemovePhChar=RemovePhayCharFromJerryBoree(&JerriesHash,&PhycharMultiHash);
                if (RemovePhChar==Memory_Problem) {
                    printf("A memory problem has been detected in the program\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (RemovePhChar == Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (RemovePhChar == failure_reading) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
            break;

            case '4':
                char Jerry_ID[301];
                printf("What is your Jerry's ID ? \n");
                // read ID of jerry from the user
                if(scanf("%s", Jerry_ID)!= 1) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                // clean the buffer before the next use scanf function
                while(getchar() != '\n');
                // call a function that remove from jerry from the daycare - RemoveJerryFromBoree function, and handel possible errors
                status RemoveJerry=RemoveJerryFromBoree(&JerriesHash,&PhycharMultiHash,&JerriesList,Jerry_ID);
                if (RemoveJerry==Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }

            break;

            case '5':
                // call a function that find similar jerry in the daycare by physical characteristics value by - FindSimilarJerry function, and handel possible errors
                status FindSimilarJerry=FindMostSimilarJerry(&JerriesHash,&PhycharMultiHash,&JerriesList);
                if (FindSimilarJerry==Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (FindSimilarJerry == failure_reading) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                    }
            break;

            case '6':
                // call a function that find saddest jerry in the daycare by minimum happiness value by - GiveSaddestJerry function, and handel possible errors
                status GiveSaddestJerr=GiveSaddestJerry(&JerriesHash,&PhycharMultiHash,&JerriesList);
                if (GiveSaddestJerr==Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
            break;

            case '7':
                // call a function that print info about the daycare by - PrintInformationToRick function, and handel possible errors
                status PrintInfo = PrintInformationToRick(&PhycharMultiHash,&JerriesList,&planets,planets_size);
                if (PrintInfo==Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (PrintInfo == failure_reading) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                break;
            case '8':
                // call a function that active activity for the jerries in the daycare and changes their level of happiness accordingly by - LetJerriesPlay function, and handel possible errors
                status LetJerryPlay = LetJerriesPlay(&JerriesList);
                if (LetJerryPlay==Invalid_input) {
                    printf("Invalid input problem\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                else if (LetJerryPlay == failure_reading) {
                    printf("Error reading input\n");
                    // free the system and all the ADT's and the data they store by CleanUp function
                    CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                    return 1;
                }
                break;
            case '9':
                // free the system and all the ADT's and the data they store by CleanUp function
                CleanUp(&JerriesList,&planets,&JerriesHash,&PhycharMultiHash,planets_size);
                printf("The daycare is now clean and close ! \n");
                // end the system without errors
                return 0;

            default:
                //  if the user don't choose 1-9 opions in the main
                printf("Rick this option is not known to the daycare ! \n");
        }
    }
}
