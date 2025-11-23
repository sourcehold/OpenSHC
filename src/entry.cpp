
#include "MainResolver.h"

#include "CompileMacros.h"

#include "lua.h"

#ifdef OPEN_SHC_DLL

int luaopen_OpenSHC(lua_State* L) { return 0; }

#endif

#ifdef OPEN_SHC_EXE

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    return MACRO_CALL(Main_Func::WinMain)(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

#endif
