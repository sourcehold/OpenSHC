#ifndef STRUCT_RESOLVER
#define STRUCT_RESOLVER

// could be defined via other methods, or could use entirely different compile parameter
#define MACRO_USE_OWN_STRUCT true

struct StructResolver {
private:
    template <typename T, int gameAddress, bool useOwnStruct = true> struct InternalResolver;
    template <typename T, int gameAddress> struct InternalResolver<T, gameAddress, true> {
    private:
        static T obj;

    public:
        static T* const ptr;
    };
    template <typename T, int gameAddress> struct InternalResolver<T, gameAddress, false> {
        static T* const ptr;
    };

public:
    template <typename T, int gameAddress> struct Resolver {
        typedef typename InternalResolver<T, gameAddress, MACRO_USE_OWN_STRUCT> Ptr;
    };
};

template <typename T, int gameAddress>
T* const StructResolver::InternalResolver<T, gameAddress, false>::ptr = reinterpret_cast<T*>(gameAddress);
template <typename T, int gameAddress> T* const StructResolver::InternalResolver<T, gameAddress, true>::ptr = &obj;

#undef MACRO_USE_OWN_STRUCT

#define MACRO_STRUCT_RESOLVER(STRUCT_TYPE, GAME_ADDRESS)                                                               \
    typedef StructResolver::Resolver<STRUCT_TYPE, GAME_ADDRESS>::Ptr

#endif // STRUCT_RESOLVER
