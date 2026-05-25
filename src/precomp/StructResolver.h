#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

#include "TypeUtility.h"

struct StructResolver {
private:
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

        template <bool implemented, typename _> struct Instance;
        template <typename _> struct Instance<true, _> {
            inline T* const get() { return &instance; }

            Instance();

        private:
            T instance;
        };
        template <typename _> struct Instance<false, _> {
            inline static T* const get() { return reinterpret_cast<T* const>(gameAddress); }
            static T* const ptr;

            Instance();
        };

    public:
        typedef Instance<isImplemented, void> Type;
    };
};

template <typename T, bool implemented, int gameAddress>
template <typename _>
StructResolver::Resolver<T, implemented, gameAddress>::Instance<false, _>::Instance()
{
    initialize(AddressUsageKeeper<gameAddress>::initialized, isImplemented, gameAddress, this->get(), getTypeName<T>());
}

template <typename T, bool implemented, int gameAddress>
template <typename _>
T* const StructResolver::Resolver<T, implemented, gameAddress>::Instance<false, _>::ptr
    = reinterpret_cast<T* const>(gameAddress);

template <int address> bool StructResolver::AddressUsageKeeper<address>::initialized = false;

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    template struct StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>;                                  \
    StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Type

// TODO: Currently not split between game addresses, would need further specialization
#define MACRO_STRUCT_INSTANCE(GAME_ADDRESS, INSTANCE)                                                                  \
    template <typename T, bool implemented, int gameAddress>                                                           \
    template <typename _>                                                                                              \
    StructResolver::Resolver<T, implemented, gameAddress>::Instance<true, _>::Instance()                               \
        : instance(INSTANCE)                                                                                           \
    {                                                                                                                  \
        initialize(                                                                                                    \
            AddressUsageKeeper<gameAddress>::initialized, isImplemented, gameAddress, this->get(), getTypeName<T>());  \
    };

#endif // STRUCT_RESOLVER
