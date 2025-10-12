#ifndef FUNCTION_RESOLVER
#define FUNCTION_RESOLVER

#include <iostream>

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
#define MACRO_INDEX_ITERATE_2(M, D) M(0)D M(1)
#define MACRO_INDEX_ITERATE_3(M, D) M(0)D M(1)D M(2)
#define MACRO_INDEX_ITERATE_4(M, D) M(0)D M(1)D M(2)D M(3)
#define MACRO_INDEX_ITERATE_5(M, D) M(0)D M(1)D M(2)D M(3)D M(4)
#define MACRO_INDEX_ITERATE_6(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)
#define MACRO_INDEX_ITERATE_7(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)
#define MACRO_INDEX_ITERATE_8(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)
#define MACRO_INDEX_ITERATE_9(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)
#define MACRO_INDEX_ITERATE_10(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)
#define MACRO_INDEX_ITERATE_11(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)D M(10)
#define MACRO_INDEX_ITERATE_12(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)D M(10)D M(11)
#define MACRO_INDEX_ITERATE_13(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)D M(10)D M(11)D M(12)
#define MACRO_INDEX_ITERATE_14(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)D M(10)D M(11)D M(12)D M(13)
#define MACRO_INDEX_ITERATE_15(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)D M(10)D M(11)D M(12)D M(13)D M(14)
#define MACRO_INDEX_ITERATE_16(M, D) M(0)D M(1)D M(2)D M(3)D M(4)D M(5)D M(6)D M(7)D M(8)D M(9)D M(10)D M(11)D M(12)D M(13)D M(14)D M(15)

#define MACRO_ARG(N) Arg##N
#define MACRO_PARAMETER(N) arg##N
#define MACRO_TYPENAME_ARG(N) typename MACRO_ARG(N)
#define MACRO_ARG_PARAMETER(N) MACRO_ARG(N) MACRO_PARAMETER(N)
#define MACRO_ARG_WITH_COMMA_PREFIX(N) M_COMMA MACRO_ARG(N)
#define MACRO_PARAMETER_WITH_COMMA_PREFIX(N) M_COMMA MACRO_PARAMETER(N)
#define MACRO_TYPENAME_ARG_WITH_COMMA_PREFIX(N) M_COMMA typename MACRO_ARG(N)
#define MACRO_ARG_PARAMETER_WITH_COMMA_PREFIX(N) M_COMMA MACRO_ARG(N) MACRO_PARAMETER(N)

// depth 0 macros
#define MACRO_ARG_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_ARG, M_COMMA)
#define MACRO_PARAMETER_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER, M_COMMA)
#define MACRO_TYPENAME_ARG_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_TYPENAME_ARG, M_COMMA)
#define MACRO_ARG_PARAMETER_LIST(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_ARG_PARAMETER, M_COMMA)
#define MACRO_ARG_LIST_WITH_COMMA_PREFIX(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_ARG_WITH_COMMA_PREFIX, M_SPACE)
#define MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_PARAMETER_WITH_COMMA_PREFIX, M_SPACE)
#define MACRO_TYPENAME_ARG_LIST_WITH_COMMA_PREFIX(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_TYPENAME_ARG_WITH_COMMA_PREFIX, M_SPACE)
#define MACRO_ARG_PARAMETER_LIST_WITH_COMMA_PREFIX(N) MACRO_INDEX_ITERATE_DEPTH_0(N, MACRO_ARG_PARAMETER_WITH_COMMA_PREFIX, M_SPACE)

#define MACRO_FUNC_PTR_CDECL(RET, NAME, ARG_NUMBER) RET(__cdecl* NAME)(MACRO_ARG_LIST(ARG_NUMBER))
#define MACRO_FUNC_PTR_STDCALL(RET, NAME, ARG_NUMBER) RET(__stdcall* NAME)(MACRO_ARG_LIST(ARG_NUMBER))
#define MACRO_FUNC_PTR_MEMBER(RET, CLASS, NAME, ARG_NUMBER) RET(CLASS::* NAME)(MACRO_ARG_LIST(ARG_NUMBER))
#define MACRO_FUNC_PTR_THISCALL(RET, CLASS, NAME, ARG_NUMBER) RET(__thiscall* NAME)(CLASS* MACRO_ARG_LIST_WITH_COMMA_PREFIX(ARG_NUMBER))
#define MACRO_FUNC_PTR_TYPE_CDECL(RET, ARG_NUMBER) MACRO_FUNC_PTR_CDECL(RET, M_SPACE, ARG_NUMBER)
#define MACRO_FUNC_PTR_TYPE_STDCALL(RET, ARG_NUMBER) MACRO_FUNC_PTR_STDCALL(RET, M_SPACE, ARG_NUMBER)
#define MACRO_FUNC_PTR_TYPE_MEMBER(RET, CLASS, ARG_NUMBER) MACRO_FUNC_PTR_MEMBER(RET, CLASS, M_SPACE, ARG_NUMBER)
#define MACRO_FUNC_PTR_TYPE_THISCALL(RET, CLASS, ARG_NUMBER) MACRO_FUNC_PTR_THISCALL(RET, CLASS, M_SPACE, ARG_NUMBER)

#define MACRO_FUNC_TEMPLATE_HEADER(PRE, RET, ARG_NUMBER, POST) template<PRE typename RET MACRO_TYPENAME_ARG_LIST_WITH_COMMA_PREFIX(ARG_NUMBER) POST>
#define MACRO_CLASS_FUNC_TEMPLATE_HEADER(PRE, RET, CLASS, ARG_NUMBER, POST) template<PRE typename RET, typename CLASS MACRO_TYPENAME_ARG_LIST_WITH_COMMA_PREFIX(ARG_NUMBER) POST>

// we are loosing one level due to the way the recursion iteration works
#define MACRO_SUPPORTED_PARAMETER_NUMBER 15
#define MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE 16


// no support for virtual function ptrs
struct RetroFunctionResolver
{
private:

  enum CallConvention
  {
    CC_CDECL,
    CC_STDCALL,
    CC_MEMBER,
    CC_THISCALL
  };

  template <typename FuncType> struct FuncTraits;

  // using void as special case which falls back to void... not nice, but it allows to continue the logic
  #define MACRO_FUNC_TRAITS_TRANSFROM_SUBSTUCT(SAME_CONV, SAME_CONV_VOID, N) \
    template<typename NewClass> struct Transform { SAME_CONV typedef MACRO_FUNC_PTR_CDECL(Ret, AsCdecl, N); typedef MACRO_FUNC_PTR_STDCALL(Ret, AsStdcall, N); typedef MACRO_FUNC_PTR_MEMBER(Ret, NewClass, AsMember, N); typedef MACRO_FUNC_PTR_THISCALL(Ret, NewClass, AsThiscall, N); }; \
    template<> struct Transform<void> { SAME_CONV_VOID typedef MACRO_FUNC_PTR_CDECL(Ret, AsCdecl, N); typedef MACRO_FUNC_PTR_STDCALL(Ret, AsStdcall, N); typedef void AsMember; typedef void AsThiscall; };
  #define MACRO_FUNC_TRAITS(N) \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_CDECL(Ret, N)> { typedef MACRO_FUNC_PTR_CDECL(Ret, FuncType, N); typedef Ret ReturnType; typedef void ClassType; static const CallConvention callConvention = CC_CDECL; static const int argCount = N; MACRO_FUNC_TRAITS_TRANSFROM_SUBSTUCT(typedef FuncType AsSame;, typedef FuncType AsSame;, N) }; \
    MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)> { typedef MACRO_FUNC_PTR_STDCALL(Ret, FuncType, N); typedef Ret ReturnType; typedef void ClassType; static const CallConvention callConvention = CC_STDCALL; static const int argCount = N; MACRO_FUNC_TRAITS_TRANSFROM_SUBSTUCT(typedef FuncType AsSame;, typedef FuncType AsSame;, N) }; \
    MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N)> { typedef MACRO_FUNC_PTR_MEMBER(Ret, Class, FuncType, N); typedef Ret ReturnType; typedef Class ClassType; static const CallConvention callConvention = CC_MEMBER; static const int argCount = N; MACRO_FUNC_TRAITS_TRANSFROM_SUBSTUCT(typedef MACRO_FUNC_PTR_MEMBER(Ret, NewClass, AsSame, N);, typedef void AsSame;, N) }; \
    MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct FuncTraits<MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N)> { typedef MACRO_FUNC_PTR_THISCALL(Ret, Class, FuncType, N); typedef Ret ReturnType; typedef Class ClassType; static const CallConvention callConvention = CC_THISCALL; static const int argCount = N; MACRO_FUNC_TRAITS_TRANSFROM_SUBSTUCT(typedef MACRO_FUNC_PTR_THISCALL(Ret, NewClass, AsSame, N);, typedef void AsSame;, N) };
  MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_FUNC_TRAITS, M_SPACE)
  #undef MACRO_FUNC_TRAITS
  #undef MACRO_FUNC_TRAITS_TRANSFROM_SUBSTUCT

  // utility templates
  // only integrals and enums are allowed as template arguments if provided as static const values, which means we need to carry the values as types

  template<bool condition, typename IF, IF ifValue, typename ELSE, ELSE elseValue> struct Ternary;
  template<bool condition, typename Type, Type ifValue, Type elseValue> struct Ternary<condition, Type, ifValue, Type, elseValue>;
  template<typename IF, IF ifValue, typename ELSE, ELSE elseValue> struct Ternary<true, IF, ifValue, ELSE, elseValue> { static const IF value; };
  template<typename IF, IF ifValue, typename ELSE, ELSE elseValue> struct Ternary<false, IF, ifValue, ELSE, elseValue> { static const ELSE value; };

  template<bool condition, typename IF, typename ELSE> struct TypeTernary;
  template<typename IF, typename ELSE> struct TypeTernary<true, IF, ELSE> { typedef IF Type; };
  template<typename IF, typename ELSE> struct TypeTernary<false, IF, ELSE> { typedef ELSE Type; };

  template<typename T, T tValue> struct ValueType { static const T value; };

  template<typename IN, IN inValue, typename OUT> struct CStyleCaster { static const OUT value; }; // potentially not runtime safe
  template<typename IN, IN inValue, typename OUT> struct StaticCaster { static const OUT value; };
  template<typename IN, IN inValue, typename OUT> struct ReinterpretCaster { static const  OUT value; }; // not runtime safe

  template<typename T, T a, T b> struct ValueEquals { static const bool value = a == b; };
  template<bool a, bool b> struct LogicalAnd { static const bool value = a && b; };


  template<int address> struct AddressUsageKeeper { static bool initialized; };

  template<int options> 
  struct OptionFlags
  {
    enum
    {
      USE_WRAPPER = !!(options & Option::USE_WRAPPER),
      USE_OWN_IMPLEMENTATION_CALL_LOGGING = !!(options & Option::USE_OWN_IMPLEMENTATION_CALL_LOGGING)
    };
  };

public:

  struct Option
  {
    enum
    {
      NONE = 0,
      USE_WRAPPER = 1,
      USE_OWN_IMPLEMENTATION_CALL_LOGGING = 2,
    };
  };

  template<typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress, int options = Option::NONE>
  struct Resolver
  {
  private:
    // TODO: if the old MSVC still works the same, one can get name information by using typeid(MyTemplate<...>).name() or __FUNCSIG__
    //   and then extract the names. This could be helpful for debugging
    typedef Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options> Self;

    typedef OptionFlags<options> Flags;

    struct Initializer { Initializer(); };
    static const Initializer initializer;

    template<typename FuncPtrType, bool implemented, bool wrapper>
    struct FunctionProvider;
    // Call helper "typename _" is needed for explicit instantiation, otherwise MSVC will complain
    // TODO: 9 Variant: 3 Implemented, 3 Not Implemented, 3-6 Wrapper (6 if wrapper for not implemented should be used, but this could also be handled by the wrapper itself
    // it might be possible to optimize (use the same funcs for different function variants, but be verbose for now
    // TODO create call for wrappers
    // TODO create wrapper for hooked calls, so that they are properly inlined
    #define MACRO_FUNCTION_PROVIDER(N) \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FunctionProvider<MACRO_FUNC_PTR_TYPE_CDECL(Ret, N), true, false> { private: template<typename R, typename = void> struct CallHelper { inline static R call(MACRO_ARG_PARAMETER_LIST(N)) { return funcAddress(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { inline static void call(MACRO_ARG_PARAMETER_LIST(N)) { funcAddress(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FunctionProvider<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N), true, false> { private: template<typename R, typename = void> struct CallHelper { inline static R call(MACRO_ARG_PARAMETER_LIST(N)) { return funcAddress(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { inline static void call(MACRO_ARG_PARAMETER_LIST(N)) { funcAddress(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct FunctionProvider<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N), true, false> { private: template<typename R, typename = void> struct CallHelper { inline static R call(Class* that MACRO_ARG_PARAMETER_LIST_WITH_COMMA_PREFIX(N)) { return (that->*funcAddress)(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { inline static void call(Class* that MACRO_ARG_PARAMETER_LIST_WITH_COMMA_PREFIX(N)) { (that->*funcAddress)(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FunctionProvider<MACRO_FUNC_PTR_TYPE_CDECL(Ret, N), false, false> { private: template<typename R, typename = void> struct CallHelper { inline static R call(MACRO_ARG_PARAMETER_LIST(N)) { return GameCallerFunction::call(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { inline static void call(MACRO_ARG_PARAMETER_LIST(N)) { GameCallerFunction::call(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct FunctionProvider<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N), false, false> { private: template<typename R, typename = void> struct CallHelper { inline static R call(MACRO_ARG_PARAMETER_LIST(N)) { return GameCallerFunction::call(Ret, N)) gameAddress)(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { inline static void call(MACRO_ARG_PARAMETER_LIST(N)) { GameCallerFunction::call(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct FunctionProvider<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N), false, false> { private: template<typename R, typename = void> struct CallHelper { inline static R call(Class* that MACRO_ARG_PARAMETER_LIST_WITH_COMMA_PREFIX(N)) { return (((GameCallerFunction*) that)->GameCallerFunction::call)(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { inline static void call(Class* that MACRO_ARG_PARAMETER_LIST_WITH_COMMA_PREFIX(N)) { (((GameCallerFunction*) that)->GameCallerFunction::call)(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; };
      // TODO: add wrapper macros
    MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_FUNCTION_PROVIDER, M_SPACE)
    #undef MACRO_FUNCTION_PROVIDER

    template<typename FuncPtrType>
    struct GameCaller;

    #define MACRO_GAME_CALLER(N) \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct GameCaller<MACRO_FUNC_PTR_TYPE_CDECL(Ret, N)> { private: template<typename R, typename = void> struct CallHelper { __declspec(noinline) static R __cdecl call(MACRO_ARG_PARAMETER_LIST(N)) { return ((MACRO_FUNC_PTR_TYPE_CDECL(Ret, N)) gameAddress)(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { __declspec(noinline) static void __cdecl call(MACRO_ARG_PARAMETER_LIST(N)) { ((MACRO_FUNC_PTR_TYPE_CDECL(Ret, N)) gameAddress)(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct GameCaller<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)> { private: template<typename R, typename = void> struct CallHelper { __declspec(noinline) static R __stdcall call(MACRO_ARG_PARAMETER_LIST(N)) { return ((MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)) gameAddress)(MACRO_PARAMETER_LIST(N)); } }; template<typename _> struct CallHelper<void, _> { __declspec(noinline) static void __stdcall call(MACRO_ARG_PARAMETER_LIST(N)) { ((MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)) gameAddress)(MACRO_PARAMETER_LIST(N)); } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct GameCaller<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N)> { private: template<typename R, typename = void> struct CallHelper { __declspec(noinline) R call(MACRO_ARG_PARAMETER_LIST(N)) { return ((MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N)) gameAddress)((Class*)this MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N)); } }; template<typename _> struct CallHelper<void, _> { __declspec(noinline) void call(MACRO_ARG_PARAMETER_LIST(N)) { ((MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N)) gameAddress)((Class*)this MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N)); } }; public: typedef CallHelper<Ret> Function; };
    MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_GAME_CALLER, M_SPACE)
    #undef MACRO_GAME_CALLER

    // TODO: address of the hooked caller could be obtained through this... if wanted
    typedef typename GameCaller<FuncPtrType>::Function GameCallerFunction;


    template<typename FuncPtrType>
    struct Wrapper;

    // TODO: might need variants for class/no-class/ return type, no return type...

    #define MACRO_WRAPPER_BODY_PRECALL(N) \
      std::cout << "Wrapper called for " << typeid(Self).name() << "\n";

    #define MACRO_WRAPPER_BODY_POSTCALL(N)

    #define MACRO_CALL_WRAPPER(N) \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_CDECL(Ret, N)> { private: template<typename R, typename = void> struct CallHelper { static R __cdecl call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = CorePtrResolver::value(MACRO_PARAMETER_LIST(N)); MACRO_WRAPPER_BODY_POSTCALL(N) return ret; } }; template<typename _> struct CallHelper<void, _> { static void __cdecl call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) CorePtrResolver::value(MACRO_PARAMETER_LIST(N)); MACRO_WRAPPER_BODY_POSTCALL(N) } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_FUNC_TEMPLATE_HEADER(, Ret, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_STDCALL(Ret, N)> { private: template<typename R, typename = void> struct CallHelper { static R __stdcall call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = CorePtrResolver::value(MACRO_PARAMETER_LIST(N)); MACRO_WRAPPER_BODY_POSTCALL(N) return ret; } }; template<typename _> struct CallHelper<void, _> { static void __stdcall call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) CorePtrResolver::value(MACRO_PARAMETER_LIST(N)); MACRO_WRAPPER_BODY_POSTCALL(N) } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_MEMBER(Ret, Class, N)> { private: template<typename R, typename = void> struct CallHelper { R call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = (((Class*)(this))->*CorePtrResolver::value)(MACRO_PARAMETER_LIST(N)); MACRO_WRAPPER_BODY_POSTCALL(N) return ret; } }; template<typename _> struct CallHelper<void, _> { void call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) (((Class*)(this))->*CorePtrResolver::value)(MACRO_PARAMETER_LIST(N)); MACRO_WRAPPER_BODY_POSTCALL(N) } }; public: typedef CallHelper<Ret> Function; }; \
      MACRO_CLASS_FUNC_TEMPLATE_HEADER(, Ret, Class, N, ) struct Wrapper<MACRO_FUNC_PTR_TYPE_THISCALL(Ret, Class, N)> { private: template<typename R, typename = void> struct CallHelper { R call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) Ret ret = CorePtrResolver::value(((Class*)(this)) MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N)); MACRO_WRAPPER_BODY_POSTCALL(N) return ret; } }; template<typename _> struct CallHelper<void, _> { void call(MACRO_ARG_PARAMETER_LIST(N)) { MACRO_WRAPPER_BODY_PRECALL(N) CorePtrResolver::value(((Class*)(this)) MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX(N)); MACRO_WRAPPER_BODY_POSTCALL(N) } }; public: typedef CallHelper<Ret> Function; };
    MACRO_INDEX_ITERATE_DEPTH_1(MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE, MACRO_CALL_WRAPPER, M_SPACE)
    #undef MACRO_CALL_WRAPPER

    #undef MACRO_WRAPPER_BODY_POSTCALL
    #undef MACRO_WRAPPER_BODY_PRECALL

     
    // there can only be one finalizing logic function (cast or the ptr) involving the ptr if the ptr should be inlined, since only integral arithmetic is compiletime supported in C++03
    typedef FuncTraits<FuncPtrType> SourceFuncTraits;
      
    typedef typename TypeTernary<
      LogicalAnd<ValueEquals<CallConvention, CC_MEMBER, SourceFuncTraits::callConvention>::value, !implemented>::value,
      typename SourceFuncTraits::template Transform<SourceFuncTraits::ClassType>::AsThiscall,
      FuncPtrType
    >::Type TargetFunctionType;
    typedef ValueType<FuncPtrType, funcAddress> FuncPtrResolver;
    typedef ReinterpretCaster<int, gameAddress, TargetFunctionType> GameAddressResolver; // indirect call is as good as it gets, since the relative address is not known at compile time (apparently there are linker tricks, but that would need a lot of external steps, making this approach void)
    typedef typename TypeTernary<implemented, FuncPtrResolver, GameAddressResolver>::Type CorePtrResolver;

    typedef typename Wrapper<TargetFunctionType>::Function WrapperFunction;
    typedef typename SourceFuncTraits::template Transform<WrapperFunction>::AsSame WrapperFuncPtrType;
    typedef ValueType<WrapperFuncPtrType, &WrapperFunction::call> WrapperFuncPtr; // TODO: apparently, this is not valid in C++03, so it seems to be time to switch
    typedef typename TypeTernary<Flags::USE_WRAPPER, WrapperFuncPtr, CorePtrResolver>::Type MaybeWrapperResolver;
    typedef typename TypeTernary<Flags::USE_WRAPPER, WrapperFuncPtrType, TargetFunctionType>::Type PtrResolverValueType;
  public:
    typedef typename FunctionProvider<FuncPtrType, implemented, Flags::USE_WRAPPER>::Function Function;
  };
};

template<typename IF, IF ifValue, typename ELSE, ELSE elseValue> const IF RetroFunctionResolver::Ternary<true, IF, ifValue, ELSE, elseValue>::value = ifValue;
template<typename IF, IF ifValue, typename ELSE, ELSE elseValue> const ELSE RetroFunctionResolver::Ternary<false, IF, ifValue, ELSE, elseValue>::value = elseValue;

template<typename T, T tValue> const T RetroFunctionResolver::ValueType<T, tValue>::value = tValue;

template<typename IN, IN inValue, typename OUT> const OUT RetroFunctionResolver::CStyleCaster<IN, inValue, OUT>::value = (OUT) inValue;
template<typename IN, IN inValue, typename OUT> const OUT RetroFunctionResolver::StaticCaster<IN, inValue, OUT>::value = static_cast<OUT>(inValue);
template<typename IN, IN inValue, typename OUT> const OUT RetroFunctionResolver::ReinterpretCaster<IN, inValue, OUT>::value = reinterpret_cast<OUT>(inValue);

template<int address>
bool RetroFunctionResolver::AddressUsageKeeper<address>::initialized = false;

template<typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress, int options>
typename RetroFunctionResolver::Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options>::Initializer const RetroFunctionResolver::Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options>::initializer;

template<typename FuncPtrType, bool implemented, int gameAddress, FuncPtrType funcAddress, int options>
RetroFunctionResolver::Resolver<FuncPtrType, implemented, gameAddress, funcAddress, options>::Initializer::Initializer()
{
  if (AddressUsageKeeper<gameAddress>::initialized)
  {
    std::cout << "do something if already initialized\n";
    return;
  }
  AddressUsageKeeper<gameAddress>::initialized = true;

  if (implemented)
  {
    // these positions could be used to hook into the game using another parameter to provide the address
    // TODO: the hook would need to take the resolved ptr as reference, not the "funcAddress", otherwise it would not call the wrapping logic if the game calls
    const PtrResolverValueType func = MaybeWrapperResolver::value;
    std::cout << "implemented with type " << typeid(Self).name() << ", now hook to: " << *((void**) (&func)) << "\n";

    // test
    //typedef FuncTraits<FuncPtrType> SourceFuncTraits;

    //typedef typename TypeTernary<
    //  LogicalAnd<ValueEquals<CallConvention, CC_MEMBER, SourceFuncTraits::callConvention>::value, !implemented>::value,
    //  typename SourceFuncTraits::template Transform<SourceFuncTraits::ClassType>::AsThiscall,
    //  FuncPtrType
    //>::Type OtherTargetFunctionType;

    //std::cout << typeid(FuncPtrType).name() << " " << typeid(OtherTargetFunctionType).name() << "\n";
    //std::cout << typeid(TargetFunctionType).name() << "\n";
  }
  else
  {
    std::cout << "not implemented\n";
  }
}

#undef MACRO_NUMBER_OF_FUNCTIONS_TO_GENERATE
#undef MACRO_SUPPORTED_PARAMETER_NUMBER

#undef MACRO_CLASS_FUNC_TEMPLATE_HEADER
#undef MACRO_FUNC_TEMPLATE_HEADER

#undef MACRO_FUNC_PTR_TYPE_THISCALL
#undef MACRO_FUNC_PTR_TYPE_MEMBER
#undef MACRO_FUNC_PTR_TYPE_STDCALL
#undef MACRO_FUNC_PTR_TYPE_CDECL
#undef MACRO_FUNC_PTR_THISCALL
#undef MACRO_FUNC_PTR_MEMBER
#undef MACRO_FUNC_PTR_STDCALL
#undef MACRO_FUNC_PTR_CDECL

#undef MACRO_ARG_PARAMETER_LIST_WITH_COMMA_PREFIX
#undef MACRO_TYPENAME_ARG_LIST_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_LIST_WITH_COMMA_PREFIX
#undef MACRO_ARG_LIST_WITH_COMMA_PREFIX
#undef MACRO_ARG_PARAMETER_LIST
#undef MACRO_TYPENAME_ARG_LIST
#undef MACRO_PARAMETER_LIST
#undef MACRO_ARG_LIST

#undef MACRO_ARG_PARAMETER_WITH_COMMA_PREFIX
#undef MACRO_TYPENAME_ARG_WITH_COMMA_PREFIX
#undef MACRO_PARAMETER_WITH_COMMA_PREFIX
#undef MACRO_ARG_WITH_COMMA_PREFIX
#undef MACRO_ARG_PARAMETER
#undef MACRO_TYPENAME_ARG
#undef MACRO_PARAMETER
#undef MACRO_ARG

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
#define MACRO_FUNCTION_RESOLVER(FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS) MACRO_FUNCTION_RESOLVER_EXT(FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, RetroFunctionResolver::Option::NONE)
#define MACRO_FUNCTION_RESOLVER_EXT(FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, OPTIONS) template struct RetroFunctionResolver::Resolver<FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, OPTIONS>; typedef RetroFunctionResolver::Resolver<FUNCTION_TYPE, IMPLEMENTED, GAME_ADDRESS, FUNCTION_ADDRESS, OPTIONS>::Function

#endif // FUNCTION_RESOLVER
