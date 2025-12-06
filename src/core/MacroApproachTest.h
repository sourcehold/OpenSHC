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
// using a body macro might be trick with inline assembly macros, had weird errors during tests
#define JMP_TO_GAME(DECLARATION, ADDR)                                                                                 \
    __declspec(naked) DECLARATION { __asm mov eax, ADDR __asm jmp eax }

namespace Address {
enum {
    F_00401040 = 0x00401040,
};
}

// apparently, another way to force init code is adding function ptrs to .CRT$XCU
// #pragma section(".CRT$XCU", read)
//__declspec(allocate(".CRT$XCU")) void(*pInit)() = myInitFunction;

struct Initializer {
private:
    template <int address> struct AddressUsageKeeper {
        static bool initialized;
    };

    static void initializeStruct(
        bool& initialized, bool isImplemented, int gameAddress, const void* structPtr, const char* structName);

    static void initializeFunction(
        bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName);

public:
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
