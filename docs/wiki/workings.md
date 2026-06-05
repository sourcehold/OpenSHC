# How reimplementation works
The reimplementation currently works by creating a windows DLL containing reimplemented functions.

## Detouring and hooking original functions to check reimplementation quality
The project progresses by incrementally including new reimplemented functions. When a new function is reimplemented, its workings can be compared on the machine-code level (`reccmp`) and/or on the functional level (does the game run the same with and without the reimplementation).

The game's functions are hooked and detoured into the DLL's reimplemented functions. An added benefit to this approach is that Debug Symbols improve the developer experience.

Hooking and detouring of course comes with a performance hit but for reimplementation purposes this will likely be negligible. A full reimplementation can reduce the need for hooks.

## Interfacing with the game
It is essential that data structures and function calls look the same as the original game.

Most the game's classes are known: it is clear which function belongs to which class.

The current approach consists of a directory and namespace layout that mimicks the roles of the game's classes.

Note that many classes follow the Singleton pattern. Other classes, such as Scenario Events, do not have any virtual functions. The main exception to this is C++ code such as strings and pipes (`<<`), but there original C++ definition is well-known and understood.

These facts simplify the approach to interfacing with the game.

### The use of macros
Macros are used to aid in interfacing with the game. They are needed because C++ doesn't really like the use of class methods based on function pointers, and we rely on function pointers to interface with the original game.

Some crucial macros are those to invoke an original class method that has not been reimplemented yet.

- `MACRO_STRUCT_RESOLVER` declares a global variable as either a pointer to the original game's memory or as a variable stored in the DLL's memory (depending on reimplementation status). These objects should be operated on using `::ptr` (we operate on the pointer agnostic of which memory it is in and reimplemenation status).
- `MACRO_FUNCTION_RESOLVER` declares a function as reimplemented or not. If reimplemented, all calls to the function in the original game are rerouted to the reimplementation. 
- `MACRO_CALL`: Used in reimplemented code to call the original or the reimplementation (depending on reimplementation status).
- `MACRO_MEMBER_CALL`: Same as `MACRO_CALL` but for class methods instead of functions.

