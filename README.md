# JerryBoree – Modular C Project for Managing Jerries and System Entities

## 📋 Overview
The **JerryBoree system** is a modular C project designed to manage a dynamic system of fictional characters called "Jerries," their planets, and physical characteristics.  
The system was built with an emphasis on **generic data structures**, **status-driven logic**, **memory safety**, and **modularity**.

It includes two main components:
* A **Jerry module**, handling the creation and management of Jerry instances.
* A **data structure–based system** that integrates Jerries using arrays, linked lists, hash tables, and multi-hash tables.

---

## 🔁 1. Status-Driven Architecture

All functions in the project return clear status codes (defined in `Defs.h`) such as:
* `SUCCESS`
* `FAILURE`
* `INVALID_INPUT`
* `MEMORY_ERROR`

This design enables safe and structured error handling. For example:
* On memory allocation failure, the function returns `MEMORY_ERROR`, prints an error message, and the main system frees resources and exits cleanly.

Even when not required, input validation and status checks were implemented consistently for clarity and future extensibility.

---

## 🧱 2. Jerry Module: Design & Encapsulation

The Jerry module defines:
* The `Jerry` struct and related data (origin, ID, planet, physical characteristics)
* `OriginCreate` is **encapsulated** within `JerryCreate` to hide implementation details

### Key Design Decisions:
* The user only interacts with `JerryCreate`, without managing origins manually.
* `OriginCreate` may be removed from the header file in future versions for full encapsulation.
* `.h` files include detailed documentation; `.c` files contain inline implementation comments.

This structure supports integration into generic data structures while maintaining clean abstraction.

---

## 📦 3. System Data Structures

### a. Array of Planets
* A fixed-size array created using the command-line parameter sent to `main`.
* Populated while reading the configuration file.

### b. Linked List of Jerries
* Each node represents a `Jerry`.
* Jerries are added as they are parsed from the input.

### c. Hashtable of Jerries
* Implemented as an array of linked lists (chaining).
* **Key**: Jerry ID (deep copy)  
  **Value**: Pointer to a `Jerry` (shallow copy).
* Built by iterating through the linked list of Jerries.
* Enables average-case **O(1)** lookup.

### d. Multi-Hashtable of Physical Characteristics
* A hashtable where:
  * **Key**: Physical characteristic name (string)
  * **Value**: Linked list of Jerries sharing that trait
* Built by iterating through each Jerry’s physical characteristics.
* Enables efficient access to all Jerries associated with a specific trait.
* Average-case lookup: **O(1)**

---

## 🧠 4. Copy, Compare, and Delete Functions

To support generic ADTs and preserve modularity:
* **Copy** – Deep copies keys (e.g., Jerry ID or trait name), shallow copies values (Jerries)
* **Delete** – Frees dynamically allocated keys, detaches Jerries when needed
* **Compare** – Matches keys (e.g., for ID search)

These functions are implemented in `JerryBoreeMain.c` and passed as function pointers to data structure constructors.

---

## 🧮 5. Hashing and Table Sizing Strategy

To ensure performance and reduce collisions:
* All hashtable sizes are rounded **up to the next prime number** ≥ required count
* **Minimum table size** is 13 to avoid poor distribution in small inputs

### Sizing Rules:
* **Hashtable**:
  * Based on the number of Jerries or traits
* **Multi-Hashtable**:
  * Based on total number of physical characteristics
* If no traits exist:
  * Fallback to number of Jerries or planets

---

## 🧾 6. Code Modularity and Maintainability

* Status-driven architecture ensures consistent error handling
* The Jerry module is fully abstract and encapsulated
* Memory allocations are tracked and properly released
* Data structures are flexible and reusable across future modules

---

## ✅ Summary

The JerryBoree system combines:
* Low-level C programming with dynamic memory management
* Generic abstract data types (ADTs)
* Hashing and efficient lookup logic
* Clean modular design and clear documentation

> All components are implemented to maximize modularity, performance, and clarity.
