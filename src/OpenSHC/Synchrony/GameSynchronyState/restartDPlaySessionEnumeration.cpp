#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/TIME_EnumerateSessionsMoment.hpp"

#include "OpenSHC/Globals/GUID_NULL_CONSTANT.hpp"
#include "OpenSHC/Globals/GUID_UNKNOWN.hpp"

namespace OpenSHC {
namespace Synchrony {

    using DirectPlay::EnumSessionsFlagsEnum;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487390
    void GameSynchronyState::restartDPlaySessionEnumeration(BOOLEnum respectTimeout)
    {
        GUID _pGUID;
        DPSESSIONDESC2 _dpSessionDesc2;
        uint local_4 = MSVC_SecurityCookie::instance ^ (uint)&_pGUID;
        DWORD _now = timeGetTime();
        _pGUID = GUID_NULL_CONSTANT::instance;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::fetchSessionGUID, this)(&_pGUID);
        if (this->unkEnumerationRelatedBool == false
            && (respectTimeout != TRUE || (int)(_now - TIME_EnumerateSessionsMoment::instance) >= 3000)) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearSessionsList, this)();
            MACRO_CALL(OS_Func::_memset)(&_dpSessionDesc2, 0, 0x50);
            _dpSessionDesc2.dwSize = 0x50;
            _dpSessionDesc2.guidApplication = GUID_UNKNOWN::instance;
            this->unkEnumerationRelatedBool = true;
            if (DAT_GameSynchronyState::instance.DPLAYX_4A != (IDirectPlay4A*)0x0) {
                /*
                  pointer to a pointer to a function
                 */
                this->DPLAYX_4A->EnumSessions(&_dpSessionDesc2, 0,
                    MACRO_CALL(Synchrony_Func::EnumSessionsCallback_addSession_async), (void*)0x0,
                    DirectPlay::ESFE_RETURN_STATUS | DirectPlay::ESFE_ASYNC_ENUMERATION | DirectPlay::ESFE_AVAILABLE);
            }
            this->unkEnumerationRelatedBool = false;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::resolveEqualEntries, this)((GUID*)&_pGUID);
            TIME_EnumerateSessionsMoment::instance = timeGetTime();
        };
        return;
    }

}
}
