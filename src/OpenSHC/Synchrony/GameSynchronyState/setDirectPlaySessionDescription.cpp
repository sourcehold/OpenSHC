#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/GUID_APP.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047DEA0
    void GameSynchronyState::setDirectPlaySessionDescription()
    {
        if (!this->isHost) {
            return;
        }
        DPSESSIONDESC2 description;
        MACRO_CALL(OS_Func::_memset)(&description, 0, sizeof(description));
        description.dwSize = sizeof(description);
        description.dwFlags
            = DPSESSION_OPTIMIZELATENCY | DPSESSION_DIRECTPLAYPROTOCOL | DPSESSION_KEEPALIVE | DPSESSION_MIGRATEHOST;
        description.guidApplication = GUID_APP::instance;
        description.dwMaxPlayers = 8;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDPlaySessionNameValue, this)();
        description.lpszSessionName = this->DPLAYX_SessionName;
        this->DPLAYX_4A->SetSessionDesc(&description, 0);
    }

}
}
