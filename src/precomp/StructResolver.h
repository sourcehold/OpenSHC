#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

#include "TypeUtility.h"

struct StructResolver {
private:
    template <typename T, int gameAddress> struct Instance;

    template <typename T, int gameAddress> struct Extern {
        static T instance;
    };

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
        bool& initialized, bool isImplemented, int gameAddress, void const* structPtr, char const* typeName);

public:
    template <typename T, bool implemented, int gameAddress> struct Resolver {
    private:
        // only use this for internal logic and declarations/definitions
        static bool const isImplemented = OPEN_SHC_IMPLEMENTED(implemented);

        struct Initializer {
            Initializer();
        };
        static Initializer const initializer;

    public:
        typedef typename InternalResolver<T, isImplemented, gameAddress> Ptr;
    };
};

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, false, gameAddress>::ptr
    = &StructResolver::Extern<T, gameAddress>::instance;

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, true, gameAddress>::ptr
    = &StructResolver::Instance<T, gameAddress>::instance;

template <int address> bool StructResolver::AddressUsageKeeper<address>::initialized = false;

template <typename T, bool implemented, int gameAddress>
typename StructResolver::Resolver<T, implemented, gameAddress>::Initializer const
    StructResolver::Resolver<T, implemented, gameAddress>::initializer;

template <typename T, bool implemented, int gameAddress>
StructResolver::Resolver<T, implemented, gameAddress>::Initializer::Initializer()
{
    initialize(AddressUsageKeeper<gameAddress>::initialized, isImplemented, gameAddress, Ptr::ptr, getTypeName<T>());
}

// TODO: rather then adding a template to hold the ref which would require a long mangled name,
//   if we have a generatable name, we use a macro to define an extern C and use this instead.
//   In this case, the asm file only needs to be touched if the general constract of the address changes
//   and should we only ever use the addresses of the globals, this might be never.
//   However, if filtered and generated names are required, maybe it could also be possible to create a generator for
//   the more complicated mangled names? Any general type change would need to also adept the ASM file.

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    template struct StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>;                                  \
    typedef StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Ptr

#define MACRO_STRUCT_INSTANCE(GAME_ADDRESS)                                                                            \
    template <typename T> struct StructResolver::Instance<T, GAME_ADDRESS> {                                           \
        static T instance;                                                                                             \
    };                                                                                                                 \
    template <typename T> T StructResolver::Instance<T, GAME_ADDRESS>::instance

#endif // STRUCT_RESOLVER
