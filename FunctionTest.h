#pragma once

#include "RetroTemplate.h"
#include "ViewportRenderState.h"

template<typename T, T value> struct TestWrapper;

template<typename R, typename Class, typename Arg0, typename Arg1, R(Class::* value)(Arg0, Arg1)>
struct TestWrapper<R(Class::*)(Arg0, Arg1), value>
{
  typedef TestWrapper<R(Class::*)(Arg0, Arg1), value> Self;

  struct Initializer
  {
    Initializer()
    {
      std::cout << "Initializing template for function" << std::endl;
    }
  };

  struct Test
  {
    //inline static R call(Class* obj, Arg0 arg0, Arg1 arg1) { return (obj->*(ptr ? value : 0))(arg0, arg1); }
    inline static R call(Class* obj, Arg0 arg0, Arg1 arg1) { return (obj->*value)(arg0, arg1); }
  };

  static Initializer initializer;

  typedef Test Function;
};

template<typename R, typename Class, typename Arg0, typename Arg1, R(Class::* value)(Arg0, Arg1)>
typename TestWrapper<R(Class::*)(Arg0, Arg1), value>::Initializer TestWrapper<R(Class::*)(Arg0, Arg1), value>::initializer;

namespace ViewportRenderState_Func
{
  MACRO_FUNCTION_RESOLVER(BOOL(ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid) xyAreValid;
  //MACRO_FUNCTION_RESOLVER_EXT(BOOL(ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid, RetroFunctionResolver::Option::USE_WRAPPER) xyAreValid;
}


