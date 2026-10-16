#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E0E0
    void GameSynchronyState::clearSessionsList()
    {
        void* pvVar1;
        int iVar2;
        iVar2 = 0;
        if (0 < this->DPLAY_SessionsCount) {
            do {
                MACRO_CALL(OS_Func::_free_base)(DAT_GameSynchronyState::instance.DPLAY_SessionNames[iVar2]);
                pvVar1 = GlobalHandle(DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[iVar2]);
                GlobalUnlock(pvVar1);
                pvVar1 = GlobalHandle(DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[iVar2]);
                GlobalFree(pvVar1);
                iVar2 = iVar2 + 1;
            } while (iVar2 < this->DPLAY_SessionsCount);
        }
        this->DPLAY_SessionsCount = 0;
    }

}
}
