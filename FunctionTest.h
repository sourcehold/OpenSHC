#pragma once

#include "RetroTemplate.h"
#include "ViewportRenderState.h"

template<typename T, T value> struct Test
{
  static bool init;
};
template<typename R, typename Class, typename Arg0, typename Arg1, R(Class::* value)(Arg0, Arg1)> struct Test<R(Class::*)(Arg0, Arg1), value>
{
  static bool init;
  template<const bool* ptr>
  inline static R call(Class* obj, Arg0 arg0, Arg1 arg1) { return (obj->*(ptr ? value : 0))(arg0, arg1); }
};

namespace ViewportRenderState_Func
{
  typedef RetroFunctionResolver::Resolver<BOOL(ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid>::Function xyAreValid;
  typedef Test<BOOL(ViewportRenderState::*)(uint, uint), &ViewportRenderState::xyAreValid> xyAreValidDirectTest;
}


template<typename T, T value> bool Test<T, value>::init = init<T, value>();

template<typename R, typename Class, typename Arg0, typename Arg1, R(Class::* value)(Arg0, Arg1)>
bool Test<R(Class::*)(Arg0, Arg1), value>::init = Initializer<R(Class::*)(Arg0, Arg1), value>::init();

template<typename T, T value>
struct Initializer
{
  static const bool init()
  {
    std::cout << "do something if already initialized\n";
    return true;
  }
};
