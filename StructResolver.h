#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

struct StructResolver {
private:
    template <typename T, int gameAddress> struct Instance {
        static T instance;
    };

    template <typename T, bool implemented, int gameAddress> struct InternalResolver;
    template <typename T, int gameAddress> struct InternalResolver<T, true, gameAddress> {
        static T* const ptr;
    };
    template <typename T, int gameAddress> struct InternalResolver<T, false, gameAddress> {
        static T* const ptr;
    };

public:
    template <typename T, bool implemented, int gameAddress> struct Resolver {
        typedef typename InternalResolver<T, implemented, gameAddress> Ptr;
    };
};

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, false, gameAddress>::ptr = reinterpret_cast<T*>(gameAddress);
template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, true, gameAddress>::ptr = &Instance<T, gameAddress>::instance;

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    typedef StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Ptr

#endif // STRUCT_RESOLVER
