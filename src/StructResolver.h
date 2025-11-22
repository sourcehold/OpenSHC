#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

#include "CompileMacros.h"
#include "TypeUtility.h"

#include <ios>

struct StructResolver {
private:
    template <typename T, int gameAddress> static T instance();

    template <typename T, bool implemented, int gameAddress> struct InternalResolver;
    template <typename T, int gameAddress> struct InternalResolver<T, true, gameAddress> {
    private:
        static T instance;

    public:
        static T* const ptr;
    };
    template <typename T, int gameAddress> struct InternalResolver<T, false, gameAddress> {
        static T* const ptr;
    };

    template <int address> struct AddressUsageKeeper {
        static bool initialized;
    };

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
T StructResolver::InternalResolver<T, true, gameAddress>::instance = StructResolver::instance<T, gameAddress>();
template <typename T, int gameAddress> T* const StructResolver::InternalResolver<T, true, gameAddress>::ptr = &instance;

template <int address> bool StructResolver::AddressUsageKeeper<address>::initialized = false;

template <typename T, bool implemented, int gameAddress>
const typename StructResolver::Resolver<T, implemented, gameAddress>::Initializer
    StructResolver::Resolver<T, implemented, gameAddress>::initializer;

template <typename T, bool implemented, int gameAddress>
StructResolver::Resolver<T, implemented, gameAddress>::Initializer::Initializer()
{
    if (AddressUsageKeeper<gameAddress>::initialized) {
        std::cout << "TODO: do something if struct already initialized\n";
        return;
    }
    AddressUsageKeeper<gameAddress>::initialized = true;

    // other then with the functions, there is only a usage check to be performed, so maybe for debug logs?
    if (isImplemented) {
        std::cout << "Implemented '" << (void*)gameAddress << "' at address '" << Ptr::ptr << "' as a '"
                  << getTypeName<T>() << "'\n";
    } else {
        std::cout << "Use '" << (void*)gameAddress << "' as a '" << getTypeName<T>() << "'\n";
    }
}

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    template struct StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>;                                  \
    typedef StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Ptr

#define MACRO_STRUCT_INSTANCE(STRUCT_TYPE, GAME_ADDRESS)                                                               \
    template <> STRUCT_TYPE StructResolver::instance<STRUCT_TYPE, GAME_ADDRESS>()

#endif // STRUCT_RESOLVER
