# openshc
An open source re-implementation of Stronghold Crusader

## API proof of concept
API calls should largely be self documenting.
The macro `CAST_THIS_CALL` doesn't document argument names. So maybe typedef approach is better and more clear.

```cpp
#include <cstdlib> 

#define __cdecl __attribute__((cdecl))
#define __stdcall __attribute__((stdcall))
#define __thiscall __attribute__((thiscall))

#define TYPEDEF_THIS_CALL(name, ...)(__thiscall name)(__VA_ARGS__)
#define SINGLETON_THIS_CALL(ecx, name, ...)
#define CALL_ARGS(...) (__VA_ARGS__)

#define ADDR_CALL_A 0x401000
#define DO_GAME_X ((FuncDef*) ADDR_CALL_A)

int (__stdcall *f)(int, int, int);

class A {

public:

    int v = 1;

    int __thiscall whatever(int a, int b) {
        this->v += (a * b);
        return this->v;
    }

};

typedef const int (__thiscall FuncDef)(A*, int, int);
typedef const int (__thiscall FuncDefVoid)(void*, int, int);
typedef const int TYPEDEF_THIS_CALL(FuncDef2, A*, int, int);

#define CAST_CDECL_CALL(addr, returnType, ...) ((const returnType (__cdecl *)(__VA_ARGS__)) addr)
#define CDECL_CALL(func, ...) func(__VA_ARGS__)

#define CALL_FUNC_CdeclExample(...) CDECL_CALL(CAST_CDECL_CALL(0x401000, int, int, int), __VA_ARGS__)

#define CAST_STD_CALL(addr, returnType, ...) ((const returnType (__stdcall *)(__VA_ARGS__)) addr)
#define STD_CALL(func, ...) func(__VA_ARGS__)

#define CALL_FUNC_StdExample(...) STD_CALL(CAST_STD_CALL(0x401000, int, int, int), __VA_ARGS__)

#define CAST_THIS_CALL(addr, returnType, ...) ((const returnType (__thiscall *)(void*, __VA_ARGS__)) addr)
#define THIS_CALL(func, thisValue, ...) func(thisValue, __VA_ARGS__)

#define CALL_FUNC_Whatever(...) THIS_CALL(CAST_THIS_CALL(0x401000, int, int, int), a, __VA_ARGS__)

const auto whatever3 = CAST_THIS_CALL(0x401000, int, int);
const FuncDef* whatever2 = (FuncDef*) 0x401000;

A *a = new A();

int main() {
    int r0 = a->whatever(100, 9);

    void * p = (void *) 0x4001000;
    A* b = ((A*) p);
    int r = b->whatever(1000, r0);

    int r2 = whatever2(a, r, 250);

    r2 = DO_GAME_X(a, r, r2);

    int r3 = ((FuncDef*) 0x401000)(a, r, r2);

    FuncDef* a4 = (const int (__thiscall *)(A*, int, int)) 0x401000;
    FuncDefVoid* a5 = CAST_THIS_CALL(0x401000, int, int, int);

    int r4 = CAST_THIS_CALL(0x401000, int, int, int)(a, r2, r3);
    int r5 = CALL_FUNC_Whatever(r3, r4);
    int r6 = CALL_FUNC_StdExample(r4, r5);
    int r7 = CALL_FUNC_CdeclExample(r6, r5);
    

    return a->whatever(r+r3, r2+r7);
}
```
