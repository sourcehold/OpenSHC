#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/TIME_EnumerateSessionsMoment.hpp"

namespace OpenSHC {
namespace Synchrony {

    using DirectPlay::EnumSessionsFlagsEnum;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487390
    void GameSynchronyState::restartDPlaySessionEnumeration(BOOLEnum respectTimeout)
    {
        DWORD _now;
        GUID _pGUID;
        DPSESSIONDESC2 _dpSessionDesc2;
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&_pGUID;
        _now = timeGetTime();
        _pGUID.Data2 = 0;
        _pGUID.Data3 = 0;
        _pGUID.Data1 = 0;
        _pGUID.Data4[0] = '\0';
        _pGUID.Data4[1] = '\0';
        _pGUID.Data4[2] = '\0';
        _pGUID.Data4[3] = '\0';
        _pGUID.Data4[4] = '\0';
        _pGUID.Data4[5] = '\0';
        _pGUID.Data4[6] = '\0';
        _pGUID.Data4[7] = '\0';
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::fetchSessionGUID, this)(&_pGUID);
        if (this->unkEnumerationRelatedBool == false
            && (respectTimeout != TRUE || (2999 < (int)(_now - TIME_EnumerateSessionsMoment::instance)))) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearSessionsList, this)();
            MACRO_CALL(OS_Func::_memset)(&_dpSessionDesc2, 0, 0x50);
            static const GUID _sessionAppGuid
                = { 0x1d5e2f48, 0xe8c0, 0x49e5, { 0xae, 0xd8, 0xb1, 0x24, 0xda, 0x9e, 0x30, 0x59 } };
            _dpSessionDesc2.guidApplication = _sessionAppGuid;
            this->unkEnumerationRelatedBool = true;
            _dpSessionDesc2.dwSize = 0x50;
            if (this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
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
