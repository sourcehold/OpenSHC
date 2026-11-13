#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/IID_IDirectDraw7.hpp"

namespace OpenSHC {

typedef HRESULT(WINAPI* DirectDrawCreateExFunc)(GUID* guid, void** directDraw, REFIID iid, IUnknown* unkOuter);

// FUNCTION: STRONGHOLDCRUSADER 0x0046F4F0
Global::DirectDrawStatus Global::DetectDXVersionByLoadingDDRAW()
{
    // "DDRAW.DLL"
    HMODULE const ddrawModule = LoadLibraryA(s_DDRAW_DLL_005a61ec);
    if (ddrawModule == NULL) {
        return Rendering::Enums::DD7_NOT_LOADED;
    }
    IUnknown* directDraw;
    // "DirectDrawCreate"
    if (GetProcAddress(ddrawModule, s_DirectDrawCreate_005a61d8) == NULL) {
        FreeLibrary(ddrawModule);
        return Rendering::Enums::DD7_NOT_LOADED;
    }
    // "DirectDrawCreateEx"
    DirectDrawCreateExFunc const directDrawCreateEx
        = (DirectDrawCreateExFunc)GetProcAddress(ddrawModule, s_DirectDrawCreateEx_005a61c4);
    if (directDrawCreateEx == NULL) {
        FreeLibrary(ddrawModule);
        return Rendering::Enums::DD7_NOT_LOADED;
    }
    if (directDrawCreateEx(NULL, (void**)&directDraw, IID_IDirectDraw7::instance, NULL) < 0) {
        FreeLibrary(ddrawModule);
        return Rendering::Enums::DD7_NOT_LOADED;
    }
    directDraw->Release();
    FreeLibrary(ddrawModule);
    return Rendering::Enums::DD7_LOADED;
}

}
