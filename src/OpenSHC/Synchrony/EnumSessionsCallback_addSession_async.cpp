#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/GlobalAllocFlag.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::GlobalAllocFlag;

// FUNCTION: STRONGHOLDCRUSADER 0x0047DF40
BOOL __stdcall Synchrony::EnumSessionsCallback_addSession_async(
    LPCDPSESSIONDESC2 lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext)
{
    WCHAR* pWVar1;
    ushort uVar2;
    WCHAR* pWVar3;
    WCHAR* _pSessionName;
    void* _alloc;
    GUID* _lockedMemory;
    WCHAR* _pReceivedSessionName;
    WCHAR* _pSessionName2;
    WCHAR _char;
    GUID* _pGUID;
    if (!(dwFlags & 1) && DAT_GameSynchronyState::instance.DPLAY_SessionsCount < 50) {
        pWVar3 = lpThisSD->lpszSessionName;
        pWVar1 = pWVar3 + 1;
        do {
            _char = *pWVar3;
            pWVar3 = pWVar3 + 1;
        } while (_char != L'\0');
        _pSessionName = (WCHAR*)(MACRO_CALL(OS_Func::_malloc)(((int)pWVar3 - (int)pWVar1 >> 1) * 2 + 4));
        DAT_GameSynchronyState::instance.DPLAY_SessionNames[DAT_GameSynchronyState::instance.DPLAY_SessionsCount]
            = _pSessionName;
        _pReceivedSessionName = lpThisSD->lpszSessionName;
        _pSessionName2
            = DAT_GameSynchronyState::instance.DPLAY_SessionNames[DAT_GameSynchronyState::instance.DPLAY_SessionsCount];
        do {
            _char = *_pReceivedSessionName;
            *_pSessionName2 = _char;
            _pReceivedSessionName = _pReceivedSessionName + 1;
            _pSessionName2 = _pSessionName2 + 1;
        } while (_char != L'\0');
        _alloc = GlobalAlloc(WindowsHelper::Enums::GAF_GHND, 16);
        _lockedMemory = (GUID*)(GlobalLock(_alloc));
        DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[DAT_GameSynchronyState::instance.DPLAY_SessionsCount]
            = _lockedMemory;
        _pGUID
            = DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[DAT_GameSynchronyState::instance.DPLAY_SessionsCount];
        if (_pGUID != (GUID*)0x0) {
            _pGUID->Data1 = (lpThisSD->guidInstance).Data1;
            uVar2 = (lpThisSD->guidInstance).Data3;
            _pGUID->Data2 = (lpThisSD->guidInstance).Data2;
            _pGUID->Data3 = uVar2;
            *(undefined4*)_pGUID->Data4 = *(undefined4*)(lpThisSD->guidInstance).Data4;
            *(undefined4*)(_pGUID->Data4 + 4) = *(undefined4*)((lpThisSD->guidInstance).Data4 + 4);
            DAT_GameSynchronyState::instance.DPLAY_SessionsCount
                = DAT_GameSynchronyState::instance.DPLAY_SessionsCount + 1;
        }
        return true;
    }
    return false;
}

}
