#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E0E0
    void GameSynchronyState::clearSessionsList()
    {
        for (int _session = 0; _session < this->DPLAY_SessionsCount; ++_session) {
            MACRO_CALL(OS_Func::_free_base)(DAT_GameSynchronyState::instance.DPLAY_SessionNames[_session]);
            GlobalUnlock(GlobalHandle(DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[_session]));
            GlobalFree(GlobalHandle(DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[_session]));
        }
        this->DPLAY_SessionsCount = 0;
    }

}
}
