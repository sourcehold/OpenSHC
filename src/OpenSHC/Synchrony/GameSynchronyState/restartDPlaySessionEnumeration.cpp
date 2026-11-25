#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_APP.hpp"
#include "OpenSHC/Globals/GUID_NULL.hpp"
#include "OpenSHC/Globals/TIME_EnumerateSessionsMoment.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00487390
    void GameSynchronyState::restartDPlaySessionEnumeration(BOOLEnum respectTimeout)
    {
        DWORD const now = timeGetTime();
        GUID selectedSession = GUID_NULL::instance;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::fetchSessionGUID, this)(&selectedSession);
        // With respectTimeout, the sessions are enumerated again at most every 3 seconds. It is compared with TRUE,
        // as in the original: a plain truth test changes the code.
        if (this->unkEnumerationRelatedBool
            || (respectTimeout == TRUE && (int)(now - TIME_EnumerateSessionsMoment::instance) < 3000)) {
            return;
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearSessionsList, this)();
        DPSESSIONDESC2 description;
        MACRO_CALL(OS_Func::_memset)(&description, 0, sizeof(description));
        description.dwSize = sizeof(description);
        description.guidApplication = GUID_APP::instance;
        this->unkEnumerationRelatedBool = true;
        // The original checks the DirectPlay interface of the global instance here.
        if (DAT_GameSynchronyState::instance.DPLAYX_4A != NULL) {
            this->DPLAYX_4A->EnumSessions(&description, 0,
                MACRO_CALL(Synchrony_Func::EnumSessionsCallback_addSession_async), NULL,
                DirectPlay::ESFE_RETURN_STATUS | DirectPlay::ESFE_ASYNC_ENUMERATION | DirectPlay::ESFE_AVAILABLE);
        }
        this->unkEnumerationRelatedBool = false;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::resolveEqualEntries, this)(&selectedSession);
        TIME_EnumerateSessionsMoment::instance = timeGetTime();
    }

}
}
