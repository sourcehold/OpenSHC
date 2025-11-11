#pragma once

#define MemberFunctionPointer_DefineSingleton(baseClass, address)                                                      \
    baseClass* const Singleton = (baseClass* const)address;

#define MemberFunctionPointer_DefineProcType(className, funcName, returnType, ...)                                     \
    typedef returnType (*const _##className##_##funcName##_PROC)(__VA_ARGS__)

#define MemberFunctionPointer_DefineMethodType(className, funcName, returnType, ...)                                   \
    typedef returnType (className::* const _##className##_##funcName##_METHOD)(__VA_ARGS__)

#define MemberFunctionPointer_DefineMethodCast(className, funcName)                                                    \
    _##className##_##funcName##_METHOD _##className##_##funcName##_Method                                              \
        = (_##className##_##funcName##_METHOD) & className::funcName

#define MemberFunctionPointer_DefineMethodPointer(className, funcName, address)                                        \
    _##className##_##funcName##_PROC _##className##_##funcName##_Pointer = (_##className##_##funcName##_PROC)address

#define MemberFunctionPointer_DefineMethodPointer_oneliner(className, funcName, address, returnType, ...)              \
    typedef returnType (*const _##className##_##funcName##_PROC)(__VA_ARGS__);                                         \
    typedef returnType (className::* const _##className##_##funcName##_METHOD)(__VA_ARGS__);                           \
    _##className##_##funcName##_METHOD _##className##_##funcName##_Method                                              \
        = (_##className##_##funcName##_METHOD) & className::funcName;                                                  \
    _##className##_##funcName##_PROC _##className##_##funcName##_Pointer = (_##className##_##funcName##_PROC)address;

#define MemberFunctionPointer_DefineThiscallType(className, funcName, returnType, ...)                                 \
    typedef returnType(__thiscall* const _##className##_##funcName##_THISCALL)(className* const _this, __VA_ARGS__)

#define MemberFunctionPointer_DefineThiscall(className, funcName, returnType, ...)                                     \
    returnType(__thiscall* const funcName)(className* const _this, __VA_ARGS__)                                        \
        = (_##className##_##funcName##_THISCALL&)_##className##_##funcName##_Method

#define MemberFunctionPointer_DefineThiscall_oneliner(className, funcName, returnType, ...)                            \
    typedef returnType (*const _##className##_##funcName##_PROC)(__VA_ARGS__);                                         \
    typedef returnType (className::* const _##className##_##funcName##_METHOD)(__VA_ARGS__);                           \
    _##className##_##funcName##_METHOD _##className##_##funcName##_Method                                              \
        = (_##className##_##funcName##_METHOD) & className::funcName;                                                  \
    typedef returnType(__thiscall* const _##className##_##funcName##_THISCALL)(className* const _this, __VA_ARGS__);   \
    returnType(__thiscall* const funcName)(className* const _this, __VA_ARGS__)                                        \
        = (_##className##_##funcName##_THISCALL&)_##className##_##funcName##_Method;

#define MemberFunctionPointer_InvokeMethod(className, funcName, ...)                                                   \
    ((className* const)this->*(_##className##_##funcName##_METHOD&)_##className##_##funcName##_Pointer)(__VA_ARGS__)