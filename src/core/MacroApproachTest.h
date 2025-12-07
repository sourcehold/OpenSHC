#pragma once

#define TRUE 1
#define FALSE 0

#ifdef OPEN_SHC_DLL
#define CHECK_IMPLEMENTED(IMPLEMENTED) IMPLEMENTED
#endif

// would be always "TRUE" in real scenario
#ifdef OPEN_SHC_EXE
#define CHECK_IMPLEMENTED(IMPLEMENTED) TRUE
#endif

// Enums can only be used, if they are simple values, so the namespace needs to be removed or not even used (addresses
// as simple macros in global namespace)
// using a body macro might be tricky with inline assembly macros, had weird errors during tests
#define JMP_TO_GAME(DECLARATION, ADDR)                                                                                 \
    __declspec(naked) DECLARATION { __asm mov eax, ADDR __asm jmp eax }

// example for macro that could create a MICROSOFT startup function
// execution apparently in name order? If the name is not important, it could also be possible to generate the name from
// something (or random) or place it in an anonymous namespace, that being said, if only function hooking should be done
// this way, the macro could also completely generate the code
#define STARTUP_FUNCTION(NAME, BODY)                                                                                   \
    static void NAME() BODY __pragma(section(".CRT$XCU", read))                                                        \
        __declspec(allocate(".CRT$XCU")) void (*_init_##NAME)()                                                        \
        = NAME;

// taken from std::type_identity, which only becomes available with C++20+
template <typename T> struct type_identity {
    typedef T type;
};

// example for generating the init body
#define INIT_FUNCTION_BODY(TYPE, IMPLEMENTED, GAME_ADDRESS, POINTER)                                                   \
    {                                                                                                                  \
        const type_identity<TYPE>::type funcPtr = POINTER;                                                             \
        Initializer::initializeFunction(Initializer::AddressUsageKeeper<GAME_ADDRESS>::initialized, IMPLEMENTED,       \
            GAME_ADDRESS, *((void**)&funcPtr), getFuncPtrName<TYPE, POINTER>());                                       \
    }

// for testing only
namespace Address {
enum {
    F_00401040 = 0x00401040,
};
}

// apparently, another way to force init code is adding function ptrs to .CRT$XCU
// #pragma section(".CRT$XCU", read)
//__declspec(allocate(".CRT$XCU")) void(*pInit)() = myInitFunction;

struct Initializer {
public: // everything is public, but only for testing
    template <int address> struct AddressUsageKeeper {
        static bool initialized;
    };

    static void initializeStruct(
        bool& initialized, bool isImplemented, int gameAddress, const void* structPtr, const char* structName);

    static void initializeFunction(
        bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName);

    template <typename T, bool implemented, int gameAddress, T* structAddress> struct StructInitializer {
    private:
        struct Init {
            Init();
        };
        static const Init init;
    };

    template <typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress>
    struct FunctionInitializer {
    private:
        struct Init {
            Init();
        };
        static const Init init;
    };
};

template <int address> bool Initializer::AddressUsageKeeper<address>::initialized = false;

template <typename T, bool implemented, int gameAddress, T* structAddress>
Initializer::StructInitializer<T, implemented, gameAddress, structAddress>::Init::Init()
{
    initializeStruct(
        AddressUsageKeeper<gameAddress>::initialized, implemented, gameAddress, structAddress, getTypeName<T>());
}

template <typename T, bool implemented, int gameAddress, T* structAddress>
const typename Initializer::StructInitializer<T, implemented, gameAddress, structAddress>::Init
    Initializer::StructInitializer<T, implemented, gameAddress, structAddress>::init;

template <typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress>
Initializer::FunctionInitializer<FuncPtrType, implemented, gameAddress, funcAddress>::Init::Init()
{
    const FuncPtrType funcPtr = funcAddress;
    const void* func = *((void**)&funcPtr);
    initializeFunction(AddressUsageKeeper<gameAddress>::initialized, implemented, gameAddress, func,
        getFuncPtrName<FuncPtrType, funcAddress>());
}

template <typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress>
const typename Initializer::FunctionInitializer<FuncPtrType, implemented, gameAddress, funcAddress>::Init
    Initializer::FunctionInitializer<FuncPtrType, implemented, gameAddress, funcAddress>::init;
