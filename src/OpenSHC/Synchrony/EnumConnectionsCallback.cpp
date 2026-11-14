// disable deprecation warnings for wcscpy
#pragma warning(disable : 4996)

#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_IPX.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D5B0
    BOOLEnum __stdcall EnumConnectionsCallback(LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize,
        LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
    {
        // 10 is the length of guids and providerNames.
        if (DAT_GameSynchronyState::instance.scrollBarItemCount >= 10) {
            return FALSE;
        }
        // TCP/IP, IPX and modem keep the first three slots; any other provider is added after them.
        int slot = DAT_GameSynchronyState::instance.scrollBarItemCount;
        if (MACRO_CALL(OS_Func::isEqualGUID)((GUID*)lpguidSP, GUID_DPSPGUID_TCPIP::ptr)) {
            slot = 0;
        } else if (MACRO_CALL(OS_Func::isEqualGUID)((GUID*)lpguidSP, GUID_DPSPGUID_IPX::ptr)) {
            slot = 1;
        } else if (MACRO_CALL(OS_Func::isEqualGUID)((GUID*)lpguidSP, GUID_DPSPGUID_MODEM::ptr)) {
            slot = 2;
        } else {
            ++DAT_GameSynchronyState::instance.scrollBarItemCount;
        }
        WCHAR* const name = (WCHAR*)MACRO_CALL(OS_Func::_malloc)((wcslen(lpName->lpszShortName) + 2) * sizeof(WCHAR));
        DAT_GameSynchronyState::instance.providerNames[slot] = name;
        wcscpy(name, lpName->lpszShortName);
        DAT_GameSynchronyState::instance.guids[slot] = (GUID*)GlobalLock(GlobalAlloc(GHND, sizeof(GUID)));
        if (DAT_GameSynchronyState::instance.guids[slot] != NULL) {
            *DAT_GameSynchronyState::instance.guids[slot] = *lpguidSP;
        }
        return TRUE;
    }

}
}
