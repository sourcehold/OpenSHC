#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

#include "TypeUtility.h"

struct StructResolver {
private:
    template <typename T, int gameAddress> struct Instance;

    template <typename T, bool implemented, int gameAddress> struct InternalResolver;
    template <typename T, int gameAddress> struct InternalResolver<T, true, gameAddress> {
        static T* const ptr;
    };
    template <typename T, int gameAddress> struct InternalResolver<T, false, gameAddress> {
        static T* const ptr;
    };

    template <int address> struct AddressUsageKeeper {
        static bool initialized;
    };

    static void initialize(
        bool& initialized, bool isImplemented, int gameAddress, const void* structPtr, const char* typeName);

public:
    template <typename T, bool implemented, int gameAddress> struct Resolver {
    private:
        // only use this for internal logic and declarations/definitions
        static const bool isImplemented = OPEN_SHC_IMPLEMENTED(implemented);

        struct Initializer {
            Initializer();
        };
        static const Initializer initializer;

    public:
        typedef typename InternalResolver<T, isImplemented, gameAddress> Ptr;
    };
};

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, false, gameAddress>::ptr = reinterpret_cast<T*>(gameAddress);

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, true, gameAddress>::ptr
    = &StructResolver::Instance<T, gameAddress>::instance;

template <int address> bool StructResolver::AddressUsageKeeper<address>::initialized = false;

template <typename T, bool implemented, int gameAddress>
const typename StructResolver::Resolver<T, implemented, gameAddress>::Initializer
    StructResolver::Resolver<T, implemented, gameAddress>::initializer;

template <typename T, bool implemented, int gameAddress>
StructResolver::Resolver<T, implemented, gameAddress>::Initializer::Initializer()
{
    initialize(AddressUsageKeeper<gameAddress>::initialized, isImplemented, gameAddress, Ptr::ptr, getTypeName<T>());
}

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    template struct StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>;                                  \
    typedef StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Ptr

#define MACRO_STRUCT_INSTANCE(GAME_ADDRESS)                                                                            \
    template <typename T> struct StructResolver::Instance<T, GAME_ADDRESS> {                                           \
        static T instance;                                                                                             \
    };                                                                                                                 \
    template <typename T> T StructResolver::Instance<T, GAME_ADDRESS>::instance

#endif // STRUCT_RESOLVER
