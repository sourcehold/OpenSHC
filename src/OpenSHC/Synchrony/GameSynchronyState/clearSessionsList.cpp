#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E0E0
    void GameSynchronyState::clearSessionsList()
    {
        if (0 < this->DPLAY_SessionsCount) {
            for (int _session = 0; _session < this->DPLAY_SessionsCount; ++_session) {
                MACRO_CALL(OS_Func::_free_base)(DAT_GameSynchronyState::instance.DPLAY_SessionNames[_session]);
                void* _guidHandle = GlobalHandle(DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[_session]);
                GlobalUnlock(_guidHandle);
                _guidHandle = GlobalHandle(DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[_session]);
                GlobalFree(_guidHandle);
            }
        }
        this->DPLAY_SessionsCount = 0;
    }

}
}
