#ifndef FUNCTION_RESOLVER
#define FUNCTION_RESOLVER

// NOTE: Changed CDECL tp CCALL to avoid window macro issue
// TODO: Maybe change naming convention to not run into these issues

#include "CompileMacros.h"
#include "TypeUtility.h"

#include "ucp3.h"

#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#define M_SPACE
#define M_COMMA ,

// Force macro argument to expand BEFORE token-pasting
// otherwise it would not expand and glue any macro number to the function name
#define MACRO_GLUE(A, B) A##B

// recursive macros are not possible in C++ (there are hacky workarounds online, but in theory they are hacks)
// there is a strict ordering imposed, so try to use the lowest level possible, and then use the next level if needed
#define MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO, DELIM) MACRO_GLUE(MACRO_INDEX_ITERATE_, N)(MACRO, DELIM)
#define MACRO_INDEX_ITERATE_DEPTH_1(N, MACRO, DELIM) MACRO_GLUE(MACRO_INDEX_ITERATE_, N)(MACRO, DELIM)
#define MACRO_INDEX_ITERATE_DEPTH_2(N, MACRO, DELIM) MACRO_GLUE(MACRO_INDEX_ITERATE_, N)(MACRO, DELIM)

#define MACRO_INDEX_ITERATE_0(M, D)
#define MACRO_INDEX_ITERATE_1(M, D) M(0)
#define MACRO_INDEX_ITERATE_2(M, D) M(0) D M(1)
#define MACRO_INDEX_ITERATE_3(M, D) M(0) D M(1) D M(2)
#define MACRO_INDEX_ITERATE_4(M, D) M(0) D M(1) D M(2) D M(3)
#define MACRO_INDEX_ITERATE_5(M, D) M(0) D M(1) D M(2) D M(3) D M(4)
#define MACRO_INDEX_ITERATE_6(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5)
#define MACRO_INDEX_ITERATE_7(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6)
#define MACRO_INDEX_ITERATE_8(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7)
#define MACRO_INDEX_ITERATE_9(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8)
#define MACRO_INDEX_ITERATE_10(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9)
#define MACRO_INDEX_ITERATE_11(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9) D M(10)
#define MACRO_INDEX_ITERATE_12(M, D) M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9) D M(10) D M(11)
#define MACRO_INDEX_ITERATE_13(M, D)                                                                                   \
    M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9) D M(10) D M(11) D M(12)
#define MACRO_INDEX_ITERATE_14(M, D)                                                                                   \
    M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9) D M(10) D M(11) D M(12) D M(13)
#define MACRO_INDEX_ITERATE_15(M, D)                                                                                   \
    M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9) D M(10) D M(11) D M(12) D M(13) D M(14)
#define MACRO_INDEX_ITERATE_16(M, D)                                                                                   \
    M(0) D M(1) D M(2) D M(3) D M(4) D M(5) D M(6) D M(7) D M(8) D M(9) D M(10) D M(11) D M(12) D M(13) D M(14) D M(15)

#define MACRO_PARAMETER_TYPE(N) Arg##N
#define MACRO_PARAMETER(N) arg##N
#define MACRO_PARAMETER_TYPENAME(N) typename MACRO_PARAMETER_TYPE(N)
#define MACRO_PARAMETER_TYPE_PARAMETER(N) MACRO_PARAMETER_TYPE(N) MACRO_PARAMETER(N)
#define MACRO_PARAMETER_TYPE_WITH_COMMA_PREFIX(N) M_COMMA MACRO_PARAMETER_TYPE(N)
#define MACRO_PARAMETER_WITH_COMMA_PREFIX(N) M_COMMA MACRO_PARAMETER(N)
#define MACRO_PARAMETER_TYPENAME_WITH_COMMA_PREFIX(N) M_COMMA typename MACRO_PARAMETER_TYPE(N)
#define MACRO_PARAMETER_TYPE_PARAMETER_WITH_COMMA_PREFIX(N) M_COMMA MACRO_PARAMETER_TYPE(N) MACRO_PARAMETER(N)

// depth 0 macros
#define MACRO_PARAMETER_TYPE_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_TYPE, M_COMMA)
#define MACRO_PARAMETER_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER, M_COMMA)
#define MACRO_PARAMETER_TYPENAME_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_TYPENAME, M_COMMA)
#define MACRO_PARAMETER_TYPE_PARAMETER_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_TYPE_PARAMETER, M_COMMA)
#define MACRO_PARAMETER_TYPE_LIST_WITH_COMMA_PREFIX(N)                                                                 \
    MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_TYPE_WITH_COMMA_PREFIX, M_SPACE)
#define MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N)                                                                      \
    MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_WITH_COMMA_PREFIX, M_SPACE)
#define MACRO_PARAMETER_TYPENAME_LIST_WITH_COMMA_PREFIX(N)                                                             \
    MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_TYPENAME_WITH_COMMA_PREFIX, M_SPACE)
#define MACRO_PARAMETER_TYPE_PARAMETER_LIST_WITH_COMMA_PREFIX(N)                                                       \
    MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_TYPE_PARAMETER_WITH_COMMA_PREFIX, M_SPACE)

#define MACRO_FUNC_PTR_CCALL(RET, NAME, ARG_NUMBER) RET(__cdecl* NAME)(MACRO_PARAMETER_TYPE_LIST(ARG_NUMBER))
#define MACRO_FUNC_PTR_STDCALL(RET, NAME, ARG_NUMBER) RET(__stdcall* NAME)(MACRO_PARAMETER_TYPE_LIST(ARG_NUMBER))
#define MACRO_FUNC_PTR_MEMBER(RET, CLASS, NAME, ARG_NUMBER) RET (CLASS::*NAME)(MACRO_PARAMETER_TYPE_LIST(ARG_NUMBER))
#define MACRO_FUNC_PTR_THISCALL(RET, CLASS, NAME, ARG_NUMBER)                                                          \
    RET(__thiscall* NAME)(CLASS * MACRO_PARAMETER_TYPE_LIST_WITH_COMMA_PREFIX(ARG_NUMBER))
#define MACRO_FUNC_PTR_TYPE_CCALL(RET, ARG_NUMBER) MACRO_FUNC_PTR_CCALL(RET, M_SPACE, ARG_NUMBER)
#define MACRO_FUNC_PTR_TYPE_STDCALL(RET, ARG_NUMBER) MACRO_FUNC_PTR_STDCALL(RET, M_SPACE, ARG_NUMBER)
#define MACRO_FUNC_PTR_TYPE_MEMBER(RET, CLASS, ARG_NUMBER) MACRO_FUNC_PTR_MEMBER(RET, CLASS, M_SPACE, ARG_NUMBER)
#define MACRO_FUNC_PTR_TYPE_THISCALL(RET, CLASS, ARG_NUMBER) MACRO_FUNC_PTR_THISCALL(RET, CLASS, M_SPACE, ARG_NUMBER)

#define MACRO_FUNC_TEMPLATE_HEADER(PRE, RET, ARG_NUMBER, POST)                                                         \
    template <PRE typename RET MACRO_PARAMETER_TYPENAME_LIST_WITH_COMMA_PREFIX(ARG_NUMBER) POST>
#define MACRO_CLASS_FUNC_TEMPLATE_HEADER(PRE, RET, CLASS, ARG_NUMBER, POST)                                            \
    template <PRE typename RET, typename CLASS MACRO_PARAMETER_TYPENAME_LIST_WITH_COMMA_PREFIX(ARG_NUMBER) POST>

// we are loosing one level due to the way the recursion iteration works
#define MACRO_SUPPORTED_PARAMETER_NUMBER 15
#define MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE 16

// no support for virtual function ptrs
struct FunctionResolver {
private:
    enum CallConvention { CC_CCALL, CC_STDCALL, CC_MEMBER, CC_THISCALL };

    template <typename FuncType> struct FuncTraits;

// using void as special case which falls back to void... not nice, but it allows to continue the logic
#define MACRO_FUNC_TRAITS_TRANSFROM_SUBSTRUCT(SAME_CONV, SAME_CONV_VOID, N)                                            \
    template <typename NewClass> struct Transform {                                                                    \
        SAME_CONV typedef MACRO_FUNC_PTR_CCALL(Ret, AsCdecl, N);                                                       \
        typedef MACRO_FUNC_PTR_STDCALL(Ret, AsStdcall, N);                                                             \
        typedef MACRO_FUNC_PTR_MEMBER(Ret, NewClass, AsMember, N);                                                     \
        typedef MACRO_FUNC_PTR_THISCALL(Ret, NewClass, AsThiscall, N);                                                 \
    };                                                                                                                 \
    template <> struct Transform<void> {                                                                               \
        SAME_CONV_VOID typedef MACRO_FUNC_PTR_CCALL(Ret, AsCdecl, N);                                                  \
        typedef MACRO_FUNC_PTR_STDCALL(Ret, AsStdcall, N);                                                             \
        typedef void AsMember;                                                                                         \
        typedef void AsThiscall;                                                                                       \
    };
#define MACRO_FUNC_TRAITS(N)                                                                                           \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_CCALL(Ret, N)> {                      \
        typedef MACRO_FUNC_PTR_CCALL(Ret, FuncType, N);                                                                \
        typedef Ret ReturnType;                                                                                        \
        typedef void ClassType;                                                                                        \
        static const CallConvention callConvention = CC_CCALL;                                                         \
        static const int argCount = N;                                                                                 \
        MACRO_FUNC_TRAITS_TRANSFROM_SUBSTRUCT(typedef FuncType AsSame;, typedef FuncType AsSame;, N)                   \
    };                                                                                                                 \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)> {                    \
        typedef MACRO_FUNC_PTR_STDCALL(Ret, FuncType, N);                                                              \
        typedef Ret ReturnType;                                                                                        \
        typedef void ClassType;                                                                                        \
        static const CallConvention callConvention = CC_STDCALL;                                                       \
        static const int argCount = N;                                                                                 \
        MACRO_FUNC_TRAITS_TRANSFROM_SUBSTRUCT(typedef FuncType AsSame;, typedef FuncType AsSame;, N)                   \
    };                                                                                                                 \
    MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N)> { \
        typedef MACRO_FUNC_PTR_MEMBER(Ret, Class, FuncType, N);                                                        \
        typedef Ret ReturnType;                                                                                        \
        typedef Class ClassType;                                                                                       \
        static const CallConvention callConvention = CC_MEMBER;                                                        \
        static const int argCount = N;                                                                                 \
        MACRO_FUNC_TRAITS_TRANSFROM_SUBSTRUCT(typedef MACRO_FUNC_PTR_MEMBER(Ret, NewClass, AsSame, N);                 \
            , typedef void AsSame;, N)                                                                                 \
    };                                                                                                                 \
    MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, )                                                                \
    struct FuncTraits<MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N)> {                                                   \
        typedef MACRO_FUNC_PTR_THISCALL(Ret, Class, FuncType, N);                                                      \
        typedef Ret ReturnType;                                                                                        \
        typedef Class ClassType;                                                                                       \
        static const CallConvention callConvention = CC_THISCALL;                                                      \
        static const int argCount = N;                                                                                 \
        MACRO_FUNC_TRAITS_TRANSFROM_SUBSTRUCT(typedef MACRO_FUNC_PTR_THISCALL(Ret, NewClass, AsSame, N);               \
            , typedef void AsSame;, N)                                                                                 \
    };
    MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_FUNC_TRAITS, M_SPACE)
#undef MACRO_FUNC_TRAITS
#undef MACRO_FUNC_TRAITS_TRANSFROM_SUBSTRUCT

    template <bool condition, typename IF, typename ELSE> struct TypeTernary;
    template <typename IF, typename ELSE> struct TypeTernary<true, IF, ELSE> {
        typedef IF Type;
    };
    template <typename IF, typename ELSE> struct TypeTernary<false, IF, ELSE> {
        typedef ELSE Type;
    };

    template <int address> struct AddressUsageKeeper {
        static bool initialized;
    };

    static void initialize(
        bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName);

    template <int options> struct OptionFlags {
        enum {
            USE_WRAPPER = !!(options & Option::USE_WRAPPER),
        };
    };

public:
    struct Option {
        enum {
            NONE = 0,
            USE_WRAPPER = 1,
        };
    };

    template <typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress,
        int options = Option::NONE>
    struct Resolver {
    private:
        // only use this for internal logic and declarations/definitions
        static const bool isImplemented = OPEN_SHC_IMPLEMENTED(implemented);

        typedef OptionFlags<options> Flags;

        struct Initializer {
            Initializer();
        };
        static const Initializer initializer;

        template <bool implemented, bool wrapper, typename _> struct FunctionPtrUnifier;
        template <typename _> struct FunctionPtrUnifier<true, false, _> {
            inline static const FuncPtrType get() { return funcAddress; }
        };
        template <bool implemented, typename _> struct FunctionPtrUnifier<implemented, true, _> {
            inline static const FuncPtrType get() { return reinterpret_cast<FuncPtrType>(&WrapperFunction::call); }
        };
        template <typename _> struct FunctionPtrUnifier<false, false, _> {
            inline static const FuncPtrType get() { return reinterpret_cast<FuncPtrType>(&GameCallerFunction::call); }
        };

        typedef FunctionPtrUnifier<isImplemented, false, void> UnifiedFunctionPtrForWrapper;

        template <typename FuncPtrType> struct Wrapper;

#define MACRO_SPACED_STREAM_PRINT_PARAMETER(N) << "\t" << MACRO_PARAMETER(N)
#define MACRO_SPACED_STREAM_PRINT_PARAMETER_LIST(N)                                                                    \
    MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_SPACED_STREAM_PRINT_PARAMETER, M_SPACE)

// TODO: Replace with proper logging with condition
#define MACRO_WRAPPER_BODY_PRECALL(N)                                                                                  \
    {                                                                                                                  \
        std::ostringstream ossParams;                                                                                  \
        if (isImplemented) {                                                                                           \
            ossParams << "Call: " << getFuncPtrName<FuncPtrType, funcAddress>() << " | Replaces: '" << std::hex        \
                      << gameAddress << std::dec << "' | Args(" << N << "): ";                                         \
        } else {                                                                                                       \
            ossParams << "Call from own function: " << std::hex << gameAddress << std::dec << "' | Args(" << N         \
                      << "): ";                                                                                        \
        }                                                                                                              \
        ossParams MACRO_SPACED_STREAM_PRINT_PARAMETER_LIST(N);                                                         \
        std::string strParams = ossParams.str();                                                                       \
        std::cout << strParams << '\n';                                                                                \
    }

#define MACRO_WRAPPER_BODY_POSTCALL(N)                                                                                 \
    {                                                                                                                  \
        std::ostringstream ossReturn;                                                                                  \
        if (isImplemented) {                                                                                           \
            ossReturn << "Call: " << getFuncPtrName<FuncPtrType, funcAddress>() << " | Replaces: '" << std::hex        \
                      << gameAddress << std::dec << "' | Returned:" << "\t" << ret;                                    \
        } else {                                                                                                       \
            ossReturn << "Call from own function: " << std::hex << gameAddress << std::dec << "' | Returned:" << "\t"  \
                      << ret;                                                                                          \
        }                                                                                                              \
        std::string strReturn = ossReturn.str();                                                                       \
        std::cout << strReturn << '\n';                                                                                \
    }

#define MACRO_WRAPPER_BODY_POSTCALL_VOID(N)                                                                            \
    {                                                                                                                  \
        std::ostringstream ossReturn;                                                                                  \
        if (isImplemented) {                                                                                           \
            ossReturn << "Call: " << getFuncPtrName<FuncPtrType, funcAddress>() << " | Replaces: '" << std::hex        \
                      << gameAddress << std::dec << "' | Returned";                                                    \
        } else {                                                                                                       \
            ossReturn << "Call from own function: " << std::hex << gameAddress << std::dec << "' | Returned";          \
        }                                                                                                              \
        std::string strReturn = ossReturn.str();                                                                       \
        std::cout << strReturn << '\n';                                                                                \
    }

#define MACRO_CALL_WRAPPER(N)                                                                                          \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_CCALL(Ret, N)> {                         \
    private:                                                                                                           \
        template <typename R, typename = void> struct CallHelper : public UnifiedFunctionPtrForWrapper {               \
            __declspec(noinline) static R __cdecl call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                         \
            {                                                                                                          \
                MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = get()(MACRO_PARAMETER_LIST(N));                                \
                MACRO_WRAPPER_BODY_POSTCALL(N) return ret;                                                             \
            }                                                                                                          \
        };                                                                                                             \
        template <typename _> struct CallHelper<void, _> : public UnifiedFunctionPtrForWrapper {                       \
            __declspec(noinline) static void __cdecl call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                      \
            {                                                                                                          \
                MACRO_WRAPPER_BODY_PRECALL(N) get()(MACRO_PARAMETER_LIST(N));                                          \
                MACRO_WRAPPER_BODY_POSTCALL_VOID(N)                                                                    \
            }                                                                                                          \
        };                                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        typedef CallHelper<Ret> Function;                                                                              \
    };                                                                                                                 \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)> {                       \
    private:                                                                                                           \
        template <typename R, typename = void> struct CallHelper : public UnifiedFunctionPtrForWrapper {               \
            __declspec(noinline) static R __stdcall call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                       \
            {                                                                                                          \
                MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = get()(MACRO_PARAMETER_LIST(N));                                \
                MACRO_WRAPPER_BODY_POSTCALL(N) return ret;                                                             \
            }                                                                                                          \
        };                                                                                                             \
        template <typename _> struct CallHelper<void, _> : public UnifiedFunctionPtrForWrapper {                       \
            __declspec(noinline) static void __stdcall call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                    \
            {                                                                                                          \
                MACRO_WRAPPER_BODY_PRECALL(N) get()(MACRO_PARAMETER_LIST(N));                                          \
                MACRO_WRAPPER_BODY_POSTCALL_VOID(N)                                                                    \
            }                                                                                                          \
        };                                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        typedef CallHelper<Ret> Function;                                                                              \
    };                                                                                                                 \
    MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N)> {    \
    private:                                                                                                           \
        template <typename R, typename = void> struct CallHelper : public UnifiedFunctionPtrForWrapper {               \
            __declspec(noinline) R call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                                        \
            {                                                                                                          \
                MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = (((Class*)(this))->*get())(MACRO_PARAMETER_LIST(N));           \
                MACRO_WRAPPER_BODY_POSTCALL(N) return ret;                                                             \
            }                                                                                                          \
        };                                                                                                             \
        template <typename _> struct CallHelper<void, _> : public UnifiedFunctionPtrForWrapper {                       \
            __declspec(noinline) void call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                                     \
            {                                                                                                          \
                MACRO_WRAPPER_BODY_PRECALL(N)(((Class*)(this))->*get())(MACRO_PARAMETER_LIST(N));                      \
                MACRO_WRAPPER_BODY_POSTCALL_VOID(N)                                                                    \
            }                                                                                                          \
        };                                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        typedef CallHelper<Ret> Function;                                                                              \
    };
        MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_CALL_WRAPPER, M_SPACE)
#undef MACRO_CALL_WRAPPER

#undef MACRO_WRAPPER_BODY_POSTCALL_VOID
#undef MACRO_WRAPPER_BODY_POSTCALL
#undef MACRO_WRAPPER_BODY_PRECALL

#undef MACRO_SPACED_STREAM_PRINT_PARAMETER_LIST
#undef MACRO_SPACED_STREAM_PRINT_PARAMETER

        typedef typename Wrapper<FuncPtrType>::Function WrapperFunction;

        template <typename FuncPtrType> struct GameCaller;

#define MACRO_GAME_CALLER(N)                                                                                           \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct GameCaller<MACRO_FUNC_PTR_TYPE_CCALL(Ret, N)> {                      \
    private:                                                                                                           \
        template <typename R, typename = void> struct CallHelper {                                                     \
            __declspec(noinline) static R __cdecl call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                         \
            {                                                                                                          \
                return ((MACRO_FUNC_PTR_TYPE_CCALL(Ret, N))gameAddress)(MACRO_PARAMETER_LIST(N));                      \
            }                                                                                                          \
        };                                                                                                             \
        template <typename _> struct CallHelper<void, _> {                                                             \
            __declspec(noinline) static void __cdecl call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                      \
            {                                                                                                          \
                ((MACRO_FUNC_PTR_TYPE_CCALL(Ret, N))gameAddress)(MACRO_PARAMETER_LIST(N));                             \
            }                                                                                                          \
        };                                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        typedef CallHelper<Ret> Function;                                                                              \
    };                                                                                                                 \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct GameCaller<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)> {                    \
    private:                                                                                                           \
        template <typename R, typename = void> struct CallHelper {                                                     \
            __declspec(noinline) static R __stdcall call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                       \
            {                                                                                                          \
                return ((MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N))gameAddress)(MACRO_PARAMETER_LIST(N));                    \
            }                                                                                                          \
        };                                                                                                             \
        template <typename _> struct CallHelper<void, _> {                                                             \
            __declspec(noinline) static void __stdcall call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                    \
            {                                                                                                          \
                ((MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N))gameAddress)(MACRO_PARAMETER_LIST(N));                           \
            }                                                                                                          \
        };                                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        typedef CallHelper<Ret> Function;                                                                              \
    };                                                                                                                 \
    MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct GameCaller<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N)> { \
    private:                                                                                                           \
        template <typename R, typename = void> struct CallHelper {                                                     \
            __declspec(noinline) R call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                                        \
            {                                                                                                          \
                return ((MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N))gameAddress)(                                     \
                    (Class*)this MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N));                                           \
            }                                                                                                          \
        };                                                                                                             \
        template <typename _> struct CallHelper<void, _> {                                                             \
            __declspec(noinline) void call(MACRO_PARAMETER_TYPE_PARAMETER_LIST(N))                                     \
            {                                                                                                          \
                ((MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N))gameAddress)(                                            \
                    (Class*)this MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N));                                           \
            }                                                                                                          \
        };                                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        typedef CallHelper<Ret> Function;                                                                              \
    };
        MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_GAME_CALLER, M_SPACE)
#undef MACRO_GAME_CALLER

        typedef typename GameCaller<FuncPtrType>::Function GameCallerFunction;

        typedef FunctionPtrUnifier<isImplemented, Flags::USE_WRAPPER, void> UnifiedFunctionPtr;

    public:
        typedef UnifiedFunctionPtr Function;
    };
};

template <int address> bool FunctionResolver::AddressUsageKeeper<address>::initialized = false;

template <typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress, int options>
const typename FunctionResolver::Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options>::Initializer
    FunctionResolver::Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options>::initializer;

template <typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress, int options>
FunctionResolver::Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options>::Initializer::Initializer()
{
    const FuncPtrType funcPtr = Function::get();
    const void* func = *((void**)&funcPtr);
    initialize(AddressUsageKeeper<gameAddress>::initialized, isImplemented, gameAddress, func,
        getFuncPtrName<FuncPtrType, funcAddress>());
}

#undef MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE
#undef MACRO_SUPPORTED_PARAMETER_NUMBER

#undef MACRO_CLASS_FUNC_TEMPLATE_HEADER
#undef MACRO_FUNC_TEMPLATE_HEADER

#undef MACRO_FUNC_PTR_TYPE_THISCALL
#undef MACRO_FUNC_PTR_TYPE_MEMBER
#undef MACRO_FUNC_PTR_TYPE_STDCALL
#undef MACRO_FUNC_PTR_TYPE_CCALL
#undef MACRO_FUNC_PTR_THISCALL
#undef MACRO_FUNC_PTR_MEMBER
#undef MACRO_FUNC_PTR_STDCALL
#undef MACRO_FUNC_PTR_CCALL

#undef MACRO_PARAMETER_TYPE_PARAMETER_LIST_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_TYPENAME_LIST_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_TYPE_LIST_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_TYPE_PARAMETER_LIST
#undef MACRO_PARAMETER_TYPENAME_LIST
#undef MACRO_PARAMETER_LIST
#undef MACRO_PARAMETER_TYPE_LIST

#undef MACRO_PARAMETER_TYPE_PARAMETER_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_TYPENAME_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_TYPE_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_TYPE_PARAMETER
#undef MACRO_PARAMETER_TYPENAME
#undef MACRO_PARAMETER
#undef MACRO_PARAMETER_TYPE

#undef MACRO_INDEX_ITERATE_16
#undef MACRO_INDEX_ITERATE_15
#undef MACRO_INDEX_ITERATE_14
#undef MACRO_INDEX_ITERATE_13
#undef MACRO_INDEX_ITERATE_12
#undef MACRO_INDEX_ITERATE_11
#undef MACRO_INDEX_ITERATE_10
#undef MACRO_INDEX_ITERATE_9
#undef MACRO_INDEX_ITERATE_8
#undef MACRO_INDEX_ITERATE_7
#undef MACRO_INDEX_ITERATE_6
#undef MACRO_INDEX_ITERATE_5
#undef MACRO_INDEX_ITERATE_4
#undef MACRO_INDEX_ITERATE_3
#undef MACRO_INDEX_ITERATE_2
#undef MACRO_INDEX_ITERATE_1
#undef MACRO_INDEX_ITERATE_0

#undef MACRO_INDEX_ITERATE_DEPTH_2
#undef MACRO_INDEX_ITERATE_DEPTH_1
#undef MACRO_INDEX_ITERATE_DEPTH_0

#undef MACRO_GLUE

#undef M_COMMA
#undef M_SPACE

// Helper Macro to support function definition
// Only provides the template instantiation and the typedef start, so add the same afterwards
#define MACRO_FUNCTION_RESOLVER(FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS)                            \
    MACRO_FUNCTION_RESOLVER_EXT(                                                                                       \
        FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, FunctionResolver::Option::NONE)
#define MACRO_FUNCTION_RESOLVER_EXT(FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, OPTIONS)               \
    template struct FunctionResolver::Resolver<FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, OPTIONS>;   \
    typedef FunctionResolver::Resolver<FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, OPTIONS>::Function

#define MACRO_CALL(RESOLVED_FUNCTION) (RESOLVED_FUNCTION::get())
#define MACRO_CALL_MEMBER(RESOLVED_FUNCTION, STRUCT_POINTER) (STRUCT_POINTER->*RESOLVED_FUNCTION::get())

#endif // FUNCTION_RESOLVER
