// disable deprecation warnings for wcscpy
#pragma warning(disable : 4996)

#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047DF40
    BOOLEnum __stdcall EnumSessionsCallback_addSession_async(
        LPCDPSESSIONDESC2 lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext)
    {
        if (dwFlags & DPESC_TIMEDOUT) {
            return FALSE;
        }
        // 50 is the length of DPLAY_SessionNames and DPLAY_SessionGUIDs.
        if (DAT_GameSynchronyState::instance.DPLAY_SessionsCount >= 50) {
            return FALSE;
        }
        DAT_GameSynchronyState::instance.DPLAY_SessionNames[DAT_GameSynchronyState::instance.DPLAY_SessionsCount]
            = (WCHAR*)MACRO_CALL(OS_Func::_malloc)((wcslen(lpThisSD->lpszSessionName) + 2) * sizeof(WCHAR));
        wcscpy(
            DAT_GameSynchronyState::instance.DPLAY_SessionNames[DAT_GameSynchronyState::instance.DPLAY_SessionsCount],
            lpThisSD->lpszSessionName);
        DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[DAT_GameSynchronyState::instance.DPLAY_SessionsCount]
            = (GUID*)GlobalLock(GlobalAlloc(GHND, sizeof(GUID)));
        if (DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[DAT_GameSynchronyState::instance.DPLAY_SessionsCount]
            != NULL) {
            *DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[DAT_GameSynchronyState::instance.DPLAY_SessionsCount]
                = lpThisSD->guidInstance;
            ++DAT_GameSynchronyState::instance.DPLAY_SessionsCount;
        }
        return TRUE;
    }

}
}
