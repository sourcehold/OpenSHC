#include "MacroApproachTest.h"

#include "ViewportRenderState.h"

// would need to be defined in every function case
// here, it causes no issues, and can even be undefined at the end
// it could even be left out completely, and the "safety" check and hooking via macro could be hardcoded at both
// conditions BUT issue:
// Structs need this switch in the header, but also in the implementation files, which would mean resolving and setting
// the implementation state twice, if not moved to a central position, where the naming could be an issue again (a
// central file would trigger recomp for everything, so that would be bad)
// the macro in the header could also used to define a macro to indicate that the struct definition should happen, but
// these would also need to be unique for the specific struct
#define IMPLEMENTED CHECK_IMPLEMENTED(TRUE)

// using macro to run init, requires also complete definition of type, otherwise we can not pass the function pointer

/* example using the template: */
// template struct Initializer::FunctionInitializer<int (ViewportRenderState::*)(int, int), IMPLEMENTED,
//    Address::F_00401040, &ViewportRenderState::translateXYToTile>;

/* example using a start up function: */
STARTUP_FUNCTION(initViewportRenderStateTranslateXYToTile,
    INIT_FUNCTION_BODY(int (ViewportRenderState::*)(int, int), IMPLEMENTED, Address::F_00401040,
        &ViewportRenderState::translateXYToTile))

#if IMPLEMENTED

// FUNCTION: STRONGHOLDCRUSADER 0x00401040
int ViewportRenderState::translateXYToTile(int x, int y) { return this->translationMatrix[y].addXgetTile + x; }

#else // !IMPLEMENTED

using namespace Address;
JMP_TO_GAME(int ViewportRenderState::translateXYToTile(int x, int y), F_00401040)

// of course, if generated anyway a helper macro could be omitted, but "using" the address namespace would be needed
// anyway

// would convert to a jmp, but would require to define the ptr type for all functions and consider the thiscall !=
// memberfunc difference
// could also use the template created for the function resolver that can take a function pointer type and transform
// it to another function type, although member ptr always require their class at the moment
// int ViewportRenderState::translateXYToTile(int x, int y)
//{
//    return ((int(__thiscall*)(ViewportRenderState*, int, int))Address::F_00401040)(this, x, y);
//}

#endif

#undef IMPLEMENTED

// even if everything is stripped out and the init done by an explicit inti function, we would have issues with the
// structs needing a definition for implemented and none for not in both header and implementation file
// in fact, the structs would not really need a definition at all if the struct is not implemented
// There could be a case that works on file level, but that runs into the issue with the structs once again, since they
// would still require the separation in the header, which would mean still two positions

// another way could be to simple generate a macro for the structs, or even for the functions
// the functions could have it here, but the structs would need it in their headers, essentially
// <name_enum_uppercase>_IMPLEMENTED and the the bool indicator
