#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

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
            local_54.guidApplication.Data1 = 0x1d5e2f48;
            memcpy(local_54.guidApplication.Data4 + 4, "ڞ0Y", 4);
            local_54.dwSize = 0x50;
            local_54.dwFlags = DPSESSION_OPTIMIZELATENCY | DPSESSION_DIRECTPLAYPROTOCOL | DPSESSION_KEEPALIVE
                | DPSESSION_JOINDISABLED | DPSESSION_MIGRATEHOST | DPSESSION_NEWPLAYERSDISABLED;
            local_54.guidApplication.Data2 = 0xe8c0;
            local_54.guidApplication.Data3 = 0x49e5;
            local_54.guidApplication.Data4[0] = 0xae;
            local_54.guidApplication.Data4[1] = 0xd8;
            local_54.guidApplication.Data4[2] = 0xb1;
            local_54.guidApplication.Data4[3] = 0x24;
            local_54.dwMaxPlayers = 8;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDPlaySessionNameValue, this)();
            local_54.lpszSessionName = this->DPLAYX_SessionName;
            this->DPLAYX_4A->SetSessionDesc(&local_54, 0);
        };
    }

}
}
