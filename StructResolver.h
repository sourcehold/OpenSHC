#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

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

public:
    template <typename T, bool implemented, int gameAddress> struct Resolver {
        typedef typename InternalResolver<T, implemented, gameAddress> Ptr;
    };
};

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, false, gameAddress>::ptr = reinterpret_cast<T*>(gameAddress);
template <typename T, int gameAddress>
T StructResolver::InternalResolver<T, true, gameAddress>::instance = StructResolver::instance<T, gameAddress>();
template <typename T, int gameAddress> T* const StructResolver::InternalResolver<T, true, gameAddress>::ptr = &instance;

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS)                                                  \
    typedef StructResolver::Resolver<STRUCT_TYPE, IMPLEMENTED, GAME_ADDRESS>::Ptr

#define MACRO_STRUCT_INSTANCE(STRUCT_TYPE, GAME_ADDRESS)                                                               \
    template <> STRUCT_TYPE StructResolver::instance<STRUCT_TYPE, GAME_ADDRESS>()

#endif // STRUCT_RESOLVER
