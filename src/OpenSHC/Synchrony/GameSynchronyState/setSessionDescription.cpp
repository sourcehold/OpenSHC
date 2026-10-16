#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "OpenSHC/Globals/GUID_UNKNOWN.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047DE00
    void GameSynchronyState::setSessionDescription()
    {
        DPSESSIONDESC2 local_54;
        uint uVar1 = MSVC_SecurityCookie::instance ^ (uint)&local_54;
        if (this->isHost) {
            MACRO_CALL(OS_Func::_memset)(&local_54, 0, 0x50);
            local_54.dwSize = 0x50;
            local_54.dwFlags = DPSESSION_OPTIMIZELATENCY | DPSESSION_DIRECTPLAYPROTOCOL | DPSESSION_KEEPALIVE
                | DPSESSION_JOINDISABLED | DPSESSION_MIGRATEHOST | DPSESSION_NEWPLAYERSDISABLED;
            local_54.guidApplication = GUID_UNKNOWN::instance;
            local_54.dwMaxPlayers = 8;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDPlaySessionNameValue, this)();
            local_54.lpszSessionName = this->DPLAYX_SessionName;
            this->DPLAYX_4A->SetSessionDesc(&local_54, 0);
        };
    }

}
}
