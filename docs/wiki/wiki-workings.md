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

### Reimplementing Classes
A reimplemented class can look as follows. A class is defined that extends the struct part of the original class.
Preferably this struct is defined in a different file. For example, `validTiles` is defined there as a `unsigned char[400][400]` (perhaps should be a `bool`).

The function `isvalidXY` has a reimplementation that can be toggled on or off in the compilation using macro define statements.

The original function of the game is called via the macro `MemberFunctionPointer_InvokeMethod`. The reason for using a macro is that the C++ hack that is needed here is error-prone if typed manually.

```cpp
#pragma once

#include "../game/constants.h"
#include "../game/common.h"
#include "../game/structs/ViewportRenderState.h"

namespace ViewportRenderState {
  class ViewportRenderStateClass : ViewportRenderStateStruct
  {
  public:


    // The one that is called from outside
    int isValidXY(int x, int y) {
    #if !defined(REIMPLEMENT_IF_AVAILABLE) && !defined(REIMPLEMENT_ViewportRendererState_isValidXY) && !defined(REIMPLEMENT_0x401000)
      // No reimplementation defined, so call the original
      return this->_isValidXY(x, y);
    #else

      // The reimplementation. In this case, this reimplementation produces the exact same machine code.
      return (x < MAP_XY_LIMIT) && (y < MAP_XY_LIMIT) && this->validTiles[y *     MAP_XY_LIMIT + x] == 1;
      
    #endif
    }

    // The invocation to the original nicely wrapped
    int _isValidXY(int x, int y) {
      // This calls the original isValidXY logic
      // This is optimized to a jmp in x86! (/O2)
      return MemberFunctionPointer_InvokeMethod(_ViewportRenderStateClass,
          _isValidXY, x, y
      );
    }

    int translateXYToTile(int x, int y);
  };
}
```

#### Shim classes
For each class there is also a "shim" class used to trick the C++ compiler into executing method function pointers (i.e. to make the macro work). It contains only virtual functions without any implementations.
```cpp
#pragma once
namespace ViewportRenderState {

    // Class containing the virtual functions so we can access
    // the original game's class member functions
    class _ViewportRenderStateClass {
    public:

        // The original game code's version of this function
        // Every virtual function must not be directly called
        virtual int _isValidXY(int x, int y);

        virtual int _translateXYToTile(int x, int y);
    };
}
```

#### Macros for singletons and method pointers
Then, to be able to use the original game code, functions pointers and a singleton pointer to the class are declared and defined. Macros take care of this part:
```cpp
#pragma once


namespace ViewportRenderState {


    /*
        Singleton pointer
    */
    MemberFunctionPointer_DefineSingleton(ViewportRenderStateClass, ADDRESS_ViewportRendererState_Singleton);

    /*
        isValidXY
    */
    MemberFunctionPointer_DefineProcType(ViewportRenderStateClass, _isValidXY, int, int x, int y);
    MemberFunctionPointer_DefineMethodType(ViewportRenderStateClass, _isValidXY, int, int x, int y);
    MemberFunctionPointer_DefineMethodCast(ViewportRenderStateClass, _isValidXY);
    MemberFunctionPointer_DefineThiscallType(ViewportRenderStateClass, _isValidXY, int, int x, int y);
    MemberFunctionPointer_DefineThiscall(ViewportRenderStateClass, _isValidXY, int, int x, int y);

    MemberFunctionPointer_DefineProcType(_ViewportRenderStateClass, _isValidXY, int, int x, int y);
    MemberFunctionPointer_DefineMethodType(_ViewportRenderStateClass, _isValidXY, int, int x, int y);
    MemberFunctionPointer_DefineMethodCast(_ViewportRenderStateClass, _isValidXY);
    MemberFunctionPointer_DefineMethodPointer(_ViewportRenderStateClass, _isValidXY, ADDRESS_ViewportRendererState_isValidXY);


    /*
        translateXYToTile
    */
    MemberFunctionPointer_DefineProcType(ViewportRenderStateClass, _translateXYToTile, int, int x, int y);
    MemberFunctionPointer_DefineMethodType(ViewportRenderStateClass, _translateXYToTile, int, int x, int y);
    MemberFunctionPointer_DefineMethodCast(ViewportRenderStateClass, _translateXYToTile);
    MemberFunctionPointer_DefineThiscallType(ViewportRenderStateClass, _translateXYToTile, int, int x, int y);
    MemberFunctionPointer_DefineThiscall(ViewportRenderStateClass, _translateXYToTile, int, int x, int y);

    MemberFunctionPointer_DefineProcType(_ViewportRenderStateClass, _translateXYToTile, int, int x, int y);
    MemberFunctionPointer_DefineMethodType(_ViewportRenderStateClass, _translateXYToTile, int, int x, int y);
    MemberFunctionPointer_DefineMethodCast(_ViewportRenderStateClass, _translateXYToTile);
    MemberFunctionPointer_DefineMethodPointer(_ViewportRenderStateClass, _translateXYToTile, ADDRESS_ViewportRendererState_translateXYToTile);
}
```

## Unfinished concepts and to-do's
### High priority
#### Detours and hooks
To permit easier reimplementation in a gradual way, individual methods should be detourable from the original game to the new definition. This can be achieved by either:
1. patching the call to the original method so it goes to the reimplementation, or
2. by hooking the original method so it detours to the reimplemented method.

The latter needs some thought to avoid infinite loops. Basically, `_isValidXY` would not optimize to a jmp because the location of the detour trampoline is only known at runtime, not at compile time. Thus `MemberFunctionPointer_DefineMethodPointer` needs a variation to deal with this case (which shouldn't be too hard...).