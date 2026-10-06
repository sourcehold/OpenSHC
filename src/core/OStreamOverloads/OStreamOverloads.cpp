#ifdef OPEN_SHC_DLL

#include "OStreamOverloadsSupport.cpp" // provides support implementations

/*
    Include overload implementations here:
    - The overload needs to be defined in OStreamOverloads.hpp.
    - Implementation files should use "same" include directory as the header but relative to OStreamOverloads.cpp.
    - Files should contain: the overload, the include for the type and an include for "OStreamOverloadsSupport.hpp".
    - Support functions, macros and ostream imports are provided by and should be added to OStreamOverloadsSupport.hpp
      and implemented in OStreamOverloadsSupport.cpp.
*/
#include "./OpenSHC/Audio/mss/UnkSoundFlagsAndLoopCount.cpp"

#endif // OPEN_SHC_DLL
