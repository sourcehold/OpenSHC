#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

#include "TypeUtility.h"

struct StructResolver {
private:
    template <typename T, int gameAddress> struct Instance;

    template <typename T, int gameAddress> struct Extern {
        static T instance;
        static T* const ptr;
    };

    template <typename T, bool implemented, int gameAddress> struct InternalResolver;
    template <typename T, int gameAddress> struct InternalResolver<T, true, gameAddress> {
        typedef typename Instance<T, gameAddress> Holder;
    };
    template <typename T, int gameAddress> struct InternalResolver<T, false, gameAddress> {
        typedef typename Extern<T, gameAddress> Holder;
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
        typedef typename InternalResolver<T, isImplemented, gameAddress>::Holder Holder;
    };
};

template <typename T, int address> T* const StructResolver::Extern<T, address>::ptr = &instance;

template <int address> bool StructResolver::AddressUsageKeeper<address>::initialized = false;

template <typename T, bool implemented, int gameAddress>
typename StructResolver::Resolver<T, implemented, gameAddress>::Initializer const
    StructResolver::Resolver<T, implemented, gameAddress>::initializer;

template <typename T, bool implemented, int gameAddress>
StructResolver::Resolver<T, implemented, gameAddress>::Initializer::Initializer()
{
    initialize(AddressUsageKeeper<gameAddress>::initialized, isImplemented, gameAddress, Holder::ptr, getTypeName<T>());
}

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    template struct StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>;                                  \
    typedef StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Holder

#define MACRO_STRUCT_INSTANCE(GAME_ADDRESS)                                                                            \
    template <typename T> struct StructResolver::Instance<T, GAME_ADDRESS> {                                           \
        static T instance;                                                                                             \
        static T* const ptr;                                                                                           \
    };                                                                                                                 \
    template <typename T> T* const StructResolver::Instance<T, GAME_ADDRESS>::ptr = &instance;                         \
    template <typename T> T StructResolver::Instance<T, GAME_ADDRESS>::instance

#endif // STRUCT_RESOLVER
