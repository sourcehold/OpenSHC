#ifndef COMPILE_MACROS
#define COMPILE_MACROS

// fail if none or both are defined
#if !defined(OPEN_SHC_DLL) && !defined(OPEN_SHC_EXE)
#error "Either OPEN_SHC_DLL or OPEN_SHC_EXE must be defined!"
#elif defined(OPEN_SHC_DLL) && defined(OPEN_SHC_EXE)
#error "Only one of OPEN_SHC_DLL or OPEN_SHC_EXE can be defined!"
#endif

// Support MACRO: If in EXE mode, it is assumed everything is implemented
#ifdef OPEN_SHC_DLL
#define OPEN_SHC_IMPLEMENTED(BOOL) BOOL
#endif
#ifdef OPEN_SHC_EXE
#define OPEN_SHC_IMPLEMENTED(BOOL) true
#endif

#endif // COMPILE_MACROS
